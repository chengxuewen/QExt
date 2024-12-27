#include <private/qextBPNodeGraphicsObject_p.h>
#include <qextBPNodeConnectionInteraction.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPAbstractNodeGeometry.h>
#include <qextBPAbstractNodePainter.h>
#include <qextBPBasicGraphicsScene.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPStyleCollection.h>
#include <qextBPUndoCommands.h>
#include <qextBPUtils.h>

#include <QtWidgets/QGraphicsEffect>
#include <QtWidgets/QtWidgets>

QExtBPNodeGraphicsObjectPrivate::QExtBPNodeGraphicsObjectPrivate(QExtBPNodeGraphicsObject *q,
                                                                 QExtBPAbstractGraphModel &graphModel)
    : q_ptr(q)
    , m_nodeState(*q)
    , m_proxyWidget(QEXT_NULLPTR)
    , m_graphModel(graphModel)
{
}

QExtBPNodeGraphicsObjectPrivate::~QExtBPNodeGraphicsObjectPrivate()
{
}

QExtBPNodeGraphicsObject::QExtBPNodeGraphicsObject(QExtBPBasicGraphicsScene &scene, QExtBPTypes::NodeId nodeId,
                                                   QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , dd_ptr(new QExtBPNodeGraphicsObjectPrivate(this, scene.graphModel()))
{
    Q_D(QExtBPNodeGraphicsObject);
    d->m_nodeId = nodeId;
    scene.addItem(this);

    this->setFlag(QGraphicsItem::ItemDoesntPropagateOpacityToChildren, true);
    this->setFlag(QGraphicsItem::ItemIsFocusable, true);

    this->setLockedState();

    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    QJsonObject nodeStyleJson = d->m_graphModel.nodeData(d->m_nodeId, QExtBPTypes::NodeRole_Style).toJsonObject();

    QExtBPNodeStyle nodeStyle(nodeStyleJson);

    {
        auto effect = new QGraphicsDropShadowEffect;
        effect->setOffset(4, 4);
        effect->setBlurRadius(20);
        effect->setColor(nodeStyle.ShadowColor);
        this->setGraphicsEffect(effect);
    }

    this->setOpacity(nodeStyle.Opacity);

    this->setAcceptHoverEvents(true);

    this->setZValue(0);

    this->embedQWidget();

    this->nodeScene()->nodeGeometry().recomputeSize(d->m_nodeId);

    const QPointF pos = d->m_graphModel.nodeData<QPointF>(d->m_nodeId, QExtBPTypes::NodeRole_Position);

    this->setPos(pos);

    connect(&d->m_graphModel, &QExtBPAbstractGraphModel::nodeFlagsUpdated, [=](const QExtBPTypes::NodeId nodeId)
            {
                if (d->m_nodeId == nodeId)
                {
                    this->setLockedState();
                }
    });
}

QExtBPNodeGraphicsObject::~QExtBPNodeGraphicsObject()
{
}

QExtBPAbstractGraphModel &QExtBPNodeGraphicsObject::graphModel() const
{
    Q_D(const QExtBPNodeGraphicsObject);
    return d->m_graphModel;
}

QExtBPBasicGraphicsScene *QExtBPNodeGraphicsObject::nodeScene() const
{
    return dynamic_cast<QExtBPBasicGraphicsScene *>(this->scene());
}

QExtBPTypes::NodeId QExtBPNodeGraphicsObject::nodeId()
{
    Q_D(const QExtBPNodeGraphicsObject);
    return d->m_nodeId;
}

QExtBPTypes::NodeId QExtBPNodeGraphicsObject::nodeId() const
{
    Q_D(const QExtBPNodeGraphicsObject);
    return d->m_nodeId;
}

QExtBPNodeState &QExtBPNodeGraphicsObject::nodeState()
{
    Q_D(QExtBPNodeGraphicsObject);
    return d->m_nodeState;
}

const QExtBPNodeState &QExtBPNodeGraphicsObject::nodeState() const
{
    Q_D(const QExtBPNodeGraphicsObject);
    return d->m_nodeState;
}

void QExtBPNodeGraphicsObject::embedQWidget()
{
    Q_D(QExtBPNodeGraphicsObject);
    QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();
    geometry.recomputeSize(d->m_nodeId);

    if (auto w = d->m_graphModel.nodeData(d->m_nodeId, QExtBPTypes::NodeRole_Widget).value<QWidget *>())
    {
        d->m_proxyWidget = new QGraphicsProxyWidget(this);

        d->m_proxyWidget->setWidget(w);

        d->m_proxyWidget->setPreferredWidth(5);

        geometry.recomputeSize(d->m_nodeId);

        if (w->sizePolicy().verticalPolicy() & QSizePolicy::ExpandFlag)
        {
            unsigned int widgetHeight = geometry.size(d->m_nodeId).height()
                                        - geometry.captionRect(d->m_nodeId).height();

            // If the widget wants to use as much vertical space as possible, set
            // it to have the geom's equivalentWidgetHeight.
            d->m_proxyWidget->setMinimumHeight(widgetHeight);
        }

        d->m_proxyWidget->setPos(geometry.widgetPosition(d->m_nodeId));

        //update();

        d->m_proxyWidget->setOpacity(1.0);
        d->m_proxyWidget->setFlag(QGraphicsItem::ItemIgnoresParentOpacity);
    }
}

void QExtBPNodeGraphicsObject::setLockedState()
{
    Q_D(QExtBPNodeGraphicsObject);
    QExtBPTypes::NodeFlagEnums flags = d->m_graphModel.nodeFlags(d->m_nodeId);

    bool const locked = flags.testFlag(QExtBPTypes::NodeFlag_Locked);

    this->setFlag(QGraphicsItem::ItemIsMovable, !locked);
    this->setFlag(QGraphicsItem::ItemIsSelectable, !locked);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, !locked);
}

QRectF QExtBPNodeGraphicsObject::boundingRect() const
{
    Q_D(const QExtBPNodeGraphicsObject);
    QExtBPAbstractNodeGeometry &geometry = this->nodeScene()->nodeGeometry();
    return geometry.boundingRect(d->m_nodeId);
    //return NodeGeometry(_nodeId, _graphModel, nodeScene()).boundingRect();
}

void QExtBPNodeGraphicsObject::setGeometryChanged()
{
    this->prepareGeometryChange();
}

void QExtBPNodeGraphicsObject::moveConnections() const
{
    Q_D(const QExtBPNodeGraphicsObject);
    const auto &connected = d->m_graphModel.allConnectionIds(d->m_nodeId);

    for (auto &cnId : connected)
    {
        auto cgo = nodeScene()->connectionGraphicsObject(cnId);
        if (cgo)
        {
            cgo->move();
        }
    }
}

void QExtBPNodeGraphicsObject::reactToConnection(QExtBPConnectionGraphicsObject const *cgo)
{
    Q_D(QExtBPNodeGraphicsObject);
    d->m_nodeState.storeConnectionForReaction(cgo);
    this->update();
}

void QExtBPNodeGraphicsObject::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *)
{
    painter->setClipRect(option->exposedRect);
    this->nodeScene()->nodePainter().paint(painter, *this);
}

QVariant QExtBPNodeGraphicsObject::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged && this->scene())
    {
        this->moveConnections();
    }
    return QGraphicsObject::itemChange(change, value);
}

void QExtBPNodeGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    //if (_nodeState.locked())
    //return;

    QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();

    for (QExtBPTypes::PortTypeEnum portToCheck : {QExtBPTypes::PortType_In, QExtBPTypes::PortType_Out})
    {
        QPointF nodeCoord = sceneTransform().inverted().map(event->scenePos());

        const QExtBPTypes::PortIndex portIndex = geometry.checkPortHit(d->m_nodeId, portToCheck, nodeCoord);

        if (portIndex == QExtBPTypes::InvalidPortIndex)
        {
            continue;
        }

        const auto &connected = d->m_graphModel.connections(d->m_nodeId, portToCheck, portIndex);

        // Start dragging existing connection.
        if (!connected.empty() && portToCheck == QExtBPTypes::PortType_In)
        {
            const auto &cnId = *connected.begin();

            // Need ConnectionGraphicsObject

            QExtBPNodeConnectionInteraction interaction(*this,
                                                        *nodeScene()->connectionGraphicsObject(cnId),
                                                        *nodeScene());

            if (d->m_graphModel.detachPossible(cnId))
            {
                interaction.disconnect(portToCheck);
            }
        }
        else // initialize new Connection
        {
            if (portToCheck == QExtBPTypes::PortType_Out)
            {
                auto const outPolicy = d->m_graphModel
                                           .portData(d->m_nodeId,
                                                     portToCheck,
                                                     portIndex,
                                                     QExtBPTypes::PortRole_ConnectionPolicyRole)
                                           .value<QExtBPTypes::ConnectionPolicyEnum>();

                if (!connected.empty() && outPolicy == QExtBPTypes::ConnectionPolicy_One)
                {
                    for (auto &cnId : connected)
                    {
                        d->m_graphModel.deleteConnection(cnId);
                    }
                }
            } // if port == out

            const QExtBPTypes::ConnectionId incompleteConnectionId = QExtBPUtils::makeIncompleteConnectionId(d->m_nodeId,
                                                                                                             portToCheck,
                                                                                                             portIndex);

            this->nodeScene()->makeDraftConnection(incompleteConnectionId);
        }
    }

    if (d->m_graphModel.nodeFlags(d->m_nodeId) & QExtBPTypes::NodeFlag_Resizable)
    {
        auto pos = event->pos();
        bool const hit = geometry.resizeHandleRect(d->m_nodeId).contains(QPoint(pos.x(), pos.y()));
        d->m_nodeState.setResizing(hit);
    }

    QGraphicsObject::mousePressEvent(event);

    if (this->isSelected())
    {
        Q_EMIT this->nodeScene()->nodeSelected(d->m_nodeId);
    }
}

void QExtBPNodeGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    // Deselect all other items after this one is selected.
    // Unless we press a CTRL button to add the item to the selected group before
    // starting moving.
    if (!this->isSelected())
    {
        if (!event->modifiers().testFlag(Qt::ControlModifier))
        {
            this->scene()->clearSelection();
        }

        this->setSelected(true);
    }

    if (d->m_nodeState.resizing())
    {
        auto diff = event->pos() - event->lastPos();

        if (auto w = d->m_graphModel.nodeData<QWidget *>(d->m_nodeId, QExtBPTypes::NodeRole_Widget))
        {
            this->prepareGeometryChange();

            auto oldSize = w->size();

            oldSize += QSize(diff.x(), diff.y());

            w->resize(oldSize);

            QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();

            // Passes the new size to the model.
            geometry.recomputeSize(d->m_nodeId);

            this->update();

            this->moveConnections();

            event->accept();
        }
    }
    else
    {
        auto diff = event->pos() - event->lastPos();

        this->nodeScene()->undoStack().push(new QExtBPMoveNodeCommand(this->nodeScene(), diff));

        event->accept();
    }

    QRectF r = this->nodeScene()->sceneRect();

    r = r.united(this->mapToScene(boundingRect()).boundingRect());

    this->nodeScene()->setSceneRect(r);
}

void QExtBPNodeGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    d->m_nodeState.setResizing(false);

    QGraphicsObject::mouseReleaseEvent(event);

    // position connections precisely after fast node move
    this->moveConnections();

    nodeScene()->nodeClicked(d->m_nodeId);
}

void QExtBPNodeGraphicsObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    // bring all the colliding nodes to background
    QList<QGraphicsItem *> overlapItems = this->collidingItems();

    for (QGraphicsItem *item : overlapItems)
    {
        if (item->zValue() > 0.0)
        {
            item->setZValue(0.0);
        }
    }

    // bring this node forward
    this->setZValue(1.0);

    d->m_nodeState.setHovered(true);

    this->update();

    Q_EMIT this->nodeScene()->nodeHovered(d->m_nodeId, event->screenPos());

    event->accept();
}

void QExtBPNodeGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    d->m_nodeState.setHovered(false);

    this->setZValue(0.0);

    this->update();

    Q_EMIT this->nodeScene()->nodeHoverLeft(d->m_nodeId);

    event->accept();
}

void QExtBPNodeGraphicsObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    auto pos = event->pos();

    //NodeGeometry geometry(_nodeId, _graphModel, nodeScene());
    QExtBPAbstractNodeGeometry &geometry = this->nodeScene()->nodeGeometry();

    if ((d->m_graphModel.nodeFlags(d->m_nodeId) | QExtBPTypes::NodeFlag_Resizable)
        && geometry.resizeHandleRect(d->m_nodeId).contains(QPoint(pos.x(), pos.y())))
    {
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else
    {
        this->setCursor(QCursor());
    }

    event->accept();
}

void QExtBPNodeGraphicsObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    QGraphicsItem::mouseDoubleClickEvent(event);

    Q_EMIT this->nodeScene()->nodeDoubleClicked(d->m_nodeId);
}

void QExtBPNodeGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_D(QExtBPNodeGraphicsObject);
    Q_EMIT this->nodeScene()->nodeContextMenu(d->m_nodeId, this->mapToScene(event->pos()));
}
