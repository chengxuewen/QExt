#ifndef _QEXTBPNODESTATE_H
#define _QEXTBPNODESTATE_H

#include <qextBlueprintGlobal.h>
#include <qextBPNodeData.h>
#include <qextBPTypes.h>

#include <QUuid>
#include <QPointF>
#include <QPointer>

#include <vector>
#include <unordered_map>


class QExtBPConnectionGraphicsObject;
class QExtBPNodeGraphicsObject;

/// Stores bool for hovering connections and resizing flag.
class QEXT_BLUEPRINT_API QExtBPNodeState
{
public:
    QExtBPNodeState(QExtBPNodeGraphicsObject &ngo);

public:
    bool hovered() const { return _hovered; }

    void setHovered(bool hovered = true) { _hovered = hovered; }

    void setResizing(bool resizing);

    bool resizing() const;

    QExtBPConnectionGraphicsObject const *connectionForReaction() const;

    void storeConnectionForReaction(QExtBPConnectionGraphicsObject const *cgo);

    void resetConnectionForReaction();

private:
    QExtBPNodeGraphicsObject &_ngo;

    bool _hovered;

    bool _resizing;

    // QPointer tracks the QObject inside and is automatically cleared
    // when the object is destroyed.
    QPointer<QExtBPConnectionGraphicsObject const> _connectionForReaction;
};

#endif // _QEXTBPNODESTATE_H
