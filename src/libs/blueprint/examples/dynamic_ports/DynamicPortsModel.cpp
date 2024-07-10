#include "DynamicPortsModel.hpp"

#include "PortAddRemoveWidget.hpp"

#include <QExtBlueprint>

#include <QJsonArray>

#include <iterator>

DynamicPortsModel::DynamicPortsModel()
    : _nextNodeId{0}
{}

DynamicPortsModel::~DynamicPortsModel()
{
    //
}

std::unordered_set<QExtBPTypes::NodeId> DynamicPortsModel::allNodeIds() const
{
    return _nodeIds;
}

std::unordered_set<QExtBPTypes::ConnectionId> DynamicPortsModel::allConnectionIds(QExtBPTypes::NodeId const nodeId) const
{
    std::unordered_set<QExtBPTypes::ConnectionId> result;

    std::copy_if(_connectivity.begin(),
                 _connectivity.end(),
                 std::inserter(result, std::end(result)),
                 [&nodeId](QExtBPTypes::ConnectionId const &cid) {
                     return cid.inNodeId == nodeId || cid.outNodeId == nodeId;
                 });

    return result;
}

std::unordered_set<QExtBPTypes::ConnectionId> DynamicPortsModel::connections(QExtBPTypes::NodeId nodeId,
                                                                QExtBPTypes::PortTypeEnum portType,
                                                                QExtBPTypes::PortIndex portIndex) const
{
    std::unordered_set<QExtBPTypes::ConnectionId> result;

    std::copy_if(_connectivity.begin(),
                 _connectivity.end(),
                 std::inserter(result, std::end(result)),
                 [&portType, &portIndex, &nodeId](QExtBPTypes::ConnectionId const &cid) -> bool {
                     return (QExtBPUtils::getNodeId(portType, cid) == nodeId
                             && QExtBPUtils::getPortIndex(portType, cid) == portIndex);
                 });

    return result;
}

bool DynamicPortsModel::connectionExists(QExtBPTypes::ConnectionId const connectionId) const
{
    return (_connectivity.find(connectionId) != _connectivity.end());
}

QExtBPTypes::NodeId DynamicPortsModel::addNode(QString const nodeType)
{
    QExtBPTypes::NodeId newId = newNodeId();

    // Create new node.
    _nodeIds.insert(newId);

    Q_EMIT nodeCreated(newId);

    return newId;
}

bool DynamicPortsModel::connectionPossible(QExtBPTypes::ConnectionId const connectionId) const
{
    return !connectionExists(connectionId);
}

void DynamicPortsModel::addConnection(QExtBPTypes::ConnectionId const connectionId)
{
    _connectivity.insert(connectionId);

    Q_EMIT connectionCreated(connectionId);
}

bool DynamicPortsModel::nodeExists(QExtBPTypes::NodeId const nodeId) const
{
    return (_nodeIds.find(nodeId) != _nodeIds.end());
}

PortAddRemoveWidget *DynamicPortsModel::widget(QExtBPTypes::NodeId nodeId) const
{
    auto it = _nodeWidgets.find(nodeId);
    if (it == _nodeWidgets.end()) {
        _nodeWidgets[nodeId] = new PortAddRemoveWidget(0,
                                                       0,
                                                       nodeId,
                                                       *const_cast<DynamicPortsModel *>(this));
    }

    return _nodeWidgets[nodeId];
}

QVariant DynamicPortsModel::nodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role) const
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
        result = _nodePortCounts[nodeId].in;
        break;

    case QExtBPTypes::NodeRole_OutPortCount:
        result = _nodePortCounts[nodeId].out;
        break;

    case QExtBPTypes::NodeRole_Widget: {
        result = QVariant::fromValue(widget(nodeId));
        break;
    }
    }

    return result;
}

bool DynamicPortsModel::setNodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role, QVariant value)
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
        _nodePortCounts[nodeId].in = value.toUInt();
        widget(nodeId)->populateButtons(QExtBPTypes::PortType_In, value.toUInt());
        break;

    case QExtBPTypes::NodeRole_OutPortCount:
        _nodePortCounts[nodeId].out = value.toUInt();
        widget(nodeId)->populateButtons(QExtBPTypes::PortType_Out, value.toUInt());
        break;

    case QExtBPTypes::NodeRole_Widget:
        break;
    }

    return result;
}

QVariant DynamicPortsModel::portData(QExtBPTypes::NodeId nodeId,
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

bool DynamicPortsModel::setPortData(
    QExtBPTypes::NodeId nodeId, QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex, QVariant const &value, QExtBPTypes::PortRoleEnum role)
{
    Q_UNUSED(nodeId);
    Q_UNUSED(portType);
    Q_UNUSED(portIndex);
    Q_UNUSED(value);
    Q_UNUSED(role);

    return false;
}

bool DynamicPortsModel::deleteConnection(QExtBPTypes::ConnectionId const connectionId)
{
    bool disconnected = false;

    auto it = _connectivity.find(connectionId);

    if (it != _connectivity.end()) {
        disconnected = true;

        _connectivity.erase(it);
    };

    if (disconnected)
        Q_EMIT connectionDeleted(connectionId);

    return disconnected;
}

bool DynamicPortsModel::deleteNode(QExtBPTypes::NodeId const nodeId)
{
    // Delete connections to this node first.
    auto connectionIds = allConnectionIds(nodeId);
    for (auto &cId : connectionIds) {
        deleteConnection(cId);
    }

    _nodeIds.erase(nodeId);
    _nodeGeometryData.erase(nodeId);
    _nodePortCounts.erase(nodeId);
    _nodeWidgets.erase(nodeId);

    Q_EMIT nodeDeleted(nodeId);

    return true;
}

QJsonObject DynamicPortsModel::saveNode(QExtBPTypes::NodeId const nodeId) const
{
    QJsonObject nodeJson;

    nodeJson["id"] = static_cast<qint64>(nodeId);

    {
        QPointF const pos = nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>();

        QJsonObject posJson;
        posJson["x"] = pos.x();
        posJson["y"] = pos.y();
        nodeJson["position"] = posJson;

        nodeJson["inPortCount"] = QString::number(_nodePortCounts[nodeId].in);
        nodeJson["outPortCount"] = QString::number(_nodePortCounts[nodeId].out);
    }

    return nodeJson;
}

QJsonObject DynamicPortsModel::save() const
{
    QJsonObject sceneJson;

    QJsonArray nodesJsonArray;
    for (auto const nodeId : allNodeIds()) {
        nodesJsonArray.append(saveNode(nodeId));
    }
    sceneJson["nodes"] = nodesJsonArray;

    QJsonArray connJsonArray;
    for (auto const &cid : _connectivity) {
        connJsonArray.append(QExtBPUtils::toJson(cid));
    }
    sceneJson["connections"] = connJsonArray;

    return sceneJson;
}

void DynamicPortsModel::loadNode(QJsonObject const &nodeJson)
{
    QExtBPTypes::NodeId restoredNodeId = static_cast<QExtBPTypes::NodeId>(nodeJson["id"].toInt());

    _nextNodeId = std::max(_nextNodeId, restoredNodeId + 1);

    // Create new node.
    _nodeIds.insert(restoredNodeId);

    setNodeData(restoredNodeId, QExtBPTypes::NodeRole_InPortCount, nodeJson["inPortCount"].toString().toUInt());

    setNodeData(restoredNodeId,
                QExtBPTypes::NodeRole_OutPortCount,
                nodeJson["outPortCount"].toString().toUInt());

    {
        QJsonObject posJson = nodeJson["position"].toObject();
        QPointF const pos(posJson["x"].toDouble(), posJson["y"].toDouble());

        setNodeData(restoredNodeId, QExtBPTypes::NodeRole_Position, pos);
    }

    Q_EMIT nodeCreated(restoredNodeId);
}

void DynamicPortsModel::load(QJsonObject const &jsonDocument)
{
    QJsonArray nodesJsonArray = jsonDocument["nodes"].toArray();

    for (QJsonValueRef nodeJson : nodesJsonArray) {
        loadNode(nodeJson.toObject());
    }

    QJsonArray connectionJsonArray = jsonDocument["connections"].toArray();

    for (QJsonValueRef connection : connectionJsonArray) {
        QJsonObject connJson = connection.toObject();

        QExtBPTypes::ConnectionId connId = QExtBPUtils::fromJson(connJson);

        // Restore the connection
        addConnection(connId);
    }
}

void DynamicPortsModel::addPort(QExtBPTypes::NodeId nodeId, QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex)
{
    // STAGE 1.
    // Compute new addresses for the existing connections that are shifted and
    // placed after the new ones
    QExtBPTypes::PortIndex first = portIndex;
    QExtBPTypes::PortIndex last = first;
    portsAboutToBeInserted(nodeId, portType, first, last);

    // STAGE 2. Change the number of connections in your model
    if (portType == QExtBPTypes::PortType_In)
        _nodePortCounts[nodeId].in++;
    else
        _nodePortCounts[nodeId].out++;

    // STAGE 3. Re-create previouly existed and now shifted connections
    portsInserted();

    Q_EMIT nodeUpdated(nodeId);
}

void DynamicPortsModel::removePort(QExtBPTypes::NodeId nodeId, QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex)
{
    // STAGE 1.
    // Compute new addresses for the existing connections that are shifted upwards
    // instead of the deleted ports.
    QExtBPTypes::PortIndex first = portIndex;
    QExtBPTypes::PortIndex last = first;
    portsAboutToBeDeleted(nodeId, portType, first, last);

    // STAGE 2. Change the number of connections in your model
    if (portType == QExtBPTypes::PortType_In)
        _nodePortCounts[nodeId].in--;
    else
        _nodePortCounts[nodeId].out--;

    portsDeleted();

    Q_EMIT nodeUpdated(nodeId);
}
