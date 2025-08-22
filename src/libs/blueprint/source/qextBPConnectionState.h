#ifndef _QEXTBPCONNECTIONSTATE_H
#define _QEXTBPCONNECTIONSTATE_H

#include <qextBlueprintGlobal.h>
#include <qextBPTypes.h>

#include <QUuid>

class QPointF;

class QExtBPConnectionGraphicsObject;

/// Stores currently draggind end.
/// Remembers last hovered Node.
class QExtBPConnectionStatePrivate;
class QEXT_BLUEPRINT_API QExtBPConnectionState
{
public:
    /// Defines whether we construct a new connection
    /// or it is already binding two nodes.
    enum LooseEnd { Pending = 0, Connected = 1 };

    explicit QExtBPConnectionState(QExtBPConnectionGraphicsObject &object);
    virtual ~QExtBPConnectionState();

    QExtBPTypes::PortTypeEnum requiredPort() const;
    bool requiresPort() const;

    bool hovered() const;
    void setHovered(bool hovered);

    /// Caches QExtBPTypes::NodeId for further interaction.
    void setLastHoveredNode(const QExtBPTypes::NodeId nodeId);

    QExtBPTypes::NodeId lastHoveredNode() const;

    void resetLastHoveredNode();

protected:
    QScopedPointer<QExtBPConnectionStatePrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtBPConnectionState)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPConnectionState)
};

#endif // _QEXTBPCONNECTIONSTATE_H
