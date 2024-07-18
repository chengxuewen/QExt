#include <qextBPConnectionGraphicsObject.h>
#include <qextBPNodeConnectionInteraction.h>
#include <qextBPAbstractNodeGeometry.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPBasicGraphicsScene.h>
#include <qextBPConnectionPainter.h>
#include <qextBPConnectionState.h>
#include <qextBPConnectionStyle.h>
#include <qextBPStyleCollection.h>
#include <qextBPLocateNode.h>
#include <qextBPUtils.h>

#include <QtWidgets/QGraphicsBlurEffect>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QStyleOptionGraphicsItem>

#include <QtCore/QDebug>

#include <stdexcept>

QExtBPConnectionGraphicsObject::QExtBPConnectionGraphicsObject(QExtBPBasicGraphicsScene &scene,
                                                               const QExtBPTypes::ConnectionId connectionId)
    : _connectionId(connectionId)
    , _graphModel(scene.graphModel())
    , _connectionState(*this)
    , _out{0, 0}
    , _in{0, 0}
{
    scene.addItem(this);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    setAcceptHoverEvents(true);

    //addGraphicsEffect();

    setZValue(-1.0);

    initializePosition();
}

void QExtBPConnectionGraphicsObject::initializePosition()
{
    // This function is only called when the ConnectionGraphicsObject
    // is newly created. At this moment both end coordinates are (0, 0)
    // in Connection G.O. coordinates. The position of the whole
    // Connection G. O. in scene coordinate system is also (0, 0).
    // By moving the whole object to the Node Port position
    // we position both connection ends correctly.

    if (_connectionState.requiredPort() != QExtBPTypes::PortType_None) {
        QExtBPTypes::PortTypeEnum attachedPort = QExtBPUtils::oppositePort(_connectionState.requiredPort());

        QExtBPTypes::PortIndex portIndex = QExtBPUtils::getPortIndex(attachedPort, _connectionId);
        QExtBPTypes::NodeId nodeId = QExtBPUtils::getNodeId(attachedPort, _connectionId);

        QExtBPNodeGraphicsObject *ngo = nodeScene()->nodeGraphicsObject(nodeId);

        if (ngo) {
            QTransform nodeSceneTransform = ngo->sceneTransform();

            QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();

            QPointF pos = geometry.portScenePosition(nodeId,
                                                     attachedPort,
                                                     portIndex,
                                                     nodeSceneTransform);

            this->setPos(pos);
        }
    }

    move();
}

QExtBPAbstractGraphModel &QExtBPConnectionGraphicsObject::graphModel() const
{
    return _graphModel;
}

QExtBPBasicGraphicsScene *QExtBPConnectionGraphicsObject::nodeScene() const
{
    return dynamic_cast<QExtBPBasicGraphicsScene *>(scene());
}

const QExtBPTypes::ConnectionId &QExtBPConnectionGraphicsObject::connectionId() const
{
    return _connectionId;
}

QRectF QExtBPConnectionGraphicsObject::boundingRect() const
{
    auto points = pointsC1C2();

    // `normalized()` fixes inverted rects.
    QRectF basicRect = QRectF(_out, _in).normalized();

    QRectF c1c2Rect = QRectF(points.first, points.second).normalized();

    QRectF commonRect = basicRect.united(c1c2Rect);

    const auto &connectionStyle = QExtBPStyleCollection::connectionStyle();
    const float diam = connectionStyle.pointDiameter();
    const QPointF cornerOffset(diam, diam);

    // Expand rect by port circle diameter
    commonRect.setTopLeft(commonRect.topLeft() - cornerOffset);
    commonRect.setBottomRight(commonRect.bottomRight() + 2 * cornerOffset);

    return commonRect;
}

QPainterPath QExtBPConnectionGraphicsObject::shape() const
{
#ifdef DEBUG_DRAWING

    //QPainterPath path;

    //path.addRect(boundingRect());
    //return path;

#else
    return QExtBPConnectionPainter::getPainterStroke(*this);
#endif
}

const QPointF &QExtBPConnectionGraphicsObject::endPoint(QExtBPTypes::PortTypeEnum portType) const
{
    Q_ASSERT(portType != QExtBPTypes::PortType_None);

    return (portType == QExtBPTypes::PortType_Out ? _out : _in);
}

void QExtBPConnectionGraphicsObject::setEndPoint(QExtBPTypes::PortTypeEnum portType, const QPointF &point)
{
    if (portType == QExtBPTypes::PortType_In)
        _in = point;
    else
        _out = point;
}

void QExtBPConnectionGraphicsObject::move()
{
    auto moveEnd = [this](QExtBPTypes::ConnectionId cId, QExtBPTypes::PortTypeEnum portType) {
        QExtBPTypes::NodeId nodeId = QExtBPUtils::getNodeId(portType, cId);

        if (nodeId == QExtBPTypes::InvalidNodeId)
            return;

        QExtBPNodeGraphicsObject *ngo = nodeScene()->nodeGraphicsObject(nodeId);

        if (ngo) {
            QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();

            QPointF scenePos = geometry.portScenePosition(nodeId,
                                                          portType,
                                                          QExtBPUtils::getPortIndex(portType, cId),
                                                          ngo->sceneTransform());

            QPointF connectionPos = sceneTransform().inverted().map(scenePos);

            setEndPoint(portType, connectionPos);
        }
    };

    moveEnd(_connectionId, QExtBPTypes::PortType_Out);
    moveEnd(_connectionId, QExtBPTypes::PortType_In);

    prepareGeometryChange();

    update();
}

const QExtBPConnectionState &QExtBPConnectionGraphicsObject::connectionState() const
{
    return _connectionState;
}

QExtBPConnectionState &QExtBPConnectionGraphicsObject::connectionState()
{
    return _connectionState;
}

void QExtBPConnectionGraphicsObject::paint(QPainter *painter,
                                           QStyleOptionGraphicsItem const *option,
                                           QWidget *)
{
    if (!scene())
        return;

    painter->setClipRect(option->exposedRect);

    QExtBPConnectionPainter::paint(painter, *this);
}

void QExtBPConnectionGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void QExtBPConnectionGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();

    auto view = static_cast<QGraphicsView *>(event->widget());
    auto ngo = locateNodeAt(event->scenePos(), *nodeScene(), view->transform());
    if (ngo) {
        ngo->reactToConnection(this);

        _connectionState.setLastHoveredNode(ngo->nodeId());
    } else {
        _connectionState.resetLastHoveredNode();
    }

    //-------------------

    auto requiredPort = _connectionState.requiredPort();

    if (requiredPort != QExtBPTypes::PortType_None) {
        setEndPoint(requiredPort, event->pos());
    }

    //-------------------

    update();

    event->accept();
}

void QExtBPConnectionGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    ungrabMouse();
    event->accept();

    auto view = static_cast<QGraphicsView *>(event->widget());

    Q_ASSERT(view);

    auto ngo = locateNodeAt(event->scenePos(), *nodeScene(), view->transform());

    bool wasConnected = false;

    if (ngo) {
        QExtBPNodeConnectionInteraction interaction(*ngo, *this, *nodeScene());

        wasConnected = interaction.tryConnect();
    }

    // If connection attempt was unsuccessful
    if (!wasConnected) {
        // Resulting unique_ptr is not used and automatically deleted.
        nodeScene()->resetDraftConnection();
    }
}

void QExtBPConnectionGraphicsObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    _connectionState.setHovered(true);

    update();

    // Signal
    emit nodeScene()->connectionHovered(connectionId(), event->screenPos());

    event->accept();
}

void QExtBPConnectionGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _connectionState.setHovered(false);

    update();

    // Signal
    emit nodeScene()->connectionHoverLeft(connectionId());

    event->accept();
}

std::pair<QPointF, QPointF> QExtBPConnectionGraphicsObject::pointsC1C2() const
{
    switch (nodeScene()->orientation()) {
    case Qt::Horizontal:
        return pointsC1C2Horizontal();
        break;

    case Qt::Vertical:
        return pointsC1C2Vertical();
        break;
    }

    throw std::logic_error("Unreachable code after switch statement");
}

void QExtBPConnectionGraphicsObject::addGraphicsEffect()
{
    auto effect = new QGraphicsBlurEffect;

    effect->setBlurRadius(5);
    setGraphicsEffect(effect);

    //auto effect = new QGraphicsDropShadowEffect;
    //auto effect = new ConnectionBlurEffect(this);
    //effect->setOffset(4, 4);
    //effect->setColor(QColor(Qt::gray).darker(800));
}

std::pair<QPointF, QPointF> QExtBPConnectionGraphicsObject::pointsC1C2Horizontal() const
{
    double const defaultOffset = 200;

    double xDistance = _in.x() - _out.x();

    double horizontalOffset = qMin(defaultOffset, std::abs(xDistance));

    double verticalOffset = 0;

    double ratioX = 0.5;

    if (xDistance <= 0) {
        double yDistance = _in.y() - _out.y() + 20;

        double vector = yDistance < 0 ? -1.0 : 1.0;

        verticalOffset = qMin(defaultOffset, std::abs(yDistance)) * vector;

        ratioX = 1.0;
    }

    horizontalOffset *= ratioX;

    QPointF c1(_out.x() + horizontalOffset, _out.y() + verticalOffset);

    QPointF c2(_in.x() - horizontalOffset, _in.y() - verticalOffset);

    return std::make_pair(c1, c2);
}

std::pair<QPointF, QPointF> QExtBPConnectionGraphicsObject::pointsC1C2Vertical() const
{
    double const defaultOffset = 200;

    double yDistance = _in.y() - _out.y();

    double verticalOffset = qMin(defaultOffset, std::abs(yDistance));

    double horizontalOffset = 0;

    double ratioY = 0.5;

    if (yDistance <= 0) {
        double xDistance = _in.x() - _out.x() + 20;

        double vector = xDistance < 0 ? -1.0 : 1.0;

        horizontalOffset = qMin(defaultOffset, std::abs(xDistance)) * vector;

        ratioY = 1.0;
    }

    verticalOffset *= ratioY;

    QPointF c1(_out.x() + horizontalOffset, _out.y() + verticalOffset);

    QPointF c2(_in.x() - horizontalOffset, _in.y() - verticalOffset);

    return std::make_pair(c1, c2);
}

//} // namespace QtNodes
