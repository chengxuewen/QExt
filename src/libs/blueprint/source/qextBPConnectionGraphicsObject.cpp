#include <private/qextBPConnectionGraphicsObject_p.h>
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

QExtBPConnectionGraphicsObjectPrivate::QExtBPConnectionGraphicsObjectPrivate(QExtBPConnectionGraphicsObject *q,
                                                                             QExtBPAbstractGraphModel &graphModel)
    : q_ptr(q)
    , m_in{0, 0}
    , m_out{0, 0}
    , m_graphModel(graphModel)
    , m_connectionState(*q)
{
}

QExtBPConnectionGraphicsObjectPrivate::~QExtBPConnectionGraphicsObjectPrivate()
{
}

QExtBPConnectionGraphicsObject::QExtBPConnectionGraphicsObject(QExtBPBasicGraphicsScene &scene,
                                                               const QExtBPTypes::ConnectionId connectionId,
                                                               QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , dd_ptr(new QExtBPConnectionGraphicsObjectPrivate(this, scene.graphModel()))
{
    Q_D(QExtBPConnectionGraphicsObject);
    d->m_connectionId = connectionId;
    scene.addItem(this);

    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);

    this->setAcceptHoverEvents(true);
    //addGraphicsEffect();
    this->setZValue(-1.0);
    this->initializePosition();
}

QExtBPConnectionGraphicsObject::~QExtBPConnectionGraphicsObject()
{
}

void QExtBPConnectionGraphicsObject::initializePosition()
{
    Q_D(QExtBPConnectionGraphicsObject);
    // This function is only called when the ConnectionGraphicsObject
    // is newly created. At this moment both end coordinates are (0, 0)
    // in Connection G.O. coordinates. The position of the whole
    // Connection G. O. in scene coordinate system is also (0, 0).
    // By moving the whole object to the Node Port position
    // we position both connection ends correctly.

    if (d->m_connectionState.requiredPort() != QExtBPTypes::PortType_None)
    {
        QExtBPTypes::PortTypeEnum attachedPort = QExtBPUtils::oppositePort(d->m_connectionState.requiredPort());

        QExtBPTypes::PortIndex portIndex = QExtBPUtils::getPortIndex(attachedPort, d->m_connectionId);
        QExtBPTypes::NodeId nodeId = QExtBPUtils::getNodeId(attachedPort, d->m_connectionId);

        QExtBPNodeGraphicsObject *ngo = this->nodeScene()->nodeGraphicsObject(nodeId);

        if (ngo)
        {
            QTransform nodeSceneTransform = ngo->sceneTransform();

            QExtBPAbstractNodeGeometry &geometry = this->nodeScene()->nodeGeometry();

            QPointF pos = geometry.portScenePosition(nodeId,
                                                     attachedPort,
                                                     portIndex,
                                                     nodeSceneTransform);

            this->setPos(pos);
        }
    }

    this->move();
}

QExtBPAbstractGraphModel &QExtBPConnectionGraphicsObject::graphModel() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    return d->m_graphModel;
}

QExtBPBasicGraphicsScene *QExtBPConnectionGraphicsObject::nodeScene() const
{
    return dynamic_cast<QExtBPBasicGraphicsScene *>(scene());
}

const QExtBPTypes::ConnectionId &QExtBPConnectionGraphicsObject::connectionId() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    return d->m_connectionId;
}

QRectF QExtBPConnectionGraphicsObject::boundingRect() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    auto points = this->pointsC1C2();

    // `normalized()` fixes inverted rects.
    QRectF basicRect = QRectF(d->m_out, d->m_in).normalized();

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
    Q_D(const QExtBPConnectionGraphicsObject);
    Q_ASSERT(portType != QExtBPTypes::PortType_None);

    return (portType == QExtBPTypes::PortType_Out ? d->m_out : d->m_in);
}

QPointF QExtBPConnectionGraphicsObject::out() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    return d->m_out;
}

QPointF QExtBPConnectionGraphicsObject::in() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    return d->m_in;
}

void QExtBPConnectionGraphicsObject::setEndPoint(QExtBPTypes::PortTypeEnum portType, const QPointF &point)
{
    Q_D(QExtBPConnectionGraphicsObject);
    if (portType == QExtBPTypes::PortType_In)
    {
        d->m_in = point;
    }
    else
    {
        d->m_out = point;
    }
}

void QExtBPConnectionGraphicsObject::move()
{
    Q_D(QExtBPConnectionGraphicsObject);
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

    moveEnd(d->m_connectionId, QExtBPTypes::PortType_Out);
    moveEnd(d->m_connectionId, QExtBPTypes::PortType_In);

    this->prepareGeometryChange();

    this->update();
}

const QExtBPConnectionState &QExtBPConnectionGraphicsObject::connectionState() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    return d->m_connectionState;
}

QExtBPConnectionState &QExtBPConnectionGraphicsObject::connectionState()
{
    Q_D(QExtBPConnectionGraphicsObject);
    return d->m_connectionState;
}

void QExtBPConnectionGraphicsObject::paint(QPainter *painter,
                                           QStyleOptionGraphicsItem const *option,
                                           QWidget *)
{
    if (!this->scene())
    {
        return;
    }

    painter->setClipRect(option->exposedRect);

    QExtBPConnectionPainter::paint(painter, *this);
}

void QExtBPConnectionGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void QExtBPConnectionGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(QExtBPConnectionGraphicsObject);
    this->prepareGeometryChange();

    auto view = static_cast<QGraphicsView *>(event->widget());
    auto ngo = QExtBPLocateNode::locateNodeAt(event->scenePos(), *nodeScene(), view->transform());
    if (ngo)
    {
        ngo->reactToConnection(this);

        d->m_connectionState.setLastHoveredNode(ngo->nodeId());
    }
    else
    {
        d->m_connectionState.resetLastHoveredNode();
    }

    //-------------------

    auto requiredPort = d->m_connectionState.requiredPort();

    if (requiredPort != QExtBPTypes::PortType_None)
    {
        this->setEndPoint(requiredPort, event->pos());
    }

    //-------------------

    this->update();

    event->accept();
}

void QExtBPConnectionGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    this->ungrabMouse();
    event->accept();

    auto view = static_cast<QGraphicsView *>(event->widget());

    Q_ASSERT(view);

    auto ngo = QExtBPLocateNode::locateNodeAt(event->scenePos(), *nodeScene(), view->transform());

    bool wasConnected = false;

    if (ngo)
    {
        QExtBPNodeConnectionInteraction interaction(*ngo, *this, *nodeScene());

        wasConnected = interaction.tryConnect();
    }

    // If connection attempt was unsuccessful
    if (!wasConnected)
    {
        // Resulting unique_ptr is not used and automatically deleted.
        nodeScene()->resetDraftConnection();
    }
}

void QExtBPConnectionGraphicsObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(QExtBPConnectionGraphicsObject);
    d->m_connectionState.setHovered(true);

    this->update();

    // Signal
    emit this->nodeScene()->connectionHovered(connectionId(), event->screenPos());

    event->accept();
}

void QExtBPConnectionGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(QExtBPConnectionGraphicsObject);
    d->m_connectionState.setHovered(false);

    this->update();

    // Signal
    emit this->nodeScene()->connectionHoverLeft(this->connectionId());

    event->accept();
}

std::pair<QPointF, QPointF> QExtBPConnectionGraphicsObject::pointsC1C2() const
{
    switch (nodeScene()->orientation())
    {
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
    this->setGraphicsEffect(effect);

    //auto effect = new QGraphicsDropShadowEffect;
    //auto effect = new ConnectionBlurEffect(this);
    //effect->setOffset(4, 4);
    //effect->setColor(QColor(Qt::gray).darker(800));
}

std::pair<QPointF, QPointF> QExtBPConnectionGraphicsObject::pointsC1C2Horizontal() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    double const defaultOffset = 200;

    double xDistance = d->m_in.x() - d->m_out.x();

    double horizontalOffset = qMin(defaultOffset, std::abs(xDistance));

    double verticalOffset = 0;

    double ratioX = 0.5;

    if (xDistance <= 0)
    {
        double yDistance = d->m_in.y() - d->m_out.y() + 20;

        double vector = yDistance < 0 ? -1.0 : 1.0;

        verticalOffset = qMin(defaultOffset, std::abs(yDistance)) * vector;

        ratioX = 1.0;
    }

    horizontalOffset *= ratioX;

    QPointF c1(d->m_out.x() + horizontalOffset, d->m_out.y() + verticalOffset);

    QPointF c2(d->m_in.x() - horizontalOffset, d->m_in.y() - verticalOffset);

    return std::make_pair(c1, c2);
}

std::pair<QPointF, QPointF> QExtBPConnectionGraphicsObject::pointsC1C2Vertical() const
{
    Q_D(const QExtBPConnectionGraphicsObject);
    double const defaultOffset = 200;

    double yDistance = d->m_in.y() - d->m_out.y();

    double verticalOffset = qMin(defaultOffset, std::abs(yDistance));

    double horizontalOffset = 0;

    double ratioY = 0.5;

    if (yDistance <= 0)
    {
        double xDistance = d->m_in.x() - d->m_out.x() + 20;

        double vector = xDistance < 0 ? -1.0 : 1.0;

        horizontalOffset = qMin(defaultOffset, std::abs(xDistance)) * vector;

        ratioY = 1.0;
    }

    verticalOffset *= ratioY;

    QPointF c1(d->m_out.x() + horizontalOffset, d->m_out.y() + verticalOffset);

    QPointF c2(d->m_in.x() - horizontalOffset, d->m_in.y() - verticalOffset);

    return std::make_pair(c1, c2);
}
