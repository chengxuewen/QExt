#include <qextBPBasicGraphicsScene.h>
#include <qextBPDefaultHorizontalNodeGeometry.h>
#include <qextBPDefaultVerticalNodeGeometry.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPDefaultNodePainter.h>
#include <qextBPAbstractNodeGeometry.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPGraphicsView.h>
#include <qextBPUtils.h>

#include <QUndoStack>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsSceneMoveEvent>

#include <QtCore/QBuffer>
#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QtGlobal>

#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <utility>
#include <queue>


QExtBPBasicGraphicsScene::QExtBPBasicGraphicsScene(QExtBPAbstractGraphModel &graphModel, QObject *parent)
    : QGraphicsScene(parent)
    , _graphModel(graphModel)
    , _nodeGeometry(new QExtBPDefaultHorizontalNodeGeometry(_graphModel))
    , _nodePainter(new QExtBPDefaultNodePainter())
    , _nodeDrag(false)
    , _undoStack(new QUndoStack(this))
    , _orientation(Qt::Horizontal)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    // this->addItem()
    connect(&_graphModel,
            &QExtBPAbstractGraphModel::connectionCreated,
            this,
            &QExtBPBasicGraphicsScene::onConnectionCreated);

    connect(&_graphModel,
            &QExtBPAbstractGraphModel::connectionDeleted,
            this,
            &QExtBPBasicGraphicsScene::onConnectionDeleted);

    connect(&_graphModel,
            &QExtBPAbstractGraphModel::nodeCreated,
            this,
            &QExtBPBasicGraphicsScene::onNodeCreated);

    connect(&_graphModel,
            &QExtBPAbstractGraphModel::nodeDeleted,
            this,
            &QExtBPBasicGraphicsScene::onNodeDeleted);

    connect(&_graphModel,
            &QExtBPAbstractGraphModel::nodePositionUpdated,
            this,
            &QExtBPBasicGraphicsScene::onNodePositionUpdated);

    connect(&_graphModel,
            &QExtBPAbstractGraphModel::nodeUpdated,
            this,
            &QExtBPBasicGraphicsScene::onNodeUpdated);

    connect(this, &QExtBPBasicGraphicsScene::nodeClicked, this, &QExtBPBasicGraphicsScene::onNodeClicked);

    connect(&_graphModel, &QExtBPAbstractGraphModel::modelReset, this, &QExtBPBasicGraphicsScene::onModelReset);

    traverseGraphAndPopulateGraphicsObjects();
}

QExtBPBasicGraphicsScene::~QExtBPBasicGraphicsScene() = default;

QExtBPAbstractGraphModel const &QExtBPBasicGraphicsScene::graphModel() const
{
    return _graphModel;
}

QExtBPAbstractGraphModel &QExtBPBasicGraphicsScene::graphModel()
{
    return _graphModel;
}

QExtBPAbstractNodeGeometry &QExtBPBasicGraphicsScene::nodeGeometry()
{
    return *_nodeGeometry;
}

QExtBPAbstractNodePainter &QExtBPBasicGraphicsScene::nodePainter()
{
    return *_nodePainter;
}

void QExtBPBasicGraphicsScene::setNodePainter(QScopedPointer<QExtBPAbstractNodePainter> newPainter)
{
    _nodePainter.swap(newPainter);
}

QUndoStack &QExtBPBasicGraphicsScene::undoStack()
{
    return *_undoStack;
}

const QScopedPointer<QExtBPConnectionGraphicsObject> &QExtBPBasicGraphicsScene::makeDraftConnection(
        QExtBPTypes::ConnectionId const incompleteConnectionId)
{
    _draftConnection.reset(new QExtBPConnectionGraphicsObject(*this, incompleteConnectionId));

    _draftConnection->grabMouse();

    return _draftConnection;
}

void QExtBPBasicGraphicsScene::resetDraftConnection()
{
    _draftConnection.reset();
}

void QExtBPBasicGraphicsScene::clearScene()
{
    auto const &allNodeIds = graphModel().allNodeIds();

    for (auto nodeId : allNodeIds) {
        graphModel().deleteNode(nodeId);
    }
}

QExtBPNodeGraphicsObject *QExtBPBasicGraphicsScene::nodeGraphicsObject(QExtBPTypes::NodeId nodeId)
{
    QExtBPNodeGraphicsObject *ngo = nullptr;
    auto it = _nodeGraphicsObjects.find(nodeId);
    if (it != _nodeGraphicsObjects.end()) {
        ngo = it->second.get();
    }

    return ngo;
}

QExtBPConnectionGraphicsObject *QExtBPBasicGraphicsScene::connectionGraphicsObject(QExtBPTypes::ConnectionId connectionId)
{
    QExtBPConnectionGraphicsObject *cgo = nullptr;
    auto it = _connectionGraphicsObjects.find(connectionId);
    if (it != _connectionGraphicsObjects.end()) {
        cgo = it->second.get();
    }

    return cgo;
}

void QExtBPBasicGraphicsScene::setOrientation(Qt::Orientation const orientation)
{
    if (_orientation != orientation) {
        _orientation = orientation;

        switch (_orientation) {
        case Qt::Horizontal:
            _nodeGeometry.reset(new QExtBPDefaultHorizontalNodeGeometry(_graphModel));
            break;

        case Qt::Vertical:
            _nodeGeometry.reset(new QExtBPDefaultVerticalNodeGeometry(_graphModel));
            break;
        }

        onModelReset();
    }
}

QMenu *QExtBPBasicGraphicsScene::createSceneMenu(QPointF const scenePos)
{
    Q_UNUSED(scenePos);
    return nullptr;
}

void QExtBPBasicGraphicsScene::traverseGraphAndPopulateGraphicsObjects()
{
    auto allNodeIds = _graphModel.allNodeIds();

    // First create all the nodes.
    for (QExtBPTypes::NodeId const nodeId : allNodeIds) {
        _nodeGraphicsObjects[nodeId].reset(new QExtBPNodeGraphicsObject(*this, nodeId));
    }

    // Then for each node check output connections and insert them.
    for (QExtBPTypes::NodeId const nodeId : allNodeIds) {
        unsigned int nOutPorts = _graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

        for (QExtBPTypes::PortIndex index = 0; index < nOutPorts; ++index) {
            auto const &outConnectionIds = _graphModel.connections(nodeId, QExtBPTypes::PortType_Out, index);

            for (auto cid : outConnectionIds) {
                _connectionGraphicsObjects[cid].reset(new QExtBPConnectionGraphicsObject(*this, cid));
            }
        }
    }
}

void QExtBPBasicGraphicsScene::updateAttachedNodes(QExtBPTypes::ConnectionId const connectionId,
                                                   QExtBPTypes::PortTypeEnum const portType)
{
    auto node = nodeGraphicsObject(QExtBPUtils::getNodeId(portType, connectionId));

    if (node) {
        node->update();
    }
}

void QExtBPBasicGraphicsScene::onConnectionDeleted(QExtBPTypes::ConnectionId const connectionId)
{
    auto it = _connectionGraphicsObjects.find(connectionId);
    if (it != _connectionGraphicsObjects.end()) {
        _connectionGraphicsObjects.erase(it);
    }

    // TODO: do we need it?
    if (_draftConnection && _draftConnection->connectionId() == connectionId) {
        _draftConnection.reset();
    }

    updateAttachedNodes(connectionId, QExtBPTypes::PortType_Out);
    updateAttachedNodes(connectionId, QExtBPTypes::PortType_In);
}

void QExtBPBasicGraphicsScene::onConnectionCreated(QExtBPTypes::ConnectionId const connectionId)
{
    _connectionGraphicsObjects[connectionId].reset(new QExtBPConnectionGraphicsObject(*this, connectionId));

    updateAttachedNodes(connectionId, QExtBPTypes::PortType_Out);
    updateAttachedNodes(connectionId, QExtBPTypes::PortType_In);
}

void QExtBPBasicGraphicsScene::onNodeDeleted(QExtBPTypes::NodeId const nodeId)
{
    auto it = _nodeGraphicsObjects.find(nodeId);
    if (it != _nodeGraphicsObjects.end()) {
        _nodeGraphicsObjects.erase(it);
    }
}

void QExtBPBasicGraphicsScene::onNodeCreated(QExtBPTypes::NodeId const nodeId)
{
    _nodeGraphicsObjects[nodeId].reset(new QExtBPNodeGraphicsObject(*this, nodeId));
}

void QExtBPBasicGraphicsScene::onNodePositionUpdated(QExtBPTypes::NodeId const nodeId)
{
    auto node = nodeGraphicsObject(nodeId);
    if (node) {
        node->setPos(_graphModel.nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>());
        node->update();
        _nodeDrag = true;
    }
}

void QExtBPBasicGraphicsScene::onNodeUpdated(QExtBPTypes::NodeId const nodeId)
{
    auto node = nodeGraphicsObject(nodeId);

    if (node) {
        node->setGeometryChanged();

        _nodeGeometry->recomputeSize(nodeId);

        node->update();
        node->moveConnections();
    }
}

void QExtBPBasicGraphicsScene::onNodeClicked(QExtBPTypes::NodeId const nodeId)
{
    if (_nodeDrag)
        Q_EMIT nodeMoved(nodeId, _graphModel.nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>());
    _nodeDrag = false;
}

void QExtBPBasicGraphicsScene::onModelReset()
{
    _connectionGraphicsObjects.clear();
    _nodeGraphicsObjects.clear();

    clear();

    traverseGraphAndPopulateGraphicsObjects();
}
