#include <private/qextBPBasicGraphicsScene_p.h>
#include <qextBPDefaultHorizontalNodeGeometry.h>
#include <qextBPDefaultVerticalNodeGeometry.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPDefaultNodePainter.h>
#include <qextBPAbstractNodeGeometry.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPGraphicsView.h>
#include <qextBPUtils.h>

#include <QUndoStack>
#include <QFileDialog>
#include <QGraphicsSceneMoveEvent>

#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtCore/QtGlobal>
#include <QtCore/QJsonArray>
#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

#include <utility>
#include <unordered_set>

QExtBPBasicGraphicsScenePrivate::QExtBPBasicGraphicsScenePrivate(QExtBPBasicGraphicsScene *q,
                                                                 QExtBPAbstractGraphModel &graphModel)
    : q_ptr(q)
    , m_graphModel(graphModel)
    , m_nodeGeometry(new QExtBPDefaultHorizontalNodeGeometry(graphModel))
    , m_nodePainter(new QExtBPDefaultNodePainter())
    , m_nodeDrag(false)
    , m_undoStack(new QUndoStack)
    , m_orientation(Qt::Horizontal)
{
}

QExtBPBasicGraphicsScenePrivate::~QExtBPBasicGraphicsScenePrivate()
{
}

void QExtBPBasicGraphicsScenePrivate::initBasicGraphicsScene()
{
    Q_Q(QExtBPBasicGraphicsScene);
    q->setItemIndexMethod(QGraphicsScene::NoIndex);
    // this->addItem()
    QObject::connect(&m_graphModel, SIGNAL(connectionCreated(QExtBPTypes::ConnectionId)),
                     q, SLOT(onConnectionCreated(QExtBPTypes::ConnectionId)));

    QObject::connect(&m_graphModel, SIGNAL(connectionDeleted(QExtBPTypes::ConnectionId)),
                     q, SLOT(onConnectionDeleted(QExtBPTypes::ConnectionId)));

    QObject::connect(&m_graphModel, SIGNAL(nodeCreated(QExtBPTypes::NodeId)),
                     q, SLOT(onNodeCreated(QExtBPTypes::NodeId)));

    QObject::connect(&m_graphModel, SIGNAL(nodeDeleted(QExtBPTypes::NodeId)),
                     q, SLOT(onNodeDeleted(QExtBPTypes::NodeId)));

    QObject::connect(&m_graphModel, SIGNAL(nodePositionUpdated(QExtBPTypes::NodeId)),
                     q, SLOT(onNodePositionUpdated(QExtBPTypes::NodeId)));

    QObject::connect(&m_graphModel, SIGNAL(nodeUpdated(QExtBPTypes::NodeId)),
                     q, SLOT(onNodeUpdated(QExtBPTypes::NodeId)));

    QObject::connect(&m_graphModel, SIGNAL(modelReset()),
                     q, SLOT(onModelReset()));

    QObject::connect(q, SIGNAL(nodeClicked(QExtBPTypes::NodeId)), q, SLOT(onNodeClicked(QExtBPTypes::NodeId)));


    q->traverseGraphAndPopulateGraphicsObjects();
}

QExtBPBasicGraphicsScene::QExtBPBasicGraphicsScene(QExtBPAbstractGraphModel &graphModel, QObject *parent)
    : QGraphicsScene(parent)
    , dd_ptr(new QExtBPBasicGraphicsScenePrivate(this, graphModel))
{
    dd_ptr->initBasicGraphicsScene();
}

QExtBPBasicGraphicsScene::QExtBPBasicGraphicsScene(QExtBPBasicGraphicsScenePrivate *d, QObject *parent)
    : QGraphicsScene(parent)
    , dd_ptr(d)
{
    dd_ptr->initBasicGraphicsScene();
}

QExtBPBasicGraphicsScene::~QExtBPBasicGraphicsScene()
{
}

const QExtBPAbstractGraphModel &QExtBPBasicGraphicsScene::graphModel() const
{
    Q_D(const QExtBPBasicGraphicsScene);
    return d->m_graphModel;
}

QExtBPAbstractGraphModel &QExtBPBasicGraphicsScene::graphModel()
{
    Q_D(QExtBPBasicGraphicsScene);
    return d->m_graphModel;
}

QExtBPAbstractNodeGeometry &QExtBPBasicGraphicsScene::nodeGeometry()
{
    Q_D(QExtBPBasicGraphicsScene);
    return *d->m_nodeGeometry;
}

QExtBPAbstractNodePainter &QExtBPBasicGraphicsScene::nodePainter()
{
    Q_D(QExtBPBasicGraphicsScene);
    return *d->m_nodePainter;
}

void QExtBPBasicGraphicsScene::setNodePainter(QScopedPointer<QExtBPAbstractNodePainter> newPainter)
{
    Q_D(QExtBPBasicGraphicsScene);
    d->m_nodePainter.swap(newPainter);
}

QUndoStack &QExtBPBasicGraphicsScene::undoStack()
{
    Q_D(QExtBPBasicGraphicsScene);
    return *d->m_undoStack;
}

const QScopedPointer<QExtBPConnectionGraphicsObject> &
QExtBPBasicGraphicsScene::makeDraftConnection(const QExtBPTypes::ConnectionId incompleteConnectionId)
{
    Q_D(QExtBPBasicGraphicsScene);
    d->m_draftConnection.reset(new QExtBPConnectionGraphicsObject(*this, incompleteConnectionId));
    d->m_draftConnection->grabMouse();
    return d->m_draftConnection;
}

void QExtBPBasicGraphicsScene::resetDraftConnection()
{
    Q_D(QExtBPBasicGraphicsScene);
    d->m_draftConnection.reset();
}

void QExtBPBasicGraphicsScene::clearScene()
{
    Q_D(QExtBPBasicGraphicsScene);
    const std::unordered_set<QExtBPTypes::NodeId> &allNodeIds = this->graphModel().allNodeIds();
    for (auto nodeId : allNodeIds)
    {
        this->graphModel().deleteNode(nodeId);
    }
}

QExtBPNodeGraphicsObject *QExtBPBasicGraphicsScene::nodeGraphicsObject(QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPBasicGraphicsScene);
    QExtBPNodeGraphicsObject *ngo = QEXT_NULLPTR;
    auto it = d->m_nodeGraphicsObjects.find(nodeId);
    if (it != d->m_nodeGraphicsObjects.end())
    {
        ngo = it->second.get();
    }
    return ngo;
}

QExtBPConnectionGraphicsObject *QExtBPBasicGraphicsScene::connectionGraphicsObject(QExtBPTypes::ConnectionId connectionId)
{
    Q_D(QExtBPBasicGraphicsScene);
    QExtBPConnectionGraphicsObject *cgo = QEXT_NULLPTR;
    auto it = d->m_connectionGraphicsObjects.find(connectionId);
    if (it != d->m_connectionGraphicsObjects.end())
    {
        cgo = it->second.get();
    }
    return cgo;
}

Qt::Orientation QExtBPBasicGraphicsScene::orientation() const
{
    Q_D(const QExtBPBasicGraphicsScene);
    return d->m_orientation;
}

void QExtBPBasicGraphicsScene::setOrientation(Qt::Orientation const orientation)
{
    Q_D(QExtBPBasicGraphicsScene);
    if (d->m_orientation != orientation)
    {
        d->m_orientation = orientation;
        switch (d->m_orientation)
        {
        case Qt::Horizontal:
            d->m_nodeGeometry.reset(new QExtBPDefaultHorizontalNodeGeometry(d->m_graphModel));
            break;
        case Qt::Vertical:
            d->m_nodeGeometry.reset(new QExtBPDefaultVerticalNodeGeometry(d->m_graphModel));
            break;
        }
        this->onModelReset();
    }
}

QMenu *QExtBPBasicGraphicsScene::createSceneMenu(const QPointF scenePos)
{
    Q_UNUSED(scenePos);
    return QEXT_NULLPTR;
}

void QExtBPBasicGraphicsScene::traverseGraphAndPopulateGraphicsObjects()
{
    Q_D(QExtBPBasicGraphicsScene);
    auto allNodeIds = d->m_graphModel.allNodeIds();

    // First create all the nodes.
    for (const QExtBPTypes::NodeId nodeId : allNodeIds)
    {
        d->m_nodeGraphicsObjects[nodeId].reset(new QExtBPNodeGraphicsObject(*this, nodeId));
    }

    // Then for each node check output connections and insert them.
    for (const QExtBPTypes::NodeId nodeId : allNodeIds)
    {
        unsigned int nOutPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

        for (QExtBPTypes::PortIndex index = 0; index < nOutPorts; ++index)
        {
            const auto &outConnectionIds = d->m_graphModel.connections(nodeId, QExtBPTypes::PortType_Out, index);

            for (auto cid : outConnectionIds)
            {
                d->m_connectionGraphicsObjects[cid].reset(new QExtBPConnectionGraphicsObject(*this, cid));
            }
        }
    }
}

void QExtBPBasicGraphicsScene::updateAttachedNodes(const QExtBPTypes::ConnectionId connectionId,
                                                   const QExtBPTypes::PortTypeEnum portType)
{
    Q_D(QExtBPBasicGraphicsScene);
    auto node = this->nodeGraphicsObject(QExtBPUtils::getNodeId(portType, connectionId));
    if (node)
    {
        node->update();
    }
}

void QExtBPBasicGraphicsScene::onConnectionDeleted(const QExtBPTypes::ConnectionId connectionId)
{
    Q_D(QExtBPBasicGraphicsScene);
    auto it = d->m_connectionGraphicsObjects.find(connectionId);
    if (it != d->m_connectionGraphicsObjects.end())
    {
        d->m_connectionGraphicsObjects.erase(it);
    }

    // TODO: do we need it?
    if (d->m_draftConnection && d->m_draftConnection->connectionId() == connectionId)
    {
        d->m_draftConnection.reset();
    }

    this->updateAttachedNodes(connectionId, QExtBPTypes::PortType_Out);
    this->updateAttachedNodes(connectionId, QExtBPTypes::PortType_In);
}

void QExtBPBasicGraphicsScene::onConnectionCreated(const QExtBPTypes::ConnectionId connectionId)
{
    Q_D(QExtBPBasicGraphicsScene);
    d->m_connectionGraphicsObjects[connectionId].reset(new QExtBPConnectionGraphicsObject(*this, connectionId));

    this->updateAttachedNodes(connectionId, QExtBPTypes::PortType_Out);
    this->updateAttachedNodes(connectionId, QExtBPTypes::PortType_In);
}

void QExtBPBasicGraphicsScene::onNodeDeleted(const QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPBasicGraphicsScene);
    auto it = d->m_nodeGraphicsObjects.find(nodeId);
    if (it != d->m_nodeGraphicsObjects.end())
    {
        d->m_nodeGraphicsObjects.erase(it);
    }
}

void QExtBPBasicGraphicsScene::onNodeCreated(const QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPBasicGraphicsScene);
    d->m_nodeGraphicsObjects[nodeId].reset(new QExtBPNodeGraphicsObject(*this, nodeId));
}

void QExtBPBasicGraphicsScene::onNodePositionUpdated(const QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPBasicGraphicsScene);
    auto node = this->nodeGraphicsObject(nodeId);
    if (node)
    {
        node->setPos(d->m_graphModel.nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>());
        node->update();
        d->m_nodeDrag = true;
    }
}

void QExtBPBasicGraphicsScene::onNodeUpdated(const QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPBasicGraphicsScene);
    auto node = this->nodeGraphicsObject(nodeId);
    if (node)
    {
        node->setGeometryChanged();
        d->m_nodeGeometry->recomputeSize(nodeId);
        node->update();
        node->moveConnections();
    }
}

void QExtBPBasicGraphicsScene::onNodeClicked(const QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPBasicGraphicsScene);
    if (d->m_nodeDrag)
    {
        Q_EMIT this->nodeMoved(nodeId,
                               d->m_graphModel.nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>());
    }
    d->m_nodeDrag = false;
}

void QExtBPBasicGraphicsScene::onModelReset()
{
    Q_D(QExtBPBasicGraphicsScene);
    d->m_connectionGraphicsObjects.clear();
    d->m_nodeGraphicsObjects.clear();

    this->clear();
    this->traverseGraphAndPopulateGraphicsObjects();
}
