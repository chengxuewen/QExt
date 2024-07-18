#include <qextBPAbstractGraphModel.h>
#include <qextBPUtils.h>


void QExtBPAbstractGraphModel::portsAboutToBeDeleted(const QExtBPTypes::NodeId nodeId,
                                                     const QExtBPTypes::PortTypeEnum portType,
                                                     const QExtBPTypes::PortIndex first,
                                                     const QExtBPTypes::PortIndex last)
{
    m_shiftedByDynamicPortsConnections.clear();

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
            m_shiftedByDynamicPortsConnections.push_back(c);

            this->deleteConnection(connectionId);
        }
    }
}

void QExtBPAbstractGraphModel::portsDeleted()
{
    for (auto const connectionId : m_shiftedByDynamicPortsConnections)
    {
        this->addConnection(connectionId);
    }
    m_shiftedByDynamicPortsConnections.clear();
}

void QExtBPAbstractGraphModel::portsAboutToBeInserted(const QExtBPTypes::NodeId nodeId,
                                                      const QExtBPTypes::PortTypeEnum portType,
                                                      const QExtBPTypes::PortIndex first,
                                                      const QExtBPTypes::PortIndex last)
{
    m_shiftedByDynamicPortsConnections.clear();

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
            m_shiftedByDynamicPortsConnections.push_back(c);

            this->deleteConnection(connectionId);
        }
    }
}

void QExtBPAbstractGraphModel::portsInserted()
{
    for (auto const connectionId : m_shiftedByDynamicPortsConnections)
    {
        this->addConnection(connectionId);
    }
    m_shiftedByDynamicPortsConnections.clear();
}
