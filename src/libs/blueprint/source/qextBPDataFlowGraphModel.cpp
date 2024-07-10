#include <qextBPDataFlowGraphModel.h>
#include <qextBPConnectionIdHash.h>

#include <QJsonArray>

#include <stdexcept>

QExtBPDataFlowGraphModel::QExtBPDataFlowGraphModel(std::shared_ptr<QExtBPNodeDelegateModelRegistry> registry)
    : _registry(std::move(registry))
    , _nextNodeId{0}
{}

std::unordered_set<QExtBPTypes::NodeId> QExtBPDataFlowGraphModel::allNodeIds() const
{
    std::unordered_set<QExtBPTypes::NodeId> nodeIds;
    for (auto &&model : _models)
    {
        nodeIds.insert(model.first);
    }
    return nodeIds;
}

std::unordered_set<QExtBPTypes::ConnectionId> QExtBPDataFlowGraphModel::allConnectionIds(QExtBPTypes::NodeId const nodeId) const
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

std::unordered_set<QExtBPTypes::ConnectionId> QExtBPDataFlowGraphModel::connections(QExtBPTypes::NodeId nodeId,
                                                                                    QExtBPTypes::PortTypeEnum portType,
                                                                                    QExtBPTypes::PortIndex portIndex) const
{
    std::unordered_set<QExtBPTypes::ConnectionId> result;

    std::copy_if(_connectivity.begin(),
                 _connectivity.end(),
                 std::inserter(result, std::end(result)),
                 [&portType, &portIndex, &nodeId](QExtBPTypes::ConnectionId const &cid) {
        return (QExtBPUtils::getNodeId(portType, cid) == nodeId
                && QExtBPUtils::getPortIndex(portType, cid) == portIndex);
    });

    return result;
}

bool QExtBPDataFlowGraphModel::connectionExists(QExtBPTypes::ConnectionId const connectionId) const
{
    return (_connectivity.find(connectionId) != _connectivity.end());
}

QExtBPTypes::NodeId QExtBPDataFlowGraphModel::addNode(QString const nodeType)
{
    QScopedPointer<QExtBPNodeDelegateModel> model(_registry->create(nodeType));

    if (model) {
        QExtBPTypes::NodeId newId = newNodeId();

        connect(model.get(),
                &QExtBPNodeDelegateModel::dataUpdated,
                [newId, this](QExtBPTypes::PortIndex const portIndex) {
            onOutPortDataUpdated(newId, portIndex);
        });

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsAboutToBeDeleted,
                this,
                [newId, this](QExtBPTypes::PortTypeEnum const portType, QExtBPTypes::PortIndex const first, QExtBPTypes::PortIndex const last) {
            portsAboutToBeDeleted(newId, portType, first, last);
        });

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsDeleted,
                this,
                &QExtBPDataFlowGraphModel::portsDeleted);

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsAboutToBeInserted,
                this,
                [newId, this](QExtBPTypes::PortTypeEnum const portType, QExtBPTypes::PortIndex const first, QExtBPTypes::PortIndex const last) {
            portsAboutToBeInserted(newId, portType, first, last);
        });

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsInserted,
                this,
                &QExtBPDataFlowGraphModel::portsInserted);

        _models[newId].swap(model);

        Q_EMIT nodeCreated(newId);

        return newId;
    }

    return QExtBPTypes::InvalidNodeId;
}

bool QExtBPDataFlowGraphModel::connectionPossible(QExtBPTypes::ConnectionId const connectionId) const
{
    auto getDataType = [&](QExtBPTypes::PortTypeEnum const portType) {
        return portData(QExtBPUtils::getNodeId(portType, connectionId),
                        portType,
                        QExtBPUtils::getPortIndex(portType, connectionId),
                        QExtBPTypes::PortRole_DataType)
                .value<QExtBPNodeDataType>();
    };

    auto portVacant = [&](QExtBPTypes::PortTypeEnum const portType) {
        QExtBPTypes::NodeId const nodeId = QExtBPUtils::getNodeId(portType, connectionId);
        QExtBPTypes::PortIndex const portIndex = QExtBPUtils::getPortIndex(portType, connectionId);
        auto const connected = connections(nodeId, portType, portIndex);

        auto policy = portData(nodeId, portType, portIndex, QExtBPTypes::PortRole_ConnectionPolicyRole)
                .value<QExtBPTypes::ConnectionPolicyEnum>();

        return connected.empty() || (policy == QExtBPTypes::ConnectionPolicy_Many);
    };

    return getDataType(QExtBPTypes::PortType_Out).id == getDataType(QExtBPTypes::PortType_In).id
            && portVacant(QExtBPTypes::PortType_Out) && portVacant(QExtBPTypes::PortType_In);
}

void QExtBPDataFlowGraphModel::addConnection(QExtBPTypes::ConnectionId const connectionId)
{
    _connectivity.insert(connectionId);

    sendConnectionCreation(connectionId);

    QVariant const portDataToPropagate = portData(connectionId.outNodeId,
                                                  QExtBPTypes::PortType_Out,
                                                  connectionId.outPortIndex,
                                                  QExtBPTypes::PortRole_Data);

    setPortData(connectionId.inNodeId,
                QExtBPTypes::PortType_In,
                connectionId.inPortIndex,
                portDataToPropagate,
                QExtBPTypes::PortRole_Data);
}

void QExtBPDataFlowGraphModel::sendConnectionCreation(QExtBPTypes::ConnectionId const connectionId)
{
    Q_EMIT connectionCreated(connectionId);

    auto iti = _models.find(connectionId.inNodeId);
    auto ito = _models.find(connectionId.outNodeId);
    if (iti != _models.end() && ito != _models.end()) {
        auto &modeli = iti->second;
        auto &modelo = ito->second;
        modeli->inputConnectionCreated(connectionId);
        modelo->outputConnectionCreated(connectionId);
    }
}

void QExtBPDataFlowGraphModel::sendConnectionDeletion(QExtBPTypes::ConnectionId const connectionId)
{
    Q_EMIT connectionDeleted(connectionId);

    auto iti = _models.find(connectionId.inNodeId);
    auto ito = _models.find(connectionId.outNodeId);
    if (iti != _models.end() && ito != _models.end()) {
        auto &modeli = iti->second;
        auto &modelo = ito->second;
        modeli->inputConnectionDeleted(connectionId);
        modelo->outputConnectionDeleted(connectionId);
    }
}

bool QExtBPDataFlowGraphModel::nodeExists(QExtBPTypes::NodeId const nodeId) const
{
    return (_models.find(nodeId) != _models.end());
}

QVariant QExtBPDataFlowGraphModel::nodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role) const
{
    QVariant result;

    auto it = _models.find(nodeId);
    if (it == _models.end())
        return result;

    auto &model = it->second;

    switch (role) {
    case QExtBPTypes::NodeRole_Type:
        result = model->name();
        break;

    case QExtBPTypes::NodeRole_Position:
        result = _nodeGeometryData[nodeId].pos;
        break;

    case QExtBPTypes::NodeRole_Size:
        result = _nodeGeometryData[nodeId].size;
        break;

    case QExtBPTypes::NodeRole_CaptionVisible:
        result = model->captionVisible();
        break;

    case QExtBPTypes::NodeRole_Caption:
        result = model->caption();
        break;

    case QExtBPTypes::NodeRole_Style: {
        auto style = QExtBPStyleCollection::nodeStyle();
        result = style.toJson().toVariantMap();
    } break;

    case QExtBPTypes::NodeRole_InternalData: {
        QJsonObject nodeJson;

        nodeJson["internal-data"] = _models.at(nodeId)->save();

        result = nodeJson.toVariantMap();
        break;
    }

    case QExtBPTypes::NodeRole_InPortCount:
        result = model->nPorts(QExtBPTypes::PortType_In);
        break;

    case QExtBPTypes::NodeRole_OutPortCount:
        result = model->nPorts(QExtBPTypes::PortType_Out);
        break;

    case QExtBPTypes::NodeRole_Widget: {
        auto w = model->embeddedWidget();
        result = QVariant::fromValue(w);
    } break;
    }

    return result;
}

QExtBPTypes::NodeFlagEnums QExtBPDataFlowGraphModel::nodeFlags(QExtBPTypes::NodeId nodeId) const
{
    auto it = _models.find(nodeId);

    if (it != _models.end() && it->second->resizable())
        return QExtBPTypes::NodeFlag_Resizable;

    return QExtBPTypes::NodeFlag_NoFlags;
}

bool QExtBPDataFlowGraphModel::setNodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role, QVariant value)
{
    Q_UNUSED(nodeId);
    Q_UNUSED(role);
    Q_UNUSED(value);

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

QVariant QExtBPDataFlowGraphModel::portData(QExtBPTypes::NodeId nodeId,
                                            QExtBPTypes::PortTypeEnum portType,
                                            QExtBPTypes::PortIndex portIndex,
                                            QExtBPTypes::PortRoleEnum role) const
{
    QVariant result;

    auto it = _models.find(nodeId);
    if (it == _models.end())
        return result;

    auto &model = it->second;

    switch (role) {
    case QExtBPTypes::PortRole_Data:
        if (portType == QExtBPTypes::PortType_Out)
            result = QVariant::fromValue(model->outData(portIndex));
        break;

    case QExtBPTypes::PortRole_DataType:
        result = QVariant::fromValue(model->dataType(portType, portIndex));
        break;

    case QExtBPTypes::PortRole_ConnectionPolicyRole:
        result = QVariant::fromValue(model->portConnectionPolicy(portType, portIndex));
        break;

    case QExtBPTypes::PortRole_CaptionVisible:
        result = model->portCaptionVisible(portType, portIndex);
        break;

    case QExtBPTypes::PortRole_Caption:
        result = model->portCaption(portType, portIndex);

        break;
    }

    return result;
}

bool QExtBPDataFlowGraphModel::setPortData(
        QExtBPTypes::NodeId nodeId, QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex, QVariant const &value, QExtBPTypes::PortRoleEnum role)
{
    Q_UNUSED(nodeId);

    QVariant result;

    auto it = _models.find(nodeId);
    if (it == _models.end())
        return false;

    auto &model = it->second;

    switch (role) {
    case QExtBPTypes::PortRole_Data:
        if (portType == QExtBPTypes::PortType_In) {
            model->setInData(value.value<std::shared_ptr<QExtBPNodeData>>(), portIndex);

            // Triggers repainting on the scene.
            Q_EMIT inPortDataWasSet(nodeId, portType, portIndex);
        }
        break;

    default:
        break;
    }

    return false;
}

bool QExtBPDataFlowGraphModel::deleteConnection(QExtBPTypes::ConnectionId const connectionId)
{
    bool disconnected = false;

    auto it = _connectivity.find(connectionId);

    if (it != _connectivity.end()) {
        disconnected = true;

        _connectivity.erase(it);
    }

    if (disconnected) {
        sendConnectionDeletion(connectionId);

        propagateEmptyDataTo(QExtBPUtils::getNodeId(QExtBPTypes::PortType_In, connectionId),
                             QExtBPUtils::getPortIndex(QExtBPTypes::PortType_In, connectionId));
    }

    return disconnected;
}

bool QExtBPDataFlowGraphModel::deleteNode(QExtBPTypes::NodeId const nodeId)
{
    // Delete connections to this node first.
    auto connectionIds = allConnectionIds(nodeId);
    for (auto &cId : connectionIds) {
        deleteConnection(cId);
    }

    _nodeGeometryData.erase(nodeId);
    _models.erase(nodeId);

    Q_EMIT nodeDeleted(nodeId);

    return true;
}

QJsonObject QExtBPDataFlowGraphModel::saveNode(QExtBPTypes::NodeId const nodeId) const
{
    QJsonObject nodeJson;

    nodeJson["id"] = static_cast<qint64>(nodeId);

    nodeJson["internal-data"] = _models.at(nodeId)->save();

    {
        QPointF const pos = nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>();

        QJsonObject posJson;
        posJson["x"] = pos.x();
        posJson["y"] = pos.y();
        nodeJson["position"] = posJson;
    }

    return nodeJson;
}

QJsonObject QExtBPDataFlowGraphModel::save() const
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

void QExtBPDataFlowGraphModel::loadNode(QJsonObject const &nodeJson)
{
    // Possibility of the id clash when reading it from json and not generating a
    // new value.
    // 1. When restoring a scene from a file.
    // Conflict is not possible because the scene must be cleared by the time of
    // loading.
    // 2. When undoing the deletion command.  Conflict is not possible
    // because all the new ids were created past the removed nodes.
    QExtBPTypes::NodeId restoredNodeId = nodeJson["id"].toInt();

    _nextNodeId = std::max(_nextNodeId, restoredNodeId + 1);

    QJsonObject const internalDataJson = nodeJson["internal-data"].toObject();

    QString delegateModelName = internalDataJson["model-name"].toString();

    QScopedPointer<QExtBPNodeDelegateModel> model(_registry->create(delegateModelName));

    if (model) {
        connect(model.get(),
                &QExtBPNodeDelegateModel::dataUpdated,
                [restoredNodeId, this](QExtBPTypes::PortIndex const portIndex) {
            onOutPortDataUpdated(restoredNodeId, portIndex);
        });

        _models[restoredNodeId].swap(model);

        Q_EMIT nodeCreated(restoredNodeId);

        QJsonObject posJson = nodeJson["position"].toObject();
        QPointF const pos(posJson["x"].toDouble(), posJson["y"].toDouble());

        setNodeData(restoredNodeId, QExtBPTypes::NodeRole_Position, pos);

        _models[restoredNodeId]->load(internalDataJson);
    } else {
        throw std::logic_error(std::string("No registered model with name ")
                               + delegateModelName.toLocal8Bit().data());
    }
}

void QExtBPDataFlowGraphModel::load(QJsonObject const &jsonDocument)
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

void QExtBPDataFlowGraphModel::onOutPortDataUpdated(QExtBPTypes::NodeId const nodeId, QExtBPTypes::PortIndex const portIndex)
{
    std::unordered_set<QExtBPTypes::ConnectionId> const &connected = connections(nodeId,
                                                                                 QExtBPTypes::PortType_Out,
                                                                                 portIndex);

    QVariant const portDataToPropagate = portData(nodeId, QExtBPTypes::PortType_Out, portIndex, QExtBPTypes::PortRole_Data);

    for (auto const &cn : connected) {
        setPortData(cn.inNodeId, QExtBPTypes::PortType_In, cn.inPortIndex, portDataToPropagate, QExtBPTypes::PortRole_Data);
    }
}

void QExtBPDataFlowGraphModel::propagateEmptyDataTo(QExtBPTypes::NodeId const nodeId, QExtBPTypes::PortIndex const portIndex)
{
    QVariant emptyData{};

    setPortData(nodeId, QExtBPTypes::PortType_In, portIndex, emptyData, QExtBPTypes::PortRole_Data);
}
