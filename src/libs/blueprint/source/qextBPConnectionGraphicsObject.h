#ifndef _QEXTBPCONNECTIONGRAPHICSOBJECT_H
#define _QEXTBPCONNECTIONGRAPHICSOBJECT_H

#include <qextBPConnectionState.h>
#include <qextBPTypes.h>

#include <QGraphicsObject>
#include <QUuid>

#include <utility>

class QGraphicsSceneMouseEvent;
class QExtBPAbstractGraphModel;
class QExtBPBasicGraphicsScene;

/// Graphic Object for connection. Adds itself to scene
class QExtBPConnectionGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
public:
    // Needed for qgraphicsitem_cast
    enum { Type = UserType + 2 };

    int type() const override { return Type; }

public:
    QExtBPConnectionGraphicsObject(QExtBPBasicGraphicsScene &scene, const QExtBPTypes::ConnectionId connectionId);

    ~QExtBPConnectionGraphicsObject() = default;

public:
    QExtBPAbstractGraphModel &graphModel() const;

    QExtBPBasicGraphicsScene *nodeScene() const;

    const QExtBPTypes::ConnectionId &connectionId() const;

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    const QPointF &endPoint(QExtBPTypes::PortTypeEnum portType) const;

    QPointF out() const { return _out; }

    QPointF in() const { return _in; }

    std::pair<QPointF, QPointF> pointsC1C2() const;

    void setEndPoint(QExtBPTypes::PortTypeEnum portType, const QPointF &point);

    /// Updates the position of both ends
    void move();

    const QExtBPConnectionState &connectionState() const;

    QExtBPConnectionState &connectionState();

protected:
    void paint(QPainter *painter,
               QStyleOptionGraphicsItem const *option,
               QWidget *widget = 0) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    void initializePosition();

    void addGraphicsEffect();

    std::pair<QPointF, QPointF> pointsC1C2Horizontal() const;

    std::pair<QPointF, QPointF> pointsC1C2Vertical() const;

private:
    QExtBPTypes::ConnectionId _connectionId;

    QExtBPAbstractGraphModel &_graphModel;

    QExtBPConnectionState _connectionState;

    mutable QPointF _out;
    mutable QPointF _in;
};

#endif // _QEXTBPCONNECTIONGRAPHICSOBJECT_H
