#include <private/qextBPDataFlowGraphModel_p.h>
#include <qextBPConnectionIdHash.h>

#include <QJsonArray>

#include <stdexcept>

QExtBPDataFlowGraphModelPrivate::QExtBPDataFlowGraphModelPrivate(QExtBPDataFlowGraphModel *q)
    : QExtBPAbstractGraphModelPrivate(q)
{
}

QExtBPDataFlowGraphModelPrivate::~QExtBPDataFlowGraphModelPrivate()
{
}

QExtBPDataFlowGraphModel::QExtBPDataFlowGraphModel(QExtSharedPointer<QExtBPNodeDelegateModelRegistry> registry, QObject *parent)
    : QExtBPAbstractGraphModel(new QExtBPDataFlowGraphModelPrivate(this), parent)
{
    Q_D(QExtBPDataFlowGraphModel);
    d->m_registry = registry;
    d->m_nextNodeId = 0;
}

QExtBPDataFlowGraphModel::~QExtBPDataFlowGraphModel()
{
}

QExtSharedPointer<QExtBPNodeDelegateModelRegistry> QExtBPDataFlowGraphModel::dataModelRegistry()
{
    Q_D(QExtBPDataFlowGraphModel);
    return d->m_registry;
}

std::unordered_set<QExtBPTypes::NodeId> QExtBPDataFlowGraphModel::allNodeIds() const
{
    Q_D(const QExtBPDataFlowGraphModel);
    std::unordered_set<QExtBPTypes::NodeId> nodeIds;
    for (auto &&model : d->m_models)
    {
        nodeIds.insert(model.first);
    }
    return nodeIds;
}

std::unordered_set<QExtBPTypes::ConnectionId> QExtBPDataFlowGraphModel::allConnectionIds(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDataFlowGraphModel);
    std::unordered_set<QExtBPTypes::ConnectionId> result;
    // std::unordered_set<QExtBPTypes::ConnectionId>::ConstIterator iter;
    // for (iter = _connectivity.begin(); iter != _connectivity.end(); ++iter)
    // {
    //     if ((*iter).inNodeId == nodeId || (*iter).outNodeId == nodeId)
    //     {
    //         result.insert((*iter));
    //     }
    // }
    std::copy_if(d->m_connectivity.begin(),
                 d->m_connectivity.end(),
                 std::inserter(result, std::end(result)),
                 [&nodeId](const QExtBPTypes::ConnectionId &cid)
                 {
                     return cid.inNodeId == nodeId || cid.outNodeId == nodeId;
                 });

    return result;
}

std::unordered_set<QExtBPTypes::ConnectionId> QExtBPDataFlowGraphModel::connections(QExtBPTypes::NodeId nodeId,
                                                                                    QExtBPTypes::PortTypeEnum portType,
                                                                                    QExtBPTypes::PortIndex portIndex) const
{
    Q_D(const QExtBPDataFlowGraphModel);
    std::unordered_set<QExtBPTypes::ConnectionId> result;
    // std::unordered_set<QExtBPTypes::ConnectionId>::ConstIterator iter;
    // for (iter = _connectivity.begin(); iter != _connectivity.end(); ++iter)
    // {
    //     const QExtBPTypes::ConnectionId &cid = (*iter);
    //     if (QExtBPUtils::getNodeId(portType, cid) == nodeId && QExtBPUtils::getPortIndex(portType, cid) == portIndex)
    //     {
    //         result.insert((*iter));
    //     }
    // }
    std::copy_if(d->m_connectivity.begin(),
                 d->m_connectivity.end(),
                 std::inserter(result, std::end(result)),
                 [&portType, &portIndex, &nodeId](const QExtBPTypes::ConnectionId &cid)
                 {
                     return (QExtBPUtils::getNodeId(portType, cid) == nodeId
                             && QExtBPUtils::getPortIndex(portType, cid) == portIndex);
                 });

    return result;
}

bool QExtBPDataFlowGraphModel::connectionExists(const QExtBPTypes::ConnectionId connectionId) const
{
    Q_D(const QExtBPDataFlowGraphModel);
    return (d->m_connectivity.find(connectionId) != d->m_connectivity.end());
}

QExtBPTypes::NodeId QExtBPDataFlowGraphModel::addNode(QString const nodeType)
{
    Q_D(QExtBPDataFlowGraphModel);
    QScopedPointer<QExtBPNodeDelegateModel> model(d->m_registry->create(nodeType));

    if (model)
    {
        QExtBPTypes::NodeId newId = newNodeId();

        connect(model.get(),
                &QExtBPNodeDelegateModel::dataUpdated, this,
                [newId, this](const QExtBPTypes::PortIndex portIndex)
                {
                    onOutPortDataUpdated(newId, portIndex);
                });

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsAboutToBeDeleted,
                this,
                [newId, this](const QExtBPTypes::PortTypeEnum portType, const QExtBPTypes::PortIndex first, const QExtBPTypes::PortIndex last) {
                    portsAboutToBeDeleted(newId, portType, first, last);
                });

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsDeleted,
                this,
                &QExtBPDataFlowGraphModel::portsDeleted);

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsAboutToBeInserted,
                this,
                [newId, this](const QExtBPTypes::PortTypeEnum portType, const QExtBPTypes::PortIndex first, const QExtBPTypes::PortIndex last) {
                    portsAboutToBeInserted(newId, portType, first, last);
                });

        connect(model.get(),
                &QExtBPNodeDelegateModel::portsInserted,
                this,
                &QExtBPDataFlowGraphModel::portsInserted);

        d->m_models[newId].swap(model);

        Q_EMIT this->nodeCreated(newId);

        return newId;
    }

    return QExtBPTypes::InvalidNodeId;
}

bool QExtBPDataFlowGraphModel::connectionPossible(const QExtBPTypes::ConnectionId connectionId) const
{
    auto getDataType = [&](const QExtBPTypes::PortTypeEnum portType)
    {
        return portData(QExtBPUtils::getNodeId(portType, connectionId),
                        portType,
                        QExtBPUtils::getPortIndex(portType, connectionId),
                        QExtBPTypes::PortRole_DataType)
            .value<QExtBPNodeDataType>();
    };

    auto portVacant = [&](const QExtBPTypes::PortTypeEnum portType) {
        const QExtBPTypes::NodeId nodeId = QExtBPUtils::getNodeId(portType, connectionId);
        const QExtBPTypes::PortIndex portIndex = QExtBPUtils::getPortIndex(portType, connectionId);
        auto const connected = connections(nodeId, portType, portIndex);

        auto policy = portData(nodeId, portType, portIndex, QExtBPTypes::PortRole_ConnectionPolicyRole)
                          .value<QExtBPTypes::ConnectionPolicyEnum>();

        return connected.empty() || (policy == QExtBPTypes::ConnectionPolicy_Many);
    };

    return getDataType(QExtBPTypes::PortType_Out).id == getDataType(QExtBPTypes::PortType_In).id
           && portVacant(QExtBPTypes::PortType_Out) && portVacant(QExtBPTypes::PortType_In);
}

void QExtBPDataFlowGraphModel::addConnection(const QExtBPTypes::ConnectionId connectionId)
{
    Q_D(QExtBPDataFlowGraphModel);
    d->m_connectivity.insert(connectionId);

    this->sendConnectionCreation(connectionId);

    QVariant const portDataToPropagate = portData(connectionId.outNodeId,
                                                  QExtBPTypes::PortType_Out,
                                                  connectionId.outPortIndex,
                                                  QExtBPTypes::PortRole_Data);

    this->setPortData(connectionId.inNodeId,
                      QExtBPTypes::PortType_In,
                      connectionId.inPortIndex,
                      portDataToPropagate,
                      QExtBPTypes::PortRole_Data);
}

void QExtBPDataFlowGraphModel::sendConnectionCreation(const QExtBPTypes::ConnectionId connectionId)
{
    Q_D(QExtBPDataFlowGraphModel);
    Q_EMIT this->connectionCreated(connectionId);

    auto iti = d->m_models.find(connectionId.inNodeId);
    auto ito = d->m_models.find(connectionId.outNodeId);
    if (iti != d->m_models.end() && ito != d->m_models.end())
    {
        auto &modeli = iti->second;
        auto &modelo = ito->second;
        modeli->inputConnectionCreated(connectionId);
        modelo->outputConnectionCreated(connectionId);
    }
}

void QExtBPDataFlowGraphModel::sendConnectionDeletion(const QExtBPTypes::ConnectionId connectionId)
{
    Q_D(QExtBPDataFlowGraphModel);
    Q_EMIT this->connectionDeleted(connectionId);

    auto iti = d->m_models.find(connectionId.inNodeId);
    auto ito = d->m_models.find(connectionId.outNodeId);
    if (iti != d->m_models.end() && ito != d->m_models.end())
    {
        auto &modeli = iti->second;
        auto &modelo = ito->second;
        modeli->inputConnectionDeleted(connectionId);
        modelo->outputConnectionDeleted(connectionId);
    }
}

std::unordered_map<QExtBPTypes::NodeId, QScopedPointer<QExtBPNodeDelegateModel> > &QExtBPDataFlowGraphModel::models()
{
    Q_D(QExtBPDataFlowGraphModel);
    return d->m_models;
}

bool QExtBPDataFlowGraphModel::nodeExists(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDataFlowGraphModel);
    return (d->m_models.find(nodeId) != d->m_models.end());
}

QVariant QExtBPDataFlowGraphModel::nodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role) const
{
    Q_D(const QExtBPDataFlowGraphModel);
    QVariant result;

    auto it = d->m_models.find(nodeId);
    if (it == d->m_models.end())
    {
        return result;
    }

    auto &model = it->second;

    switch (role)
    {
    case QExtBPTypes::NodeRole_Type:
    {
        result = model->name();
        break;
    }
    case QExtBPTypes::NodeRole_Position:
    {
        result = d->m_nodeGeometryData[nodeId].pos;
        break;
    }
    case QExtBPTypes::NodeRole_Size:
    {
        result = d->m_nodeGeometryData[nodeId].size;
        break;
    }
    case QExtBPTypes::NodeRole_CaptionVisible:
    {
        result = model->captionVisible();
        break;
    }
    case QExtBPTypes::NodeRole_Caption:
    {
        result = model->caption();
        break;
    }
    case QExtBPTypes::NodeRole_Style:
    {
        auto style = QExtBPStyleCollection::nodeStyle();
        result = style.toJson().toVariantMap();
        break;
    }
    case QExtBPTypes::NodeRole_InternalData:
    {
        QJsonObject nodeJson;
        nodeJson["internal-data"] = d->m_models.at(nodeId)->save();
        result = nodeJson.toVariantMap();
        break;
    }
    case QExtBPTypes::NodeRole_InPortCount:
    {
        result = model->nPorts(QExtBPTypes::PortType_In);
        break;
    }
    case QExtBPTypes::NodeRole_OutPortCount:
    {
        result = model->nPorts(QExtBPTypes::PortType_Out);
        break;
    }
    case QExtBPTypes::NodeRole_Widget:
    {
        auto w = model->embeddedWidget();
        result = QVariant::fromValue(w);
    } break;
    }

    return result;
}

QExtBPTypes::NodeFlagEnums QExtBPDataFlowGraphModel::nodeFlags(QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDataFlowGraphModel);
    auto it = d->m_models.find(nodeId);

    if (it != d->m_models.end() && it->second->resizable())
    {
        return QExtBPTypes::NodeFlag_Resizable;
    }

    return QExtBPTypes::NodeFlag_NoFlags;
}

bool QExtBPDataFlowGraphModel::setNodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role, QVariant value)
{
    Q_UNUSED(nodeId);
    Q_UNUSED(role);
    Q_UNUSED(value);
    Q_D(QExtBPDataFlowGraphModel);

    bool result = false;

    switch (role)
    {
    case QExtBPTypes::NodeRole_Type:
        break;
    case QExtBPTypes::NodeRole_Position:
    {
        d->m_nodeGeometryData[nodeId].pos = value.value<QPointF>();
        Q_EMIT this->nodePositionUpdated(nodeId);
        result = true;
        break;
    }
    case QExtBPTypes::NodeRole_Size:
    {
        d->m_nodeGeometryData[nodeId].size = value.value<QSize>();
        result = true;
        break;
    }
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
    Q_D(const QExtBPDataFlowGraphModel);
    QVariant result;

    auto it = d->m_models.find(nodeId);
    if (it == d->m_models.end())
    {
        return result;
    }

    auto &model = it->second;

    switch (role)
    {
    case QExtBPTypes::PortRole_Data:
    {
        if (portType == QExtBPTypes::PortType_Out)
        {
            result = QVariant::fromValue(model->outData(portIndex));
        }
        break;
    }
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

bool QExtBPDataFlowGraphModel::setPortData(QExtBPTypes::NodeId nodeId,
                                           QExtBPTypes::PortTypeEnum portType,
                                           QExtBPTypes::PortIndex portIndex,
                                           const QVariant &value,
                                           QExtBPTypes::PortRoleEnum role)
{
    Q_UNUSED(nodeId);
    Q_D(QExtBPDataFlowGraphModel);

    QVariant result;

    auto it = d->m_models.find(nodeId);
    if (it == d->m_models.end())
    {
        return false;
    }

    auto &model = it->second;

    switch (role)
    {
    case QExtBPTypes::PortRole_Data:
    {
        if (portType == QExtBPTypes::PortType_In)
        {
            model->setInData(value.value<QExtSharedPointer<QExtBPNodeData>>(), portIndex);
            // Triggers repainting on the scene.
            Q_EMIT this->inPortDataWasSet(nodeId, portType, portIndex);
        }
        break;
    }
    default:
        break;
    }
    return false;
}

bool QExtBPDataFlowGraphModel::deleteConnection(const QExtBPTypes::ConnectionId connectionId)
{
    Q_D(QExtBPDataFlowGraphModel);
    bool disconnected = false;

    auto it = d->m_connectivity.find(connectionId);

    if (it != d->m_connectivity.end())
    {
        disconnected = true;

        d->m_connectivity.erase(it);
    }

    if (disconnected)
    {
        this->sendConnectionDeletion(connectionId);

        this->propagateEmptyDataTo(QExtBPUtils::getNodeId(QExtBPTypes::PortType_In, connectionId),
                                   QExtBPUtils::getPortIndex(QExtBPTypes::PortType_In, connectionId));
    }

    return disconnected;
}

bool QExtBPDataFlowGraphModel::deleteNode(const QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPDataFlowGraphModel);
    // Delete connections to this node first.
    auto connectionIds = this->allConnectionIds(nodeId);
    for (auto &cId : connectionIds)
    {
        this->deleteConnection(cId);
    }

    d->m_nodeGeometryData.erase(nodeId);
    d->m_models.erase(nodeId);

    Q_EMIT this->nodeDeleted(nodeId);
    return true;
}

QJsonObject QExtBPDataFlowGraphModel::saveNode(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDataFlowGraphModel);
    QJsonObject nodeJson;

    nodeJson["id"] = static_cast<qint64>(nodeId);

    nodeJson["internal-data"] = d->m_models.at(nodeId)->save();

    {
        const QPointF pos = this->nodeData(nodeId, QExtBPTypes::NodeRole_Position).value<QPointF>();

        QJsonObject posJson;
        posJson["x"] = pos.x();
        posJson["y"] = pos.y();
        nodeJson["position"] = posJson;
    }

    return nodeJson;
}

QJsonObject QExtBPDataFlowGraphModel::save() const
{
    Q_D(const QExtBPDataFlowGraphModel);
    QJsonObject sceneJson;

    QJsonArray nodesJsonArray;
    for (const auto nodeId : allNodeIds())
    {
        nodesJsonArray.append(saveNode(nodeId));
    }
    sceneJson["nodes"] = nodesJsonArray;

    QJsonArray connJsonArray;
    for (const auto &cid : d->m_connectivity)
    {
        connJsonArray.append(QExtBPUtils::toJson(cid));
    }
    sceneJson["connections"] = connJsonArray;

    return sceneJson;
}

void QExtBPDataFlowGraphModel::loadNode(const QJsonObject &nodeJson)
{
    Q_D(QExtBPDataFlowGraphModel);
    // Possibility of the id clash when reading it from json and not generating a
    // new value.
    // 1. When restoring a scene from a file.
    // Conflict is not possible because the scene must be cleared by the time of
    // loading.
    // 2. When undoing the deletion command.  Conflict is not possible
    // because all the new ids were created past the removed nodes.
    QExtBPTypes::NodeId restoredNodeId = nodeJson["id"].toInt();

    d->m_nextNodeId = std::max(d->m_nextNodeId, restoredNodeId + 1);

    QJsonObject const internalDataJson = nodeJson["internal-data"].toObject();

    QString delegateModelName = internalDataJson["model-name"].toString();

    QScopedPointer<QExtBPNodeDelegateModel> model(d->m_registry->create(delegateModelName));

    if (model)
    {
        connect(model.get(),
                &QExtBPNodeDelegateModel::dataUpdated,
                [restoredNodeId, this](const QExtBPTypes::PortIndex portIndex)
                {
                    onOutPortDataUpdated(restoredNodeId, portIndex);
                });

        d->m_models[restoredNodeId].swap(model);

        Q_EMIT this->nodeCreated(restoredNodeId);

        QJsonObject posJson = nodeJson["position"].toObject();
        const QPointF pos(posJson["x"].toDouble(), posJson["y"].toDouble());

        setNodeData(restoredNodeId, QExtBPTypes::NodeRole_Position, pos);

        d->m_models[restoredNodeId]->load(internalDataJson);
    }
    else
    {
        throw std::logic_error(std::string("No registered model with name ") + delegateModelName.toLocal8Bit().data());
    }
}

void QExtBPDataFlowGraphModel::load(const QJsonObject &jsonDocument)
{
    QJsonArray nodesJsonArray = jsonDocument["nodes"].toArray();

    for (QJsonValueRef nodeJson : nodesJsonArray)
    {
        this->loadNode(nodeJson.toObject());
    }

    QJsonArray connectionJsonArray = jsonDocument["connections"].toArray();

    for (QJsonValueRef connection : connectionJsonArray)
    {
        QJsonObject connJson = connection.toObject();

        QExtBPTypes::ConnectionId connId = QExtBPUtils::fromJson(connJson);

        // Restore the connection
        this->addConnection(connId);
    }
}

void QExtBPDataFlowGraphModel::onOutPortDataUpdated(const QExtBPTypes::NodeId nodeId,
                                                    const QExtBPTypes::PortIndex portIndex)
{
    const std::unordered_set<QExtBPTypes::ConnectionId> &connected = connections(nodeId,
                                                                                 QExtBPTypes::PortType_Out,
                                                                                 portIndex);

    const QVariant portDataToPropagate = this->portData(nodeId, QExtBPTypes::PortType_Out,
                                                        portIndex, QExtBPTypes::PortRole_Data);

    for (const auto &cn : connected)
    {
        this->setPortData(cn.inNodeId, QExtBPTypes::PortType_In,
                          cn.inPortIndex, portDataToPropagate, QExtBPTypes::PortRole_Data);
    }
}

void QExtBPDataFlowGraphModel::propagateEmptyDataTo(const QExtBPTypes::NodeId nodeId,
                                                    const QExtBPTypes::PortIndex portIndex)
{
    QVariant emptyData;

    this->setPortData(nodeId, QExtBPTypes::PortType_In, portIndex, emptyData, QExtBPTypes::PortRole_Data);
}

QExtBPTypes::NodeId QExtBPDataFlowGraphModel::newNodeId()
{
    Q_D(QExtBPDataFlowGraphModel);
    return d->m_nextNodeId++;
}
