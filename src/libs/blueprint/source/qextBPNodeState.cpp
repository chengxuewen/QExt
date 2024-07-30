#include <private/qextBPNodeState_p.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPNodeGraphicsObject.h>

QExtBPNodeStatePrivate::QExtBPNodeStatePrivate(QExtBPNodeState *q, QExtBPNodeGraphicsObject &object)
    : q_ptr(q)
    , m_hovered(false)
    , m_resizing(false)
    , m_nodeGraphicsObject(object)
    , m_connectionForReaction(QEXT_NULLPTR)
{
}

QExtBPNodeStatePrivate::~QExtBPNodeStatePrivate()
{
}

QExtBPNodeState::QExtBPNodeState(QExtBPNodeGraphicsObject &object)
    : dd_ptr(new QExtBPNodeStatePrivate(this, object))
{
}

QExtBPNodeState::~QExtBPNodeState()
{
}

bool QExtBPNodeState::hovered() const
{
    Q_D(const QExtBPNodeState);
    return d->m_hovered;
}

void QExtBPNodeState::setHovered(bool hovered)
{
    Q_D(QExtBPNodeState);
    d->m_hovered = hovered;
}

void QExtBPNodeState::setResizing(bool resizing)
{
    Q_D(QExtBPNodeState);
    d->m_resizing = resizing;
}

bool QExtBPNodeState::resizing() const
{
    Q_D(const QExtBPNodeState);
    return d->m_resizing;
}

QExtBPConnectionGraphicsObject const *QExtBPNodeState::connectionForReaction() const
{
    Q_D(const QExtBPNodeState);
    return d->m_connectionForReaction.data();
}

void QExtBPNodeState::storeConnectionForReaction(QExtBPConnectionGraphicsObject const *object)
{
    Q_D(QExtBPNodeState);
    d->m_connectionForReaction = object;
}

void QExtBPNodeState::resetConnectionForReaction()
{
    Q_D(QExtBPNodeState);
    d->m_connectionForReaction.clear();
}
