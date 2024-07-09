#include "NodeGraphicsObject.hpp"

#include <cstdlib>
#include <iostream>

#include <QtWidgets/QGraphicsEffect>
#include <QtWidgets/QtWidgets>

#include "AbstractGraphModel.hpp"
#include "AbstractNodeGeometry.hpp"
#include "AbstractNodePainter.hpp"
#include "BasicGraphicsScene.hpp"
#include "ConnectionGraphicsObject.hpp"
#include "ConnectionIdUtils.hpp"
#include "NodeConnectionInteraction.hpp"
#include "StyleCollection.hpp"
#include "UndoCommands.hpp"

QExtBPNodeGraphicsObject::QExtBPNodeGraphicsObject(QExtBPBasicGraphicsScene &scene, QExtBPTypes::NodeId nodeId)
    : _nodeId(nodeId)
    , _graphModel(scene.graphModel())
    , _nodeState(*this)
    , _proxyWidget(nullptr)
{
    scene.addItem(this);

    setFlag(QGraphicsItem::ItemDoesntPropagateOpacityToChildren, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    setLockedState();

    setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    QJsonObject nodeStyleJson = _graphModel.nodeData(_nodeId, QExtBPTypes::NodeRole_Style).toJsonObject();

    QExtBPNodeStyle nodeStyle(nodeStyleJson);

    {
        auto effect = new QGraphicsDropShadowEffect;
        effect->setOffset(4, 4);
        effect->setBlurRadius(20);
        effect->setColor(nodeStyle.ShadowColor);

        setGraphicsEffect(effect);
    }

    setOpacity(nodeStyle.Opacity);

    setAcceptHoverEvents(true);

    setZValue(0);

    embedQWidget();

    nodeScene()->nodeGeometry().recomputeSize(_nodeId);

    QPointF const pos = _graphModel.nodeData<QPointF>(_nodeId, QExtBPTypes::NodeRole_Position);

    setPos(pos);

    connect(&_graphModel, &QExtBPAbstractGraphModel::nodeFlagsUpdated, [this](QExtBPTypes::NodeId const nodeId) {
        if (_nodeId == nodeId)
            setLockedState();
    });
}

QExtBPAbstractGraphModel &QExtBPNodeGraphicsObject::graphModel() const
{
    return _graphModel;
}

QExtBPBasicGraphicsScene *QExtBPNodeGraphicsObject::nodeScene() const
{
    return dynamic_cast<QExtBPBasicGraphicsScene *>(scene());
}

void QExtBPNodeGraphicsObject::embedQWidget()
{
    QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();
    geometry.recomputeSize(_nodeId);

    if (auto w = _graphModel.nodeData(_nodeId, QExtBPTypes::NodeRole_Widget).value<QWidget *>()) {
        _proxyWidget = new QGraphicsProxyWidget(this);

        _proxyWidget->setWidget(w);

        _proxyWidget->setPreferredWidth(5);

        geometry.recomputeSize(_nodeId);

        if (w->sizePolicy().verticalPolicy() & QSizePolicy::ExpandFlag) {
            unsigned int widgetHeight = geometry.size(_nodeId).height()
                    - geometry.captionRect(_nodeId).height();

            // If the widget wants to use as much vertical space as possible, set
            // it to have the geom's equivalentWidgetHeight.
            _proxyWidget->setMinimumHeight(widgetHeight);
        }

        _proxyWidget->setPos(geometry.widgetPosition(_nodeId));

        //update();

        _proxyWidget->setOpacity(1.0);
        _proxyWidget->setFlag(QGraphicsItem::ItemIgnoresParentOpacity);
    }
}

void QExtBPNodeGraphicsObject::setLockedState()
{
    QExtBPTypes::NodeFlagEnums flags = _graphModel.nodeFlags(_nodeId);

    bool const locked = flags.testFlag(QExtBPTypes::NodeFlag_Locked);

    setFlag(QGraphicsItem::ItemIsMovable, !locked);
    setFlag(QGraphicsItem::ItemIsSelectable, !locked);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, !locked);
}

QRectF QExtBPNodeGraphicsObject::boundingRect() const
{
    QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();
    return geometry.boundingRect(_nodeId);
    //return NodeGeometry(_nodeId, _graphModel, nodeScene()).boundingRect();
}

void QExtBPNodeGraphicsObject::setGeometryChanged()
{
    prepareGeometryChange();
}

void QExtBPNodeGraphicsObject::moveConnections() const
{
    auto const &connected = _graphModel.allConnectionIds(_nodeId);

    for (auto &cnId : connected) {
        auto cgo = nodeScene()->connectionGraphicsObject(cnId);

        if (cgo)
            cgo->move();
    }
}

void QExtBPNodeGraphicsObject::reactToConnection(QExtBPConnectionGraphicsObject const *cgo)
{
    _nodeState.storeConnectionForReaction(cgo);

    update();
}

void QExtBPNodeGraphicsObject::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *)
{
    painter->setClipRect(option->exposedRect);

    nodeScene()->nodePainter().paint(painter, *this);
}

QVariant QExtBPNodeGraphicsObject::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged && scene()) {
        moveConnections();
    }

    return QGraphicsObject::itemChange(change, value);
}

void QExtBPNodeGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //if (_nodeState.locked())
    //return;

    QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();

    for (QExtBPTypes::PortTypeEnum portToCheck : {QExtBPTypes::PortType_In, QExtBPTypes::PortType_Out}) {
        QPointF nodeCoord = sceneTransform().inverted().map(event->scenePos());

        QExtBPTypes::PortIndex const portIndex = geometry.checkPortHit(_nodeId, portToCheck, nodeCoord);

        if (portIndex == QExtBPTypes::InvalidPortIndex)
            continue;

        auto const &connected = _graphModel.connections(_nodeId, portToCheck, portIndex);

        // Start dragging existing connection.
        if (!connected.empty() && portToCheck == QExtBPTypes::PortType_In) {
            auto const &cnId = *connected.begin();

            // Need ConnectionGraphicsObject

            QExtBPNodeConnectionInteraction interaction(*this,
                                                           *nodeScene()->connectionGraphicsObject(cnId),
                                                           *nodeScene());

            if (_graphModel.detachPossible(cnId))
                interaction.disconnect(portToCheck);
        } else // initialize new Connection
        {
            if (portToCheck == QExtBPTypes::PortType_Out) {
                auto const outPolicy = _graphModel
                        .portData(_nodeId,
                                  portToCheck,
                                  portIndex,
                                  QExtBPTypes::PortRole_ConnectionPolicyRole)
                        .value<QExtBPTypes::ConnectionPolicyEnum>();

                if (!connected.empty() && outPolicy == QExtBPTypes::ConnectionPolicy_One) {
                    for (auto &cnId : connected) {
                        _graphModel.deleteConnection(cnId);
                    }
                }
            } // if port == out

            QExtBPTypes::ConnectionId const incompleteConnectionId = QExtBPUtils::makeIncompleteConnectionId(_nodeId,
                                                                                                         portToCheck,
                                                                                                         portIndex);

            nodeScene()->makeDraftConnection(incompleteConnectionId);
        }
    }

    if (_graphModel.nodeFlags(_nodeId) & QExtBPTypes::NodeFlag_Resizable) {
        auto pos = event->pos();
        bool const hit = geometry.resizeHandleRect(_nodeId).contains(QPoint(pos.x(), pos.y()));
        _nodeState.setResizing(hit);
    }

    QGraphicsObject::mousePressEvent(event);

    if (isSelected()) {
        Q_EMIT nodeScene()->nodeSelected(_nodeId);
    }
}

void QExtBPNodeGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Deselect all other items after this one is selected.
    // Unless we press a CTRL button to add the item to the selected group before
    // starting moving.
    if (!isSelected()) {
        if (!event->modifiers().testFlag(Qt::ControlModifier))
            scene()->clearSelection();

        setSelected(true);
    }

    if (_nodeState.resizing()) {
        auto diff = event->pos() - event->lastPos();

        if (auto w = _graphModel.nodeData<QWidget *>(_nodeId, QExtBPTypes::NodeRole_Widget)) {
            prepareGeometryChange();

            auto oldSize = w->size();

            oldSize += QSize(diff.x(), diff.y());

            w->resize(oldSize);

            QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();

            // Passes the new size to the model.
            geometry.recomputeSize(_nodeId);

            update();

            moveConnections();

            event->accept();
        }
    } else {
        auto diff = event->pos() - event->lastPos();

        nodeScene()->undoStack().push(new QExtBPMoveNodeCommand(nodeScene(), diff));

        event->accept();
    }

    QRectF r = nodeScene()->sceneRect();

    r = r.united(mapToScene(boundingRect()).boundingRect());

    nodeScene()->setSceneRect(r);
}

void QExtBPNodeGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    _nodeState.setResizing(false);

    QGraphicsObject::mouseReleaseEvent(event);

    // position connections precisely after fast node move
    moveConnections();

    nodeScene()->nodeClicked(_nodeId);
}

void QExtBPNodeGraphicsObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // bring all the colliding nodes to background
    QList<QGraphicsItem *> overlapItems = collidingItems();

    for (QGraphicsItem *item : overlapItems) {
        if (item->zValue() > 0.0) {
            item->setZValue(0.0);
        }
    }

    // bring this node forward
    setZValue(1.0);

    _nodeState.setHovered(true);

    update();

    Q_EMIT nodeScene()->nodeHovered(_nodeId, event->screenPos());

    event->accept();
}

void QExtBPNodeGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _nodeState.setHovered(false);

    setZValue(0.0);

    update();

    Q_EMIT nodeScene()->nodeHoverLeft(_nodeId);

    event->accept();
}

void QExtBPNodeGraphicsObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    auto pos = event->pos();

    //NodeGeometry geometry(_nodeId, _graphModel, nodeScene());
    QExtBPAbstractNodeGeometry &geometry = nodeScene()->nodeGeometry();

    if ((_graphModel.nodeFlags(_nodeId) | QExtBPTypes::NodeFlag_Resizable)
            && geometry.resizeHandleRect(_nodeId).contains(QPoint(pos.x(), pos.y()))) {
        setCursor(QCursor(Qt::SizeFDiagCursor));
    } else {
        setCursor(QCursor());
    }

    event->accept();
}

void QExtBPNodeGraphicsObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);

    Q_EMIT nodeScene()->nodeDoubleClicked(_nodeId);
}

void QExtBPNodeGraphicsObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_EMIT nodeScene()->nodeContextMenu(_nodeId, mapToScene(event->pos()));
}
