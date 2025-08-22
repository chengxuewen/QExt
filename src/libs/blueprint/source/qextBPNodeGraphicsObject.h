#ifndef _QEXTBPNODEGRAPHICSOBJECT_H
#define _QEXTBPNODEGRAPHICSOBJECT_H

#include <qextBPNodeState.h>

#include <QtCore/QUuid>
#include <QtWidgets/QGraphicsObject>

class QGraphicsProxyWidget;

class QExtBPAbstractGraphModel;
class QExtBPBasicGraphicsScene;
class QExtBPNodeGraphicsObjectPrivate;
class QExtBPNodeGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    // Needed for qgraphicsitem_cast
    enum { Type = UserType + 1 };

    int type() const override { return Type; }

    QExtBPNodeGraphicsObject(QExtBPBasicGraphicsScene &scene, QExtBPTypes::NodeId node,
                             QGraphicsItem *parent = QEXT_NULLPTR);
    ~QExtBPNodeGraphicsObject() QEXT_OVERRIDE;

    QExtBPAbstractGraphModel &graphModel() const;

    QExtBPBasicGraphicsScene *nodeScene() const;

    QExtBPTypes::NodeId nodeId();

    QExtBPTypes::NodeId nodeId() const;

    QExtBPNodeState &nodeState();

    const QExtBPNodeState &nodeState() const;

    QRectF boundingRect() const QEXT_OVERRIDE;

    void setGeometryChanged();

    /// Visits all attached connections and corrects
    /// their corresponding end points.
    void moveConnections() const;

    /// Repaints the node once with reacting ports.
    void reactToConnection(QExtBPConnectionGraphicsObject const *cgo);

protected:
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget = 0) QEXT_OVERRIDE;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) QEXT_OVERRIDE;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) QEXT_OVERRIDE;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) QEXT_OVERRIDE;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) QEXT_OVERRIDE;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) QEXT_OVERRIDE;

    void hoverMoveEvent(QGraphicsSceneHoverEvent *) QEXT_OVERRIDE;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) QEXT_OVERRIDE;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtBPNodeGraphicsObjectPrivate> dd_ptr;

private:
    void embedQWidget();

    void setLockedState();

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtBPNodeGraphicsObject)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPNodeGraphicsObject)
};

#endif // _QEXTBPNODEGRAPHICSOBJECT_H
