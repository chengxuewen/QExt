#include <private/qextBPAbstractGraphModel_p.h>
#include <qextBPUtils.h>
#include <qextMemory.h>

QExtBPAbstractGraphModelPrivate::QExtBPAbstractGraphModelPrivate(QExtBPAbstractGraphModel *q)
    : q_ptr(q)
{
}

QExtBPAbstractGraphModelPrivate::~QExtBPAbstractGraphModelPrivate()
{
}

QExtBPAbstractGraphModel::QExtBPAbstractGraphModel(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtBPAbstractGraphModelPrivate(this))
{
}

QExtBPAbstractGraphModel::QExtBPAbstractGraphModel(QExtBPAbstractGraphModelPrivate *d, QObject *parent)
    : QObject(parent)
    , dd_ptr(d)
{
}

QExtBPAbstractGraphModel::~QExtBPAbstractGraphModel()
{
}

void QExtBPAbstractGraphModel::portsAboutToBeDeleted(const QExtBPTypes::NodeId nodeId,
                                                     const QExtBPTypes::PortTypeEnum portType,
                                                     const QExtBPTypes::PortIndex first,
                                                     const QExtBPTypes::PortIndex last)
{
    Q_D(QExtBPAbstractGraphModel);
    d->m_shiftedByDynamicPortsConnections.clear();

    auto portCountRole = portType == QExtBPTypes::PortType_In ? QExtBPTypes::NodeRole_InPortCount
                                                              : QExtBPTypes::NodeRole_OutPortCount;

    unsigned int portCount = nodeData(nodeId, portCountRole).toUInt();
    if (first > portCount - 1)
    {
        return;
    }

    if (last < first)
    {
        return;
    }

    auto clampedLast = std::min(last, portCount - 1);
    for (QExtBPTypes::PortIndex portIndex = first; portIndex <= clampedLast; ++portIndex)
    {
        std::unordered_set<QExtBPTypes::ConnectionId> conns = connections(nodeId, portType, portIndex);
        for (auto connectionId : conns)
        {
            this->deleteConnection(connectionId);
        }
    }

    std::size_t const nRemovedPorts = clampedLast - first + 1;

    for (QExtBPTypes::PortIndex portIndex = clampedLast + 1; portIndex < portCount; ++portIndex)
    {
        std::unordered_set<QExtBPTypes::ConnectionId> conns = connections(nodeId, portType, portIndex);
        for (auto connectionId : conns)
        {
            // Erases the information about the port on one side;
            auto c = QExtBPUtils::makeIncompleteConnectionId(connectionId, portType);
            c = QExtBPUtils::makeCompleteConnectionId(c, nodeId, portIndex - nRemovedPorts);
            d->m_shiftedByDynamicPortsConnections.push_back(c);

            this->deleteConnection(connectionId);
        }
    }
}

void QExtBPAbstractGraphModel::portsDeleted()
{
    Q_D(QExtBPAbstractGraphModel);
    Q_FOREACH (const auto &connectionId, d->m_shiftedByDynamicPortsConnections)
    {
        this->addConnection(connectionId);
    }
    d->m_shiftedByDynamicPortsConnections.clear();
}

void QExtBPAbstractGraphModel::portsAboutToBeInserted(const QExtBPTypes::NodeId nodeId,
                                                      const QExtBPTypes::PortTypeEnum portType,
                                                      const QExtBPTypes::PortIndex first,
                                                      const QExtBPTypes::PortIndex last)
{
    Q_D(QExtBPAbstractGraphModel);
    d->m_shiftedByDynamicPortsConnections.clear();

    auto portCountRole = portType == QExtBPTypes::PortType_In ? QExtBPTypes::NodeRole_InPortCount
                                                              : QExtBPTypes::NodeRole_OutPortCount;

    unsigned int portCount = this->nodeData(nodeId, portCountRole).toUInt();
    if (first > portCount)
    {
        return;
    }

    if (last < first)
    {
        return;
    }

    std::size_t const nNewPorts = last - first + 1;
    for (QExtBPTypes::PortIndex portIndex = first; portIndex < portCount; ++portIndex)
    {
        std::unordered_set<QExtBPTypes::ConnectionId> conns = connections(nodeId, portType, portIndex);

        for (auto connectionId : conns)
        {
            // Erases the information about the port on one side;
            auto c = QExtBPUtils::makeIncompleteConnectionId(connectionId, portType);
            c = QExtBPUtils::makeCompleteConnectionId(c, nodeId, portIndex + nNewPorts);
            d->m_shiftedByDynamicPortsConnections.push_back(c);

            this->deleteConnection(connectionId);
        }
    }
}

void QExtBPAbstractGraphModel::portsInserted()
{
    Q_D(QExtBPAbstractGraphModel);
    Q_FOREACH (const auto &connectionId, d->m_shiftedByDynamicPortsConnections)
    {
        this->addConnection(connectionId);
    }
    d->m_shiftedByDynamicPortsConnections.clear();
}
