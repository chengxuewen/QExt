#ifndef _QEXTBPNODESTATE_P_H
#define _QEXTBPNODESTATE_P_H

#include <qextBPNodeState.h>

class QExtBPNodeStatePrivate
{
public:
    QExtBPNodeStatePrivate(QExtBPNodeState *q, QExtBPNodeGraphicsObject &object);
    virtual ~QExtBPNodeStatePrivate();

    QExtBPNodeState *q_ptr;

    bool m_hovered;
    bool m_resizing;
    QExtBPNodeGraphicsObject &m_nodeGraphicsObject;
    // QPointer tracks the QObject inside and is automatically cleared when the object is destroyed.
    QPointer<QExtBPConnectionGraphicsObject const> m_connectionForReaction;

private:
    QEXT_DECLARE_PUBLIC(QExtBPNodeState)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPNodeStatePrivate)
};

#endif // _QEXTBPNODESTATE_P_H
