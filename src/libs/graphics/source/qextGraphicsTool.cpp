#include <qextGraphicsTool.h>
#include <qextGraphicsScene.h>

#include <QDebug>
#include <QtMath>
#include <QGlobalStatic>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>

#define PI 3.1416

QList<QExtGraphicsTool*> QExtGraphicsTool::sm_tools;
QPointF QExtGraphicsTool::sm_down;
QPointF QExtGraphicsTool::sm_last;
quint32 QExtGraphicsTool::sm_nDownFlags;

DrawShape QExtGraphicsTool::sm_drawShape = selection;

Q_GLOBAL_STATIC(QExtGraphicsSelectTool, sg_selectTool)

// static QExtGraphicsSelectTool selectTool;
static QExtGraphicsRectTool   rectTool(rectangle);
static QExtGraphicsRectTool   roundRectTool(roundrect);
static QExtGraphicsRectTool   ellipseTool(ellipse);
static QExtGraphicsPolygonTool lineTool(line);
static QExtGraphicsPolygonTool polygonTool(polygon);
static QExtGraphicsPolygonTool bezierTool(bezier);
static QExtGraphicsPolygonTool polylineTool(polyline);
static QExtGraphicsRotationTool rotationTool;

enum SelectMode
{
    none,
    netSelect,
    move,
    size,
    rotate,
    editor,
};

SelectMode selectMode = none;

int nDragHandle = QExtGraphicsSizeHandle::Handle_None;

static void qextSetCursor(QExtGraphicsScene *scene, const QCursor &cursor)
{
    QGraphicsView *view = scene->view();
    if (view)
    {
        view->setCursor(cursor);
    }
}

QExtGraphicsTool::QExtGraphicsTool(DrawShape shape)
{
    m_drawShape = shape;
    m_hoverSizer = false;
    sm_tools.push_back(this);
}

void QExtGraphicsTool::mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    sm_down = event->scenePos();
    sm_last = event->scenePos();
}

void QExtGraphicsTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    sm_last = event->scenePos();
}

void QExtGraphicsTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    if (event->scenePos() == sm_down)
    {
        sm_drawShape = selection;
    }
    qextSetCursor(scene, Qt::ArrowCursor);
}

void QExtGraphicsTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{

}

QExtGraphicsTool *QExtGraphicsTool::findTool(DrawShape drawShape)
{
    QList<QExtGraphicsTool*>::const_iterator iter;
    for (iter = sm_tools.constBegin(); iter != sm_tools.constEnd(); ++iter)
    {
        if ((*iter)->m_drawShape == drawShape)
        {
            return (*iter);
        }
    }
    return QEXT_NULLPTR;
}

QExtGraphicsSelectTool::QExtGraphicsSelectTool()
    : QExtGraphicsTool(selection)
{
    m_dashRect = QEXT_NULLPTR;
    m_selLayer = QEXT_NULLPTR;
    m_opposite = QPointF();
}

void QExtGraphicsSelectTool::mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mousePressEvent(event,scene);

    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    if (!m_hoverSizer)
    {
        scene->mouseEvent(event);
    }

    nDragHandle = QExtGraphicsSizeHandle::Handle_None;
    selectMode = none;
    QList<QGraphicsItem *> items = scene->selectedItems();
    QExtGraphicsAbstractShapeItem *item = QEXT_NULLPTR;

    if (items.count() == 1)
    {
        item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(items.first());
    }

    if (item != QEXT_NULLPTR)
    {

        nDragHandle = item->collidesWithHandle(event->scenePos());
        if (nDragHandle != QExtGraphicsSizeHandle::Handle_None && nDragHandle <= QExtGraphicsSizeHandle::Handle_Left)
        {
            selectMode = size;
        }
        else if (nDragHandle > QExtGraphicsSizeHandle::Handle_Left)
        {
            selectMode = editor;
        }
        else
        {
            selectMode =  move;
        }

        if (nDragHandle!= QExtGraphicsSizeHandle::Handle_None && nDragHandle <= QExtGraphicsSizeHandle::Handle_Left)
        {
            m_opposite = item->opposite(nDragHandle);
            if(m_opposite.x() == 0)
            {
                m_opposite.setX(1);
            }
            if (m_opposite.y() == 0)
            {
                m_opposite.setY(1);
            }
        }

        qextSetCursor(scene, Qt::ClosedHandCursor);
    }
    else if (items.count() > 1)
    {
        selectMode =  move;
    }

    if(selectMode == none)
    {
        selectMode = netSelect;
        if (scene->view())
        {
            QGraphicsView *view = scene->view();
            view->setDragMode(QGraphicsView::RubberBandDrag);
        }
#if 0
        if (selLayer)
        {
            scene->destroyGroup(selLayer);
            selLayer = 0;
        }
#endif
    }

    if (selectMode == move && items.count() == 1)
    {

        if (m_dashRect)
        {
            scene->removeItem(m_dashRect);
            delete m_dashRect;
            m_dashRect = 0;
        }

        m_dashRect = new QGraphicsPathItem(item->shape());
        m_dashRect->setPen(Qt::DashLine);
        m_dashRect->setPos(item->pos());
        m_dashRect->setTransformOriginPoint(item->transformOriginPoint());
        m_dashRect->setTransform(item->transform());
        m_dashRect->setRotation(item->rotation());
        m_dashRect->setScale(item->scale());
        m_dashRect->setZValue(item->zValue());
        scene->addItem(m_dashRect);

        m_initialPositions = item->pos();
    }
}

void QExtGraphicsSelectTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mouseMoveEvent(event,scene);
    QList<QGraphicsItem *> items = scene->selectedItems();
    QExtGraphicsAbstractShapeItem *item = QEXT_NULLPTR;
    if (items.count() == 1)
    {
        item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(items.first());
        if (item != QEXT_NULLPTR)
        {
            if (nDragHandle != QExtGraphicsSizeHandle::Handle_None && selectMode == size)
            {
                if (m_opposite.isNull())
                {
                    m_opposite = item->opposite(nDragHandle);
                    if(m_opposite.x() == 0)
                    {
                        m_opposite.setX(1);
                    }
                    if (m_opposite.y() == 0)
                    {
                        m_opposite.setY(1);
                    }
                }

                QPointF new_delta = item->mapFromScene(sm_last) - m_opposite;
                QPointF initial_delta = item->mapFromScene(sm_down) - m_opposite;

                double sx = new_delta.x() / initial_delta.x();
                double sy = new_delta.y() / initial_delta.y();

                item->stretch(nDragHandle, sx , sy , m_opposite);

                emit scene->itemResize(item,nDragHandle,QPointF(sx,sy));

                //  qDebug()<<"scale:"<<nDragHandle<< item->mapToScene(opposite_)<< sx << " ，" << sy
                //         << new_delta << item->mapFromScene(c_last)
                //         << initial_delta << item->mapFromScene(c_down) << item->boundingRect();

            }
            else if (nDragHandle > QExtGraphicsSizeHandle::Handle_Left  && selectMode == editor)
            {
                item->control(nDragHandle,sm_last);
                emit scene->itemControl(item,nDragHandle, sm_last,sm_down);
            }
            else if(nDragHandle == QExtGraphicsSizeHandle::Handle_None)
            {
                int handle = item->collidesWithHandle(event->scenePos());
                if (handle != QExtGraphicsSizeHandle::Handle_None)
                {
                    qextSetCursor(scene, Qt::OpenHandCursor);
                    m_hoverSizer = true;
                }
                else
                {
                    qextSetCursor(scene, Qt::ArrowCursor);
                    m_hoverSizer = false;
                }
            }
        }
    }

    if (selectMode == move)
    {
        qextSetCursor(scene, Qt::ClosedHandCursor);
        if (m_dashRect)
        {
            m_dashRect->setPos(m_initialPositions + sm_last - sm_down);
        }
    }

    if (selectMode != size  && items.count() > 1)
    {
        scene->mouseEvent(event);
    }
}

void QExtGraphicsSelectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{

    QExtGraphicsTool::mouseReleaseEvent(event,scene);

    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1)
    {
        QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(items.first());
        if (item != QEXT_NULLPTR  && selectMode == move && sm_last != sm_down)
        {
            item->setPos(m_initialPositions + sm_last - sm_down);
            emit scene->itemMoved(item, sm_last - sm_down);
        }
        else if (item !=0 && (selectMode == size || selectMode ==editor) && sm_last != sm_down)
        {
            item->updateCoordinate();
        }
    }
    else if (items.count() > 1 && selectMode == move && sm_last != sm_down)
    {
        emit scene->itemMoved(NULL, sm_last - sm_down);
    }

    if (selectMode == netSelect)
    {
        if (scene->view())
        {
            QGraphicsView *view = scene->view();
            view->setDragMode(QGraphicsView::NoDrag);
        }
#if 0
        if ( scene->selectedItems().count() > 1 )
        {
            selLayer = scene->createGroup(scene->selectedItems());
            selLayer->setSelected(true);
        }
#endif
    }
    if (m_dashRect)
    {
        scene->removeItem(m_dashRect);
        delete m_dashRect;
        m_dashRect = QEXT_NULLPTR;
    }
    selectMode = none;
    nDragHandle = QExtGraphicsSizeHandle::Handle_None;
    m_hoverSizer = false;
    m_opposite = QPointF();
    scene->mouseEvent(event);
}

QExtGraphicsRotationTool::QExtGraphicsRotationTool()
    : QExtGraphicsTool(rotation)
{
    m_lastAngle = 0;
    m_dashRect = QEXT_NULLPTR;
}

void QExtGraphicsRotationTool::mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mousePressEvent(event,scene);
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    if (!m_hoverSizer)
    {
        scene->mouseEvent(event);
    }

    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1)
    {
        QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(items.first());
        if (item != QEXT_NULLPTR)
        {
            nDragHandle = item->collidesWithHandle(event->scenePos());
            if (nDragHandle != QExtGraphicsSizeHandle::Handle_None)
            {
                QPointF origin = item->mapToScene(item->boundingRect().center());

                qreal len_y = sm_last.y() - origin.y();
                qreal len_x = sm_last.x() - origin.x();

                qreal angle = atan2(len_y, len_x) * 180 / PI;

                m_lastAngle = angle;
                selectMode = rotate;

                if (m_dashRect)
                {
                    scene->removeItem(m_dashRect);
                    delete m_dashRect;
                    m_dashRect = QEXT_NULLPTR;
                }

                m_dashRect = new QGraphicsPathItem(item->shape());
                m_dashRect->setPen(Qt::DashLine);
                m_dashRect->setPos(item->pos());
                m_dashRect->setTransformOriginPoint(item->transformOriginPoint());
                m_dashRect->setTransform(item->transform());
                m_dashRect->setRotation(item->rotation());
                m_dashRect->setScale(item->scale());
                m_dashRect->setZValue(item->zValue());
                scene->addItem(m_dashRect);
                qextSetCursor(scene,QCursor((QPixmap(":/icons/rotate.png"))));
            }
            else
            {
                sm_drawShape = selection;
                sg_selectTool->mousePressEvent(event,scene);
            }
        }
    }
}

void QExtGraphicsRotationTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mouseMoveEvent(event,scene);
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1)
    {
        QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(items.first());
        if ( item != QEXT_NULLPTR && nDragHandle != QExtGraphicsSizeHandle::Handle_None && selectMode == rotate)
        {
            QPointF origin = item->mapToScene(item->boundingRect().center());

            qreal len_y = sm_last.y() - origin.y();
            qreal len_x = sm_last.x() - origin.x();
            qreal angle = atan2(len_y, len_x) * 180 / PI;

            angle = item->rotation() + int(angle - m_lastAngle);

            if (angle > 360)
            {
                angle -= 360;
            }
            if (angle < -360)
            {
                angle += 360;
            }

            if (m_dashRect)
            {
                //dashRect->setTransform(QTransform::fromTranslate(15,15),true);
                //dashRect->setTransform(QTransform().rotate(angle));
                //dashRect->setTransform(QTransform::fromTranslate(-15,-15),true);
                m_dashRect->setRotation(angle);
            }

            qextSetCursor(scene, QCursor((QPixmap(":/icons/rotate.png"))));
        }
        else if (item)
        {
            int handle = item->collidesWithHandle(event->scenePos());
            if (handle != QExtGraphicsSizeHandle::Handle_None)
            {
                qextSetCursor(scene,QCursor((QPixmap(":/icons/rotate.png"))));
                m_hoverSizer = true;
            }
            else
            {
                qextSetCursor(scene, Qt::ArrowCursor);
                m_hoverSizer = false;
            }
        }
    }
    scene->mouseEvent(event);
}

void QExtGraphicsRotationTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mouseReleaseEvent(event,scene);
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1)
    {
        QExtGraphicsAbstractShapeItem *item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(items.first());
        if (item != QEXT_NULLPTR  && nDragHandle != QExtGraphicsSizeHandle::Handle_None && selectMode == rotate)
        {
            QPointF origin = item->mapToScene(item->boundingRect().center());
            QPointF delta = sm_last - origin;
            qreal len_y = sm_last.y() - origin.y();
            qreal len_x = sm_last.x() - origin.x();
            qreal angle = atan2(len_y, len_x) * 180 / PI, oldAngle = item->rotation();
            angle = item->rotation() + int(angle - m_lastAngle);

            if (angle > 360)
            {
                angle -= 360;
            }
            if (angle < -360)
            {
                angle += 360;
            }

            item->setRotation(angle);
            emit scene->itemRotate(item, oldAngle);
            qDebug() << "rotate:" << angle << item->boundingRect();
        }
    }

    qextSetCursor(scene, Qt::ArrowCursor);
    selectMode = none;
    nDragHandle = QExtGraphicsSizeHandle::Handle_None;
    m_lastAngle = 0;
    m_hoverSizer = false;
    if (m_dashRect)
    {
        scene->removeItem(m_dashRect);
        delete m_dashRect;
        m_dashRect = QEXT_NULLPTR;
    }
    scene->mouseEvent(event);
}

QExtGraphicsRectTool::QExtGraphicsRectTool(DrawShape drawShape)
    : QExtGraphicsTool(drawShape)
{
    m_item = QEXT_NULLPTR;
}

void QExtGraphicsRectTool::mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    scene->clearSelection();
    QExtGraphicsTool::mousePressEvent(event, scene);
    switch (sm_drawShape)
    {
    case rectangle:
    {
        m_item = new QExtGraphicsRectItem(QRect(1, 1, 1, 1));
        break;
    }
    case roundrect:
    {
        m_item = new QExtGraphicsRectItem(QRect(1, 1, 1, 1), true);
        break;
    }
    case ellipse:
    {
        m_item = new QExtGraphicsEllipseItem(QRect(1, 1, 1, 1));
        break;
    }
    }
    if (m_item == QEXT_NULLPTR)
    {
        return;
    }
    sm_down += QPoint(2,2);
    m_item->setPos(event->scenePos());
    scene->addItem(m_item);
    m_item->setSelected(true);

    selectMode = size;
    nDragHandle = QExtGraphicsSizeHandle::Handle_RightBottom;
}

void QExtGraphicsRectTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    qextSetCursor(scene,Qt::CrossCursor);
    sg_selectTool->mouseMoveEvent(event, scene);
}

void QExtGraphicsRectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    sg_selectTool->mouseReleaseEvent(event, scene);

    if (event->scenePos() == (sm_down-QPoint(2,2)))
    {
        if (m_item != QEXT_NULLPTR)
        {
            m_item->setSelected(false);
            scene->removeItem(m_item);
            delete m_item ;
            m_item = QEXT_NULLPTR;
        }
        qDebug() << "QExtGraphicsRectTool removeItem:";
    }
    else if(m_item)
    {
        emit scene->itemAdded(m_item);
    }
    sm_drawShape = selection;
}


QExtGraphicsPolygonTool::QExtGraphicsPolygonTool(DrawShape shape)
    : QExtGraphicsTool(shape)
{
    m_item = QEXT_NULLPTR;
    m_pointsCount = 0;
}

void QExtGraphicsPolygonTool::mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mousePressEvent(event,scene);

    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    if (m_item == QEXT_NULLPTR)
    {
        if (sm_drawShape == polygon)
        {
            m_item = new QExtGraphicsPolygonItem(QEXT_NULLPTR);
        }
        else if (sm_drawShape == bezier)
        {
            m_item = new QExtGraphicsBezierItem();
        }
        else if (sm_drawShape == polyline)
        {
            m_item = new QExtGraphicsBezierItem(false);
        }
        else if (sm_drawShape == line)
        {
            m_item = new QExtGraphicsLineItem();
        }
        m_item->setPos(event->scenePos());
        scene->addItem(m_item);
        m_initialPositions = sm_down;
        m_item->addPoint(sm_down);
        m_item->setSelected(true);
        m_pointsCount++;

    }
    else if (sm_down == sm_last)
    {
        /*
        if ( item != NULL )
        {
            scene->removeItem(item);
            delete item;
            item = NULL ;
            c_drawShape = selection;
            selectMode = none;
            return ;
        }
        */
    }
    m_item->addPoint(sm_down + QPoint(1, 0));
    m_pointsCount++;
    selectMode = size;
    nDragHandle = m_item->handleCount();
}

void QExtGraphicsPolygonTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mouseMoveEvent(event,scene);
    qextSetCursor(scene, Qt::CrossCursor);

    //    selectTool.mouseMoveEvent(event,scene);

    if (m_item != QEXT_NULLPTR)
    {
        if (nDragHandle != QExtGraphicsSizeHandle::Handle_None && selectMode == size)
        {
            m_item->control(nDragHandle, sm_last);
        }
    }
}

void QExtGraphicsPolygonTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mousePressEvent(event,scene);
    if (sm_drawShape == line)
    {
        m_item->endPoint(event->scenePos());
        m_item->updateCoordinate();
        emit scene->itemAdded(m_item);
        m_item = QEXT_NULLPTR;
        selectMode = none;
        sm_drawShape = selection;
        m_pointsCount = 0;
    }
}

void QExtGraphicsPolygonTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene)
{
    QExtGraphicsTool::mouseDoubleClickEvent(event, scene);
    m_item->endPoint(event->scenePos());
    m_item->updateCoordinate();
    emit scene->itemAdded(m_item);
    m_item = QEXT_NULLPTR;
    selectMode = none;
    sm_drawShape = selection;
    m_pointsCount = 0;
}
