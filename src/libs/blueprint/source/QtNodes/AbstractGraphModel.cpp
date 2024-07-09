#include "AbstractGraphModel.hpp"

#include "ConnectionIdUtils.hpp"

void QExtBPAbstractGraphModel::portsAboutToBeDeleted(QExtBPTypes::NodeId const nodeId,
                                                     QExtBPTypes::PortTypeEnum const portType,
                                                     QExtBPTypes::PortIndex const first,
                                                     QExtBPTypes::PortIndex const last)
{
    _shiftedByDynamicPortsConnections.clear();

    auto portCountRole = portType == QExtBPTypes::PortType_In ? QExtBPTypes::NodeRole_InPortCount : QExtBPTypes::NodeRole_OutPortCount;

    unsigned int portCount = nodeData(nodeId, portCountRole).toUInt();

    if (first > portCount - 1)
        return;

    if (last < first)
        return;

    auto clampedLast = std::min(last, portCount - 1);

    for (QExtBPTypes::PortIndex portIndex = first; portIndex <= clampedLast; ++portIndex) {
        std::unordered_set<QExtBPTypes::ConnectionId> conns = connections(nodeId, portType, portIndex);

        for (auto connectionId : conns) {
            deleteConnection(connectionId);
        }
    }

    std::size_t const nRemovedPorts = clampedLast - first + 1;

    for (QExtBPTypes::PortIndex portIndex = clampedLast + 1; portIndex < portCount; ++portIndex) {
        std::unordered_set<QExtBPTypes::ConnectionId> conns = connections(nodeId, portType, portIndex);

        for (auto connectionId : conns) {
            // Erases the information about the port on one side;
            auto c = QExtBPUtils::makeIncompleteConnectionId(connectionId, portType);

            c = QExtBPUtils::makeCompleteConnectionId(c, nodeId, portIndex - nRemovedPorts);

            _shiftedByDynamicPortsConnections.push_back(c);

            deleteConnection(connectionId);
        }
    }
}

void QExtBPAbstractGraphModel::portsDeleted()
{
    for (auto const connectionId : _shiftedByDynamicPortsConnections) {
        addConnection(connectionId);
    }

    _shiftedByDynamicPortsConnections.clear();
}

void QExtBPAbstractGraphModel::portsAboutToBeInserted(QExtBPTypes::NodeId const nodeId,
                                                      QExtBPTypes::PortTypeEnum const portType,
                                                      QExtBPTypes::PortIndex const first,
                                                      QExtBPTypes::PortIndex const last)
{
    _shiftedByDynamicPortsConnections.clear();

    auto portCountRole = portType == QExtBPTypes::PortType_In ? QExtBPTypes::NodeRole_InPortCount : QExtBPTypes::NodeRole_OutPortCount;

    unsigned int portCount = nodeData(nodeId, portCountRole).toUInt();

    if (first > portCount)
        return;

    if (last < first)
        return;

    std::size_t const nNewPorts = last - first + 1;

    for (QExtBPTypes::PortIndex portIndex = first; portIndex < portCount; ++portIndex) {
        std::unordered_set<QExtBPTypes::ConnectionId> conns = connections(nodeId, portType, portIndex);

        for (auto connectionId : conns) {
            // Erases the information about the port on one side;
            auto c = QExtBPUtils::makeIncompleteConnectionId(connectionId, portType);

            c = QExtBPUtils::makeCompleteConnectionId(c, nodeId, portIndex + nNewPorts);

            _shiftedByDynamicPortsConnections.push_back(c);

            deleteConnection(connectionId);
        }
    }
}

void QExtBPAbstractGraphModel::portsInserted()
{
    for (auto const connectionId : _shiftedByDynamicPortsConnections) {
        addConnection(connectionId);
    }

    _shiftedByDynamicPortsConnections.clear();
}
