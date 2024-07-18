#ifndef _QEXTBPNODEGRAPHICSOBJECT_H
#define _QEXTBPNODEGRAPHICSOBJECT_H

#include <QtCore/QUuid>
#include <QtWidgets/QGraphicsObject>

#include "qextBPNodeState.h"

class QGraphicsProxyWidget;

class QExtBPAbstractGraphModel;
class QExtBPBasicGraphicsScene;

class QExtBPNodeGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    // Needed for qgraphicsitem_cast
    enum { Type = UserType + 1 };

    int type() const override { return Type; }

public:
    QExtBPNodeGraphicsObject(QExtBPBasicGraphicsScene &scene, QExtBPTypes::NodeId node);

    ~QExtBPNodeGraphicsObject() override = default;

public:
    QExtBPAbstractGraphModel &graphModel() const;

    QExtBPBasicGraphicsScene *nodeScene() const;

    QExtBPTypes::NodeId nodeId() { return _nodeId; }

    QExtBPTypes::NodeId nodeId() const { return _nodeId; }

    QExtBPNodeState &nodeState() { return _nodeState; }

    const QExtBPNodeState &nodeState() const { return _nodeState; }

    QRectF boundingRect() const override;

    void setGeometryChanged();

    /// Visits all attached connections and corrects
    /// their corresponding end points.
    void moveConnections() const;

    /// Repaints the node once with reacting ports.
    void reactToConnection(QExtBPConnectionGraphicsObject const *cgo);

protected:
    void paint(QPainter *painter,
               QStyleOptionGraphicsItem const *option,
               QWidget *widget = 0) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    void embedQWidget();

    void setLockedState();

private:
    QExtBPTypes::NodeId _nodeId;

    QExtBPAbstractGraphModel &_graphModel;

    QExtBPNodeState _nodeState;

    // either QEXT_NULLPTR or owned by parent QGraphicsItem
    QGraphicsProxyWidget *_proxyWidget;
};

#endif // _QEXTBPNODEGRAPHICSOBJECT_H
