#ifndef _QEXTBPUTILS_H
#define _QEXTBPUTILS_H

#include <qextBPTypes.h>

#include <QJsonObject>

#include <iostream>
#include <string>

namespace QExtBPUtils
{

inline QExtBPTypes::PortIndex getNodeId(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::ConnectionId connectionId)
{
    QExtBPTypes::NodeId id = QExtBPTypes::InvalidNodeId;

    if (portType == QExtBPTypes::PortType_Out) {
        id = connectionId.outNodeId;
    } else if (portType == QExtBPTypes::PortType_In) {
        id = connectionId.inNodeId;
    }

    return id;
}

inline QExtBPTypes::PortIndex getPortIndex(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::ConnectionId connectionId)
{
    QExtBPTypes::PortIndex index = QExtBPTypes::InvalidPortIndex;

    if (portType == QExtBPTypes::PortType_Out) {
        index = connectionId.outPortIndex;
    } else if (portType == QExtBPTypes::PortType_In) {
        index = connectionId.inPortIndex;
    }

    return index;
}

inline QExtBPTypes::PortTypeEnum oppositePort(QExtBPTypes::PortTypeEnum port)
{
    QExtBPTypes::PortTypeEnum result = QExtBPTypes::PortType_None;

    switch (port) {
    case QExtBPTypes::PortType_In:
        result = QExtBPTypes::PortType_Out;
        break;

    case QExtBPTypes::PortType_Out:
        result = QExtBPTypes::PortType_In;
        break;

    case QExtBPTypes::PortType_None:
        result = QExtBPTypes::PortType_None;
        break;

    default:
        break;
    }
    return result;
}

inline bool isPortIndexValid(QExtBPTypes::PortIndex index)
{
    return index != QExtBPTypes::InvalidPortIndex;
}

inline bool isPortTypeValid(QExtBPTypes::PortTypeEnum portType)
{
    return portType != QExtBPTypes::PortType_None;
}

/**
 * Creates a connection Id instance filled just on one side.
 */
inline QExtBPTypes::ConnectionId makeIncompleteConnectionId(QExtBPTypes::NodeId const connectedNodeId,
                                                            QExtBPTypes::PortTypeEnum const connectedPort,
                                                            QExtBPTypes::PortIndex const connectedPortIndex)
{
    return (connectedPort == QExtBPTypes::PortType_In)
            ? QExtBPTypes::ConnectionId{QExtBPTypes::InvalidNodeId, QExtBPTypes::InvalidPortIndex, connectedNodeId, connectedPortIndex}
            : QExtBPTypes::ConnectionId{connectedNodeId, connectedPortIndex, QExtBPTypes::InvalidNodeId, QExtBPTypes::InvalidPortIndex};
}

/**
 * Turns a full connection Id into an incomplete one by removing the
 * data on the given side
 */
inline QExtBPTypes::ConnectionId makeIncompleteConnectionId(QExtBPTypes::ConnectionId connectionId,
                                                            QExtBPTypes::PortTypeEnum const portToDisconnect)
{
    if (portToDisconnect == QExtBPTypes::PortType_Out) {
        connectionId.outNodeId = QExtBPTypes::InvalidNodeId;
        connectionId.outPortIndex = QExtBPTypes::InvalidPortIndex;
    } else {
        connectionId.inNodeId = QExtBPTypes::InvalidNodeId;
        connectionId.inPortIndex = QExtBPTypes::InvalidPortIndex;
    }

    return connectionId;
}

inline QExtBPTypes::ConnectionId makeCompleteConnectionId(QExtBPTypes::ConnectionId incompleteConnectionId,
                                                          QExtBPTypes::NodeId const nodeId,
                                                          QExtBPTypes::PortIndex const portIndex)
{
    if (incompleteConnectionId.outNodeId == QExtBPTypes::InvalidNodeId) {
        incompleteConnectionId.outNodeId = nodeId;
        incompleteConnectionId.outPortIndex = portIndex;
    } else {
        incompleteConnectionId.inNodeId = nodeId;
        incompleteConnectionId.inPortIndex = portIndex;
    }

    return incompleteConnectionId;
}

inline std::ostream &operator<<(std::ostream &ostr, QExtBPTypes::ConnectionId const connectionId)
{
    ostr << "(" << connectionId.outNodeId << ", "
         << (isPortIndexValid(connectionId.outPortIndex) ? std::to_string(connectionId.outPortIndex)
                                                         : "INVALID")
         << ", " << connectionId.inNodeId << ", "
         << (isPortIndexValid(connectionId.inPortIndex) ? std::to_string(connectionId.inPortIndex)
                                                        : "INVALID")
         << ")" << std::endl;

    return ostr;
}

inline QJsonObject toJson(QExtBPTypes::ConnectionId const &connId)
{
    QJsonObject connJson;

    connJson["outNodeId"] = static_cast<qint64>(connId.outNodeId);
    connJson["outPortIndex"] = static_cast<qint64>(connId.outPortIndex);
    connJson["intNodeId"] = static_cast<qint64>(connId.inNodeId);
    connJson["inPortIndex"] = static_cast<qint64>(connId.inPortIndex);

    return connJson;
}

inline QExtBPTypes::ConnectionId fromJson(QJsonObject const &connJson)
{
    QExtBPTypes::ConnectionId connId{static_cast<QExtBPTypes::NodeId>(connJson["outNodeId"].toInt(QExtBPTypes::InvalidNodeId)),
                static_cast<QExtBPTypes::PortIndex>(connJson["outPortIndex"].toInt(QExtBPTypes::InvalidPortIndex)),
                static_cast<QExtBPTypes::NodeId>(connJson["intNodeId"].toInt(QExtBPTypes::InvalidNodeId)),
                static_cast<QExtBPTypes::PortIndex>(connJson["inPortIndex"].toInt(QExtBPTypes::InvalidPortIndex))};

    return connId;
}

} // namespace QExtBPUtils

#endif // _QEXTBPUTILS_H
