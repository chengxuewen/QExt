#include <qextBPUndoCommands.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPBasicGraphicsScene.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPTypes.h>
#include <qextBPUtils.h>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QMimeData>
#include <QtGui/QClipboard>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsObject>

#include <typeinfo>

static QJsonObject serializeSelectedItems(QExtBPBasicGraphicsScene *scene)
{
    QJsonObject serializedScene;
    auto &graphModel = scene->graphModel();
    std::unordered_set<QExtBPTypes::NodeId> selectedNodes;

    QJsonArray nodesJsonArray;
    for (QGraphicsItem *item : scene->selectedItems())
    {
        if (auto n = qgraphicsitem_cast<QExtBPNodeGraphicsObject *>(item))
        {
            nodesJsonArray.append(graphModel.saveNode(n->nodeId()));
            selectedNodes.insert(n->nodeId());
        }
    }

    QJsonArray connJsonArray;
    for (QGraphicsItem *item : scene->selectedItems())
    {
        if (auto c = qgraphicsitem_cast<QExtBPConnectionGraphicsObject *>(item))
        {
            const auto &cid = c->connectionId();
            if (selectedNodes.count(cid.outNodeId) > 0 && selectedNodes.count(cid.inNodeId) > 0)
            {
                connJsonArray.append(QExtBPUtils::toJson(cid));
            }
        }
    }

    serializedScene["nodes"] = nodesJsonArray;
    serializedScene["connections"] = connJsonArray;
    return serializedScene;
}

static void insertSerializedItems(const QJsonObject &json, QExtBPBasicGraphicsScene *scene)
{
    QExtBPAbstractGraphModel &graphModel = scene->graphModel();

    const QJsonArray &nodesJsonArray = json["nodes"].toArray();

    for (QJsonValue node : nodesJsonArray)
    {
        QJsonObject obj = node.toObject();

        graphModel.loadNode(obj);

        auto id = obj["id"].toInt();
        scene->nodeGraphicsObject(id)->setZValue(1.0);
        scene->nodeGraphicsObject(id)->setSelected(true);
    }

    const QJsonArray &connJsonArray = json["connections"].toArray();

    for (QJsonValue connection : connJsonArray)
    {
        QJsonObject connJson = connection.toObject();

        QExtBPTypes::ConnectionId connId = QExtBPUtils::fromJson(connJson);

        // Restore the connection
        graphModel.addConnection(connId);

        scene->connectionGraphicsObject(connId)->setSelected(true);
    }
}

static void deleteSerializedItems(QJsonObject &sceneJson, QExtBPAbstractGraphModel &graphModel)
{
    QJsonArray connectionJsonArray = sceneJson["connections"].toArray();

    for (QJsonValueRef connection : connectionJsonArray)
    {
        QJsonObject connJson = connection.toObject();

        QExtBPTypes::ConnectionId connId = QExtBPUtils::fromJson(connJson);

        graphModel.deleteConnection(connId);
    }

    QJsonArray nodesJsonArray = sceneJson["nodes"].toArray();

    for (QJsonValueRef node : nodesJsonArray)
    {
        QJsonObject nodeJson = node.toObject();
        graphModel.deleteNode(nodeJson["id"].toInt());
    }
}

static QPointF computeAverageNodePosition(const QJsonObject &sceneJson)
{
    QPointF averagePos(0, 0);

    QJsonArray nodesJsonArray = sceneJson["nodes"].toArray();

    for (QJsonValueRef node : nodesJsonArray)
    {
        QJsonObject nodeJson = node.toObject();

        averagePos += QPointF(nodeJson["position"].toObject()["x"].toDouble(),
                nodeJson["position"].toObject()["y"].toDouble());
    }

    averagePos /= static_cast<double>(nodesJsonArray.size());

    return averagePos;
}

//-------------------------------------

QExtBPCreateCommand::QExtBPCreateCommand(QExtBPBasicGraphicsScene *scene,
                                         const QString name,
                                         const QPointF &mouseScenePos)
    : m_scene(scene)
    , m_sceneJson(QJsonObject())
{
    m_nodeId = m_scene->graphModel().addNode(name);
    if (m_nodeId != QExtBPTypes::InvalidNodeId)
    {
        m_scene->graphModel().setNodeData(m_nodeId, QExtBPTypes::NodeRole_Position, mouseScenePos);
    }
    else
    {
        setObsolete(true);
    }
}

void QExtBPCreateCommand::undo()
{
    QJsonArray nodesJsonArray;
    nodesJsonArray.append(m_scene->graphModel().saveNode(m_nodeId));
    m_sceneJson["nodes"] = nodesJsonArray;
    
    m_scene->graphModel().deleteNode(m_nodeId);
}

void QExtBPCreateCommand::redo()
{
    if (m_sceneJson.empty() || m_sceneJson["nodes"].toArray().empty())
    {
        return;
    }
    
    insertSerializedItems(m_sceneJson, m_scene);
}

//-------------------------------------

QExtBPDeleteCommand::QExtBPDeleteCommand(QExtBPBasicGraphicsScene *scene)
    : m_scene(scene)
{
    auto &graphModel = m_scene->graphModel();

    QJsonArray connJsonArray;
    // Delete the selected connections first, ensuring that they won't be
    // automatically deleted when selected nodes are deleted (deleting a
    // node deletes some connections as well)
    for (QGraphicsItem *item : m_scene->selectedItems())
    {
        if (auto c = qgraphicsitem_cast<QExtBPConnectionGraphicsObject *>(item))
        {
            const auto &cid = c->connectionId();

            connJsonArray.append(QExtBPUtils::toJson(cid));
        }
    }

    QJsonArray nodesJsonArray;
    // Delete the nodes; this will delete many of the connections.
    // Selected connections were already deleted prior to this loop,
    for (QGraphicsItem *item : m_scene->selectedItems())
    {
        if (auto n = qgraphicsitem_cast<QExtBPNodeGraphicsObject *>(item))
        {
            // saving connections attached to the selected nodes
            for (const auto &cid : graphModel.allConnectionIds(n->nodeId()))
            {
                connJsonArray.append(QExtBPUtils::toJson(cid));
            }

            nodesJsonArray.append(graphModel.saveNode(n->nodeId()));
        }
    }

    // If nothing is deleted, cancel this operation
    if (connJsonArray.isEmpty() && nodesJsonArray.isEmpty())
    {
        setObsolete(true);
    }

    m_sceneJson["nodes"] = nodesJsonArray;
    m_sceneJson["connections"] = connJsonArray;
}

void QExtBPDeleteCommand::undo()
{
    insertSerializedItems(m_sceneJson, m_scene);
}

void QExtBPDeleteCommand::redo()
{
    deleteSerializedItems(m_sceneJson, m_scene->graphModel());
}

//-------------------------------------

void offsetNodeGroup(QJsonObject &sceneJson, const QPointF &diff)
{
    QJsonArray nodesJsonArray = sceneJson["nodes"].toArray();

    QJsonArray newNodesJsonArray;
    for (QJsonValueRef node : nodesJsonArray)
    {
        QJsonObject obj = node.toObject();

        QPointF oldPos(obj["position"].toObject()["x"].toDouble(),
                obj["position"].toObject()["y"].toDouble());

        oldPos += diff;

        QJsonObject posJson;
        posJson["x"] = oldPos.x();
        posJson["y"] = oldPos.y();
        obj["position"] = posJson;

        newNodesJsonArray.append(obj);
    }

    sceneJson["nodes"] = newNodesJsonArray;
}

//-------------------------------------

CopyCommand::CopyCommand(QExtBPBasicGraphicsScene *scene)
{
    QJsonObject sceneJson = serializeSelectedItems(scene);

    if (sceneJson.empty() || sceneJson["nodes"].toArray().empty())
    {
        setObsolete(true);
        return;
    }

    QClipboard *clipboard = QApplication::clipboard();

    QByteArray const data = QJsonDocument(sceneJson).toJson();

    QMimeData *mimeData = new QMimeData();
    mimeData->setData("application/qt-nodes-graph", data);
    mimeData->setText(data);

    clipboard->setMimeData(mimeData);

    // Copy command does not have any effective redo/undo operations.
    // It copies the data to the clipboard and could be immediately removed
    // from the stack.
    setObsolete(true);
}

//-------------------------------------

QExtBPPasteCommand::QExtBPPasteCommand(QExtBPBasicGraphicsScene *scene, const QPointF &mouseScenePos)
    : m_scene(scene)
    , m_mouseScenePos(mouseScenePos)
{
    m_newSceneJson = takeSceneJsonFromClipboard();

    if (m_newSceneJson.empty() || m_newSceneJson["nodes"].toArray().empty())
    {
        setObsolete(true);
        return;
    }

    m_newSceneJson = makeNewNodeIdsInScene(m_newSceneJson);

    QPointF averagePos = computeAverageNodePosition(m_newSceneJson);

    offsetNodeGroup(m_newSceneJson, m_mouseScenePos - averagePos);
}

void QExtBPPasteCommand::undo()
{
    deleteSerializedItems(m_newSceneJson, m_scene->graphModel());
}

void QExtBPPasteCommand::redo()
{
    m_scene->clearSelection();

    // Ignore if pasted in content does not generate nodes.
    try
    {
        insertSerializedItems(m_newSceneJson, m_scene);
    }
    catch (...)
    {
        // If the paste does not work, delete all selected nodes and connections
        // `deleteNode(...)` implicitly removed connections
        auto &graphModel = m_scene->graphModel();

        QJsonArray nodesJsonArray;
        for (QGraphicsItem *item : m_scene->selectedItems())
        {
            if (auto n = qgraphicsitem_cast<QExtBPNodeGraphicsObject *>(item))
            {
                graphModel.deleteNode(n->nodeId());
            }
        }

        setObsolete(true);
    }
}

QJsonObject QExtBPPasteCommand::takeSceneJsonFromClipboard()
{
    QClipboard const *clipboard = QApplication::clipboard();
    QMimeData const *mimeData = clipboard->mimeData();

    QJsonDocument json;
    if (mimeData->hasFormat("application/qt-nodes-graph"))
    {
        json = QJsonDocument::fromJson(mimeData->data("application/qt-nodes-graph"));
    }
    else if (mimeData->hasText())
    {
        json = QJsonDocument::fromJson(mimeData->text().toUtf8());
    }

    return json.object();
}

QJsonObject QExtBPPasteCommand::makeNewNodeIdsInScene(const QJsonObject &sceneJson)
{
    QExtBPAbstractGraphModel &graphModel = m_scene->graphModel();

    std::unordered_map<QExtBPTypes::NodeId, QExtBPTypes::NodeId> mapNodeIds;

    QJsonArray nodesJsonArray = sceneJson["nodes"].toArray();

    QJsonArray newNodesJsonArray;
    for (QJsonValueRef node : nodesJsonArray)
    {
        QJsonObject nodeJson = node.toObject();

        QExtBPTypes::NodeId oldNodeId = nodeJson["id"].toInt();

        QExtBPTypes::NodeId newNodeId = graphModel.newNodeId();

        mapNodeIds[oldNodeId] = newNodeId;

        // Replace QExtBPTypes::NodeId in json
        nodeJson["id"] = static_cast<qint64>(newNodeId);

        newNodesJsonArray.append(nodeJson);
    }

    QJsonArray connectionJsonArray = sceneJson["connections"].toArray();

    QJsonArray newConnJsonArray;
    for (QJsonValueRef connection : connectionJsonArray)
    {
        QJsonObject connJson = connection.toObject();

        QExtBPTypes::ConnectionId connId = QExtBPUtils::fromJson(connJson);

        QExtBPTypes::ConnectionId newConnId{mapNodeIds[connId.outNodeId],
                    connId.outPortIndex,
                    mapNodeIds[connId.inNodeId],
                    connId.inPortIndex};

        newConnJsonArray.append(QExtBPUtils::toJson(newConnId));
    }

    QJsonObject newSceneJson;

    newSceneJson["nodes"] = newNodesJsonArray;
    newSceneJson["connections"] = newConnJsonArray;

    return newSceneJson;
}

//-------------------------------------

QExtBPDisconnectCommand::QExtBPDisconnectCommand(QExtBPBasicGraphicsScene *scene, const QExtBPTypes::ConnectionId connId)
    : m_scene(scene)
    , m_connId(connId)
{
    //
}

void QExtBPDisconnectCommand::undo()
{
    m_scene->graphModel().addConnection(m_connId);
}

void QExtBPDisconnectCommand::redo()
{
    m_scene->graphModel().deleteConnection(m_connId);
}

//------

ConnectCommand::ConnectCommand(QExtBPBasicGraphicsScene *scene, const QExtBPTypes::ConnectionId connId)
    : m_scene(scene)
    , m_connId(connId)
{
    //
}

void ConnectCommand::undo()
{
    m_scene->graphModel().deleteConnection(m_connId);
}

void ConnectCommand::redo()
{
    m_scene->graphModel().addConnection(m_connId);
}

//------

QExtBPMoveNodeCommand::QExtBPMoveNodeCommand(QExtBPBasicGraphicsScene *scene, const QPointF &diff)
    : m_scene(scene)
    , m_diff(diff)
{
    m_selectedNodes.clear();
    for (QGraphicsItem *item : m_scene->selectedItems())
    {
        if (auto n = qgraphicsitem_cast<QExtBPNodeGraphicsObject *>(item))
        {
            m_selectedNodes.insert(n->nodeId());
        }
    }
}

void QExtBPMoveNodeCommand::undo()
{
    for (auto nodeId : m_selectedNodes)
    {
        auto oldPos = m_scene->graphModel().nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>();

        oldPos -= m_diff;

        m_scene->graphModel().setNodeData(nodeId, QExtBPTypes::NodeRole_Position, oldPos);
    }
}

void QExtBPMoveNodeCommand::redo()
{
    for (auto nodeId : m_selectedNodes)
    {
        auto oldPos = m_scene->graphModel().nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>();

        oldPos += m_diff;

        m_scene->graphModel().setNodeData(nodeId, QExtBPTypes::NodeRole_Position, oldPos);
    }
}

int QExtBPMoveNodeCommand::id() const
{
    return static_cast<int>(typeid(QExtBPMoveNodeCommand).hash_code());
}

bool QExtBPMoveNodeCommand::mergeWith(QUndoCommand const *c)
{
    auto mc = static_cast<QExtBPMoveNodeCommand const *>(c);

    if (m_selectedNodes == mc->m_selectedNodes)
    {
        m_diff += mc->m_diff;
        return true;
    }
    return false;
}
