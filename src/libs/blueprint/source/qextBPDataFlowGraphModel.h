#ifndef _QEXTBPDATAFLOWGRAPHICSMODEL_H
#define _QEXTBPDATAFLOWGRAPHICSMODEL_H

#include <qextBPAbstractGraphModel.h>
#include <qextBPNodeDelegateModelRegistry.h>
#include <qextBPStyleCollection.h>
#include <qextBlueprintGlobal.h>
#include <qextBPSerializable.h>
#include <qextBPUtils.h>

#include <QJsonObject>

class QExtBPDataFlowGraphModelPrivate;
class QEXT_BLUEPRINT_API QExtBPDataFlowGraphModel : public QExtBPAbstractGraphModel, public QExtBPSerializable
{
    Q_OBJECT

public:
    struct NodeGeometryData
    {
        QSize size;
        QPointF pos;
    };

    QExtBPDataFlowGraphModel(QExtSharedPointer<QExtBPNodeDelegateModelRegistry> registry, QObject *parent = QEXT_NULLPTR);
    ~QExtBPDataFlowGraphModel() QEXT_OVERRIDE;

    QExtSharedPointer<QExtBPNodeDelegateModelRegistry> dataModelRegistry();

    std::unordered_set<QExtBPTypes::NodeId> allNodeIds() const override;

    std::unordered_set<QExtBPTypes::ConnectionId> allConnectionIds(const QExtBPTypes::NodeId nodeId) const override;

    std::unordered_set<QExtBPTypes::ConnectionId> connections(QExtBPTypes::NodeId nodeId,
                                                              QExtBPTypes::PortTypeEnum portType,
                                                              QExtBPTypes::PortIndex portIndex) const override;

    bool connectionExists(const QExtBPTypes::ConnectionId connectionId) const override;

    QExtBPTypes::NodeId addNode(QString const nodeType) override;

    bool connectionPossible(const QExtBPTypes::ConnectionId connectionId) const override;

    void addConnection(const QExtBPTypes::ConnectionId connectionId) override;

    bool nodeExists(const QExtBPTypes::NodeId nodeId) const override;

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
                     const QVariant &value,
                     QExtBPTypes::PortRoleEnum role = QExtBPTypes::PortRole_Data) override;

    bool deleteConnection(const QExtBPTypes::ConnectionId connectionId) override;

    bool deleteNode(const QExtBPTypes::NodeId nodeId) override;

    QJsonObject saveNode(const QExtBPTypes::NodeId) const override;

    QJsonObject save() const override;

    void loadNode(const QJsonObject &nodeJson) override;

    void load(const QJsonObject &json) override;

    /**
     * @brief Fetches the NodeDelegateModel for the given `nodeId` and tries to cast the stored pointer to the given type
     */
    template<typename NodeDelegateModelType>
    NodeDelegateModelType *delegateModel(const QExtBPTypes::NodeId nodeId)
    {
        auto it = this->models().find(nodeId);
        if (it == this->models().end())
        {
            return QEXT_NULLPTR;
        }

        auto model = dynamic_cast<NodeDelegateModelType *>(it->second.get());
        return model;
    }

Q_SIGNALS:
    void inPortDataWasSet(const QExtBPTypes::NodeId, const QExtBPTypes::PortTypeEnum, const QExtBPTypes::PortIndex);

private Q_SLOTS:
    /**
     * @brief Fuction is called in three cases:
     * - By underlying NodeDelegateModel when a node has new data to propagate.
     *   @see DataFlowGraphModel::addNode
     * - When a new connection is created.
     *   @see DataFlowGraphModel::addConnection
     * - When a node restored from JSON an needs to send data downstream.
     *   @see DataFlowGraphModel::loadNode
     */
    void onOutPortDataUpdated(const QExtBPTypes::NodeId nodeId, const QExtBPTypes::PortIndex portIndex);

    /**
     * @brief Function is called after detaching a connection.
     */
    void propagateEmptyDataTo(const QExtBPTypes::NodeId nodeId, const QExtBPTypes::PortIndex portIndex);

private:
    QExtBPTypes::NodeId newNodeId() override;

    void sendConnectionCreation(const QExtBPTypes::ConnectionId connectionId);

    void sendConnectionDeletion(const QExtBPTypes::ConnectionId connectionId);

    std::unordered_map<QExtBPTypes::NodeId, QScopedPointer<QExtBPNodeDelegateModel>> &models();

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBPDataFlowGraphModel)
    QEXT_DISABLE_COPY_MOVE(QExtBPDataFlowGraphModel)
};

#endif // _QEXTBPDATAFLOWGRAPHICSMODEL_H
