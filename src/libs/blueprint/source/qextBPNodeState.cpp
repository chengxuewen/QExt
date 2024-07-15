#include <qextBPNodeState.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPNodeGraphicsObject.h>

QExtBPNodeState::QExtBPNodeState(QExtBPNodeGraphicsObject &ngo)
    : _ngo(ngo)
    , _hovered(false)
    , _resizing(false)
    , _connectionForReaction(QEXT_NULLPTR)
{
    Q_UNUSED(_ngo);
}

void QExtBPNodeState::setResizing(bool resizing)
{
    _resizing = resizing;
}

bool QExtBPNodeState::resizing() const
{
    return _resizing;
}

QExtBPConnectionGraphicsObject const *QExtBPNodeState::connectionForReaction() const
{
    return _connectionForReaction.data();
}

void QExtBPNodeState::storeConnectionForReaction(QExtBPConnectionGraphicsObject const *cgo)
{
    _connectionForReaction = cgo;
}

void QExtBPNodeState::resetConnectionForReaction()
{
    _connectionForReaction.clear();
}
