#ifndef _QEXTBPDATAFLOWGRAPHMODEL_P_H
#define _QEXTBPDATAFLOWGRAPHMODEL_P_H

#include <qextBPDataFlowGraphModel.h>
#include <private/qextBPAbstractGraphModel_p.h>

class QExtBPDataFlowGraphModelPrivate : public QExtBPAbstractGraphModelPrivate
{
public:
    explicit QExtBPDataFlowGraphModelPrivate(QExtBPDataFlowGraphModel *q);
    ~QExtBPDataFlowGraphModelPrivate() QEXT_OVERRIDE;

    QExtBPTypes::NodeId m_nextNodeId;
    QExtSharedPointer<QExtBPNodeDelegateModelRegistry> m_registry;
    std::unordered_set<QExtBPTypes::ConnectionId> m_connectivity;
    std::unordered_map<QExtBPTypes::NodeId, QScopedPointer<QExtBPNodeDelegateModel>> m_models;
    mutable std::unordered_map<QExtBPTypes::NodeId, QExtBPDataFlowGraphModel::NodeGeometryData> m_nodeGeometryData;

private:
    QEXT_DECLARE_PUBLIC(QExtBPDataFlowGraphModel)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPDataFlowGraphModelPrivate)
};

#endif // _QEXTBPDATAFLOWGRAPHMODEL_P_H
