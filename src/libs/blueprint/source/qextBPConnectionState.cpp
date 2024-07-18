#include <qextBPConnectionState.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPBasicGraphicsScene.h>

#include <QtCore/QDebug>
#include <QtCore/QPointF>

QExtBPConnectionState::~QExtBPConnectionState()
{
    //resetLastHoveredNode();
}

QExtBPTypes::PortTypeEnum QExtBPConnectionState::requiredPort() const
{
    QExtBPTypes::PortTypeEnum t = QExtBPTypes::PortType_None;

    if (_cgo.connectionId().outNodeId == QExtBPTypes::InvalidNodeId) {
        t = QExtBPTypes::PortType_Out;
    } else if (_cgo.connectionId().inNodeId == QExtBPTypes::InvalidNodeId) {
        t = QExtBPTypes::PortType_In;
    }

    return t;
}

bool QExtBPConnectionState::requiresPort() const
{
    const QExtBPTypes::ConnectionId &id = _cgo.connectionId();
    return id.outNodeId == QExtBPTypes::InvalidNodeId || id.inNodeId == QExtBPTypes::InvalidNodeId;
}

bool QExtBPConnectionState::hovered() const
{
    return _hovered;
}

void QExtBPConnectionState::setHovered(bool hovered)
{
    _hovered = hovered;
}

void QExtBPConnectionState::setLastHoveredNode(const QExtBPTypes::NodeId nodeId)
{
    _lastHoveredNode = nodeId;
}

QExtBPTypes::NodeId QExtBPConnectionState::lastHoveredNode() const
{
    return _lastHoveredNode;
}

void QExtBPConnectionState::resetLastHoveredNode()
{
    if (_lastHoveredNode != QExtBPTypes::InvalidNodeId) {
        auto ngo = _cgo.nodeScene()->nodeGraphicsObject(_lastHoveredNode);
        ngo->update();
    }

    _lastHoveredNode = QExtBPTypes::InvalidNodeId;
}
