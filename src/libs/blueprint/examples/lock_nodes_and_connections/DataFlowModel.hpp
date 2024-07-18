#include <QExtBlueprint>

class DataFlowModel : public QExtBPDataFlowGraphModel
{
public:
    DataFlowModel(QSharedPointer<QExtBPNodeDelegateModelRegistry> registry)
        : QExtBPDataFlowGraphModel(registry)
        , _detachPossible{true}
        , _nodesLocked{false}
    {}

    bool detachPossible(const QExtBPTypes::ConnectionId) const override { return _detachPossible; }

    void setDetachPossible(bool d = true) { _detachPossible = d; }

    //----

    QExtBPTypes::NodeFlagEnums nodeFlags(QExtBPTypes::NodeId nodeId) const override
    {
        auto basicFlags = QExtBPDataFlowGraphModel::nodeFlags(nodeId);

        if (_nodesLocked)
            basicFlags |= QExtBPTypes::NodeFlag_Locked;

        return basicFlags;
    }

    void setNodesLocked(bool b = true)
    {
        _nodesLocked = b;

        for (QExtBPTypes::NodeId nodeId : allNodeIds()) {
            Q_EMIT nodeFlagsUpdated(nodeId);
        }
    }

private:
    bool _detachPossible;

    bool _nodesLocked;
};
