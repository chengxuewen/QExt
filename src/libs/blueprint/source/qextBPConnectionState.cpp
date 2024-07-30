#include <private/qextBPConnectionState_p.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPBasicGraphicsScene.h>

#include <QtCore/QDebug>
#include <QtCore/QPointF>

QExtBPConnectionStatePrivate::QExtBPConnectionStatePrivate(QExtBPConnectionState *q,
                                                           QExtBPConnectionGraphicsObject &object)
    : q_ptr(q)
    , m_hovered(false)
    , m_lastHoveredNode(QExtBPTypes::InvalidNodeId)
    , m_connectionGraphicsObject(object)
{
}

QExtBPConnectionStatePrivate::~QExtBPConnectionStatePrivate()
{
}

QExtBPConnectionState::QExtBPConnectionState(QExtBPConnectionGraphicsObject &object)
    : dd_ptr(new QExtBPConnectionStatePrivate(this, object))
{
}

QExtBPConnectionState::~QExtBPConnectionState()
{
    //resetLastHoveredNode();
}

QExtBPTypes::PortTypeEnum QExtBPConnectionState::requiredPort() const
{
    Q_D(const QExtBPConnectionState);
    QExtBPTypes::PortTypeEnum t = QExtBPTypes::PortType_None;

    if (d->m_connectionGraphicsObject.connectionId().outNodeId == QExtBPTypes::InvalidNodeId)
    {
        t = QExtBPTypes::PortType_Out;
    }
    else if (d->m_connectionGraphicsObject.connectionId().inNodeId == QExtBPTypes::InvalidNodeId)
    {
        t = QExtBPTypes::PortType_In;
    }

    return t;
}

bool QExtBPConnectionState::requiresPort() const
{
    Q_D(const QExtBPConnectionState);
    const QExtBPTypes::ConnectionId &id = d->m_connectionGraphicsObject.connectionId();
    return id.outNodeId == QExtBPTypes::InvalidNodeId || id.inNodeId == QExtBPTypes::InvalidNodeId;
}

bool QExtBPConnectionState::hovered() const
{
    Q_D(const QExtBPConnectionState);
    return d->m_hovered;
}

void QExtBPConnectionState::setHovered(bool hovered)
{
    Q_D(QExtBPConnectionState);
    d->m_hovered = hovered;
}

void QExtBPConnectionState::setLastHoveredNode(const QExtBPTypes::NodeId nodeId)
{
    Q_D(QExtBPConnectionState);
    d->m_lastHoveredNode = nodeId;
}

QExtBPTypes::NodeId QExtBPConnectionState::lastHoveredNode() const
{
    Q_D(const QExtBPConnectionState);
    return d->m_lastHoveredNode;
}

void QExtBPConnectionState::resetLastHoveredNode()
{
    Q_D(QExtBPConnectionState);
    if (d->m_lastHoveredNode != QExtBPTypes::InvalidNodeId)
    {
        auto ngo = d->m_connectionGraphicsObject.nodeScene()->nodeGraphicsObject(d->m_lastHoveredNode);
        ngo->update();
    }
    d->m_lastHoveredNode = QExtBPTypes::InvalidNodeId;
}

