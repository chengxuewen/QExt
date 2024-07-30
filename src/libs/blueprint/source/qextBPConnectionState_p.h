#ifndef _QEXTBPCONNECTIONSTATE_P_H
#define _QEXTBPCONNECTIONSTATE_P_H

#include <qextBPConnectionState.h>

class QExtBPConnectionStatePrivate
{
public:
    QExtBPConnectionStatePrivate(QExtBPConnectionState *q, QExtBPConnectionGraphicsObject &object);
    virtual ~QExtBPConnectionStatePrivate();

    QExtBPConnectionState * const q_ptr;

    bool m_hovered;
    QExtBPTypes::NodeId m_lastHoveredNode;
    QExtBPConnectionGraphicsObject &m_connectionGraphicsObject;

private:
    QEXT_DECL_PUBLIC(QExtBPConnectionState)
    QEXT_DISABLE_COPY_MOVE(QExtBPConnectionStatePrivate)
};

#endif // _QEXTBPCONNECTIONSTATE_P_H
