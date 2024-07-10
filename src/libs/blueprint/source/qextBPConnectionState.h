#ifndef _QEXTBPCONNECTIONSTATE_H
#define _QEXTBPCONNECTIONSTATE_H

#include <qextBlueprintGlobal.h>
#include <qextBPTypes.h>

#include <QUuid>

class QPointF;

class QExtBPConnectionGraphicsObject;

/// Stores currently draggind end.
/// Remembers last hovered Node.
class QEXT_BLUEPRINT_API QExtBPConnectionState
{
public:
    /// Defines whether we construct a new connection
    /// or it is already binding two nodes.
    enum LooseEnd { Pending = 0, Connected = 1 };

public:
    QExtBPConnectionState(QExtBPConnectionGraphicsObject &cgo)
        : _cgo(cgo)
        , _hovered(false)
    {}

    QExtBPConnectionState(QExtBPConnectionState const &) = delete;
    QExtBPConnectionState(QExtBPConnectionState &&) = delete;

    QExtBPConnectionState &operator=(QExtBPConnectionState const &) = delete;
    QExtBPConnectionState &operator=(QExtBPConnectionState &&) = delete;

    ~QExtBPConnectionState();

public:
    QExtBPTypes::PortTypeEnum requiredPort() const;
    bool requiresPort() const;

    bool hovered() const;
    void setHovered(bool hovered);

public:
    /// Caches QExtBPTypes::NodeId for further interaction.
    void setLastHoveredNode(QExtBPTypes::NodeId const nodeId);

    QExtBPTypes::NodeId lastHoveredNode() const;

    void resetLastHoveredNode();

private:
    QExtBPConnectionGraphicsObject &_cgo;

    bool _hovered;

    QExtBPTypes::NodeId _lastHoveredNode{QExtBPTypes::InvalidNodeId};
};

#endif // _QEXTBPCONNECTIONSTATE_H
