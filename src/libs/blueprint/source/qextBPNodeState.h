#ifndef _QEXTBPNODESTATE_H
#define _QEXTBPNODESTATE_H

#include <qextBlueprintGlobal.h>
#include <qextBPNodeData.h>
#include <qextBPTypes.h>

#include <QUuid>
#include <QPointF>
#include <QPointer>

class QExtBPConnectionGraphicsObject;
class QExtBPNodeGraphicsObject;

/// Stores bool for hovering connections and resizing flag.
class QExtBPNodeStatePrivate;
class QEXT_BLUEPRINT_API QExtBPNodeState
{
public:
    QExtBPNodeState(QExtBPNodeGraphicsObject &object);
    virtual ~QExtBPNodeState();

    bool hovered() const;

    void setHovered(bool hovered = true);

    void setResizing(bool resizing);

    bool resizing() const;

    QExtBPConnectionGraphicsObject const *connectionForReaction() const;

    void storeConnectionForReaction(QExtBPConnectionGraphicsObject const *object);

    void resetConnectionForReaction();

protected:
    QScopedPointer<QExtBPNodeStatePrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtBPNodeState)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPNodeState)
};

#endif // _QEXTBPNODESTATE_H
