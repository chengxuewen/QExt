#ifndef _QEXTBPDATAFLOWGRAPHICSMODEL_H
#define _QEXTBPDATAFLOWGRAPHICSMODEL_H

#include <qextBPAbstractGraphModel.h>
#include <qextBPNodeDelegateModelRegistry.h>
#include <qextBPStyleCollection.h>
#include <qextBlueprintGlobal.h>
#include <qextBPSerializable.h>
#include <qextBPUtils.h>

#include <QJsonObject>

#include <memory>


class QEXT_BLUEPRINT_API QExtBPDataFlowGraphModel : public QExtBPAbstractGraphModel, public QExtBPSerializable
{
    Q_OBJECT

public:
    struct NodeGeometryData
    {
        QSize size;
        QPointF pos;
    };

public:
    QExtBPDataFlowGraphModel(QSharedPointer<QExtBPNodeDelegateModelRegistry> registry);

    QSharedPointer<QExtBPNodeDelegateModelRegistry> dataModelRegistry() { return _registry; }

public:
    std::unordered_set<QExtBPTypes::NodeId> allNodeIds() const override;

    std::unordered_set<QExtBPTypes::ConnectionId> allConnectionIds(QExtBPTypes::NodeId const nodeId) const override;

    std::unordered_set<QExtBPTypes::ConnectionId> connections(QExtBPTypes::NodeId nodeId,
                                                              QExtBPTypes::PortTypeEnum portType,
                                                              QExtBPTypes::PortIndex portIndex) const override;

    bool connectionExists(QExtBPTypes::ConnectionId const connectionId) const override;

    QExtBPTypes::NodeId addNode(QString const nodeType) override;

    bool connectionPossible(QExtBPTypes::ConnectionId const connectionId) const override;

    void addConnection(QExtBPTypes::ConnectionId const connectionId) override;

    bool nodeExists(QExtBPTypes::NodeId const nodeId) const override;

    QVariant nodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role) const override;

    QExtBPTypes::NodeFlagEnums nodeFlags(QExtBPTypes::NodeId nodeId) const override;

    bool setNodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role, QVariant value) override;

    QVariant portData(QExtBPTypes::NodeId nodeId,
                      QExtBPTypes::PortTypeEnum portType,
                      QExtBPTypes::PortIndex portIndex,
                      QExtBPTypes::PortRoleEnum role) const override;

    bool setPortData(QExtBPTypes::NodeId nodeId,
                     QExtBPTypes::PortTypeEnum portType,
                     QExtBPTypes::PortIndex portIndex,
                     QVariant const &value,
                     QExtBPTypes::PortRoleEnum role = QExtBPTypes::PortRole_Data) override;

    bool deleteConnection(QExtBPTypes::ConnectionId const connectionId) override;

    bool deleteNode(QExtBPTypes::NodeId const nodeId) override;

    QJsonObject saveNode(QExtBPTypes::NodeId const) const override;

    QJsonObject save() const override;

    void loadNode(QJsonObject const &nodeJson) override;

    void load(QJsonObject const &json) override;

    /**
   * Fetches the NodeDelegateModel for the given `nodeId` and tries to cast the
   * stored pointer to the given type
   */
    template<typename NodeDelegateModelType>
    NodeDelegateModelType *delegateModel(QExtBPTypes::NodeId const nodeId)
    {
        auto it = _models.find(nodeId);
        if (it == _models.end())
            return QEXT_NULLPTR;

        auto model = dynamic_cast<NodeDelegateModelType *>(it->second.get());

        return model;
    }

Q_SIGNALS:
    void inPortDataWasSet(QExtBPTypes::NodeId const, QExtBPTypes::PortTypeEnum const, QExtBPTypes::PortIndex const);

private:
    QExtBPTypes::NodeId newNodeId() override { return _nextNodeId++; }

    void sendConnectionCreation(QExtBPTypes::ConnectionId const connectionId);

    void sendConnectionDeletion(QExtBPTypes::ConnectionId const connectionId);

private Q_SLOTS:
    /**
   * Fuction is called in three cases:
   *
   * - By underlying NodeDelegateModel when a node has new data to propagate.
   *   @see DataFlowGraphModel::addNode
   * - When a new connection is created.
   *   @see DataFlowGraphModel::addConnection
   * - When a node restored from JSON an needs to send data downstream.
   *   @see DataFlowGraphModel::loadNode
   */
    void onOutPortDataUpdated(QExtBPTypes::NodeId const nodeId, QExtBPTypes::PortIndex const portIndex);

    /// Function is called after detaching a connection.
    void propagateEmptyDataTo(QExtBPTypes::NodeId const nodeId, QExtBPTypes::PortIndex const portIndex);

private:
    QSharedPointer<QExtBPNodeDelegateModelRegistry> _registry;

    QExtBPTypes::NodeId _nextNodeId;

    std::unordered_map<QExtBPTypes::NodeId, QScopedPointer<QExtBPNodeDelegateModel>> _models;

    std::unordered_set<QExtBPTypes::ConnectionId> _connectivity;

    mutable std::unordered_map<QExtBPTypes::NodeId, NodeGeometryData> _nodeGeometryData;
};

#endif // _QEXTBPDATAFLOWGRAPHICSMODEL_H
