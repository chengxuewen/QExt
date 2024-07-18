#include "SimpleGraphModel.hpp"

SimpleGraphModel::SimpleGraphModel()
    : _nextNodeId{0}
{}

SimpleGraphModel::~SimpleGraphModel()
{
    //
}

std::unordered_set<QExtBPTypes::NodeId> SimpleGraphModel::allNodeIds() const
{
    return _nodeIds;
}

std::unordered_set<QExtBPTypes::ConnectionId> SimpleGraphModel::allConnectionIds(const QExtBPTypes::NodeId nodeId) const
{
    std::unordered_set<QExtBPTypes::ConnectionId> result;

    std::copy_if(_connectivity.begin(),
                 _connectivity.end(),
                 std::inserter(result, std::end(result)),
                 [&nodeId](const QExtBPTypes::ConnectionId &cid) {
                     return cid.inNodeId == nodeId || cid.outNodeId == nodeId;
                 });

    return result;
}

std::unordered_set<QExtBPTypes::ConnectionId> SimpleGraphModel::connections(QExtBPTypes::NodeId nodeId,
                                                               QExtBPTypes::PortTypeEnum portType,
                                                               QExtBPTypes::PortIndex portIndex) const
{
    std::unordered_set<QExtBPTypes::ConnectionId> result;

    std::copy_if(_connectivity.begin(),
                 _connectivity.end(),
                 std::inserter(result, std::end(result)),
                 [&portType, &portIndex, &nodeId](const QExtBPTypes::ConnectionId &cid) {
                     return (QExtBPUtils::getNodeId(portType, cid) == nodeId
                             && QExtBPUtils::getPortIndex(portType, cid) == portIndex);
                 });

    return result;
}

bool SimpleGraphModel::connectionExists(const QExtBPTypes::ConnectionId connectionId) const
{
    return (_connectivity.find(connectionId) != _connectivity.end());
}

QExtBPTypes::NodeId SimpleGraphModel::addNode(QString const nodeType)
{
    QExtBPTypes::NodeId newId = _nextNodeId++;
    // Create new node.
    _nodeIds.insert(newId);

    Q_EMIT nodeCreated(newId);

    return newId;
}

bool SimpleGraphModel::connectionPossible(const QExtBPTypes::ConnectionId connectionId) const
{
    return _connectivity.find(connectionId) == _connectivity.end();
}

void SimpleGraphModel::addConnection(const QExtBPTypes::ConnectionId connectionId)
{
    _connectivity.insert(connectionId);

    Q_EMIT connectionCreated(connectionId);
}

bool SimpleGraphModel::nodeExists(const QExtBPTypes::NodeId nodeId) const
{
    return (_nodeIds.find(nodeId) != _nodeIds.end());
}

QVariant SimpleGraphModel::nodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role) const
{
    Q_UNUSED(nodeId);

    QVariant result;

    switch (role) {
    case QExtBPTypes::NodeRole_Type:
        result = QString("Default Node Type");
        break;

    case QExtBPTypes::NodeRole_Position:
        result = _nodeGeometryData[nodeId].pos;
        break;

    case QExtBPTypes::NodeRole_Size:
        result = _nodeGeometryData[nodeId].size;
        break;

    case QExtBPTypes::NodeRole_CaptionVisible:
        result = true;
        break;

    case QExtBPTypes::NodeRole_Caption:
        result = QString("Node");
        break;

    case QExtBPTypes::NodeRole_Style: {
        auto style = QExtBPStyleCollection::nodeStyle();
        result = style.toJson().toVariantMap();
    } break;

    case QExtBPTypes::NodeRole_InternalData:
        break;

    case QExtBPTypes::NodeRole_InPortCount:
        result = 5u;
        break;

    case QExtBPTypes::NodeRole_OutPortCount:
        result = 3u;
        break;

    case QExtBPTypes::NodeRole_Widget:
        result = QVariant();
        break;
    }

    return result;
}

bool SimpleGraphModel::setNodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role, QVariant value)
{
    bool result = false;

    switch (role) {
    case QExtBPTypes::NodeRole_Type:
        break;
    case QExtBPTypes::NodeRole_Position: {
        _nodeGeometryData[nodeId].pos = value.value<QPointF>();

        Q_EMIT nodePositionUpdated(nodeId);

        result = true;
    } break;

    case QExtBPTypes::NodeRole_Size: {
        _nodeGeometryData[nodeId].size = value.value<QSize>();
        result = true;
    } break;

    case QExtBPTypes::NodeRole_CaptionVisible:
        break;

    case QExtBPTypes::NodeRole_Caption:
        break;

    case QExtBPTypes::NodeRole_Style:
        break;

    case QExtBPTypes::NodeRole_InternalData:
        break;

    case QExtBPTypes::NodeRole_InPortCount:
        break;

    case QExtBPTypes::NodeRole_OutPortCount:
        break;

    case QExtBPTypes::NodeRole_Widget:
        break;
    }

    return result;
}

QVariant SimpleGraphModel::portData(QExtBPTypes::NodeId nodeId,
                                    QExtBPTypes::PortTypeEnum portType,
                                    QExtBPTypes::PortIndex portIndex,
                                    QExtBPTypes::PortRoleEnum role) const
{
    switch (role) {
    case QExtBPTypes::PortRole_Data:
        return QVariant();
        break;

    case QExtBPTypes::PortRole_DataType:
        return QVariant();
        break;

    case QExtBPTypes::PortRole_ConnectionPolicyRole:
        return QVariant::fromValue(QExtBPTypes::ConnectionPolicy_One);
        break;

    case QExtBPTypes::PortRole_CaptionVisible:
        return true;
        break;

    case QExtBPTypes::PortRole_Caption:
        if (portType == QExtBPTypes::PortType_In)
            return QString::fromUtf8("Port In");
        else
            return QString::fromUtf8("Port Out");

        break;
    }

    return QVariant();
}

bool SimpleGraphModel::setPortData(QExtBPTypes::NodeId nodeId,
                                   QExtBPTypes::PortTypeEnum portType,
                                   QExtBPTypes::PortIndex portIndex,
                                   const QVariant &value,
                                   QExtBPTypes::PortRoleEnum role)
{
    Q_UNUSED(nodeId);
    Q_UNUSED(portType);
    Q_UNUSED(portIndex);
    Q_UNUSED(value);
    Q_UNUSED(role);

    return false;
}

bool SimpleGraphModel::deleteConnection(const QExtBPTypes::ConnectionId connectionId)
{
    bool disconnected = false;

    auto it = _connectivity.find(connectionId);

    if (it != _connectivity.end()) {
        disconnected = true;

        _connectivity.erase(it);
    }

    if (disconnected)
        Q_EMIT connectionDeleted(connectionId);

    return disconnected;
}

bool SimpleGraphModel::deleteNode(const QExtBPTypes::NodeId nodeId)
{
    // Delete connections to this node first.
    auto connectionIds = allConnectionIds(nodeId);
    for (auto &cId : connectionIds) {
        deleteConnection(cId);
    }

    _nodeIds.erase(nodeId);
    _nodeGeometryData.erase(nodeId);

    Q_EMIT nodeDeleted(nodeId);

    return true;
}

QJsonObject SimpleGraphModel::saveNode(const QExtBPTypes::NodeId nodeId) const
{
    QJsonObject nodeJson;

    nodeJson["id"] = static_cast<qint64>(nodeId);

    {
        const QPointF pos = nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>();

        QJsonObject posJson;
        posJson["x"] = pos.x();
        posJson["y"] = pos.y();
        nodeJson["position"] = posJson;
    }

    return nodeJson;
}

void SimpleGraphModel::loadNode(const QJsonObject &nodeJson)
{
    QExtBPTypes::NodeId restoredNodeId = nodeJson["id"].toInt();

    // Next QExtBPTypes::NodeId must be larger that any id existing in the graph
    _nextNodeId = std::max(restoredNodeId + 1, _nextNodeId);

    // Create new node.
    _nodeIds.insert(restoredNodeId);

    Q_EMIT nodeCreated(restoredNodeId);

    {
        QJsonObject posJson = nodeJson["position"].toObject();
        const QPointF pos(posJson["x"].toDouble(), posJson["y"].toDouble());

        setNodeData(restoredNodeId, QExtBPTypes::NodeRole_Position, pos);
    }
}
