#include <private/qextGraphicsScene_p.h>

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <vector>

QExtGraphicsGridTool::QExtGraphicsGridTool(const QSize & grid , const QSize & space )
    :m_sizeGrid(grid)
    ,m_sizeGridSpace(20,20)
{
}


void QExtGraphicsGridTool::paintGrid(QPainter *painter, const QRect &rect)
{
    QColor c(Qt::darkCyan);
    QPen p(c);
    p.setStyle(Qt::DashLine);
    p.setWidthF(0.2);
    painter->setPen(p);

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing,false);
    painter->fillRect(rect,Qt::white);
    for (int x=rect.left() ;x <rect.right()  ;x+=(int)(m_sizeGridSpace.width())) {
        painter->drawLine(x,rect.top(),x,rect.bottom());

    }
    for (int y=rect.top();y<rect.bottom() ;y+=(int)(m_sizeGridSpace.height()))
    {
        painter->drawLine(rect.left(),y,rect.right(),y);
    }
    p.setStyle(Qt::SolidLine);
    p.setColor(Qt::black);
    painter->drawLine(rect.right(),rect.top(),rect.right(),rect.bottom());
    painter->drawLine(rect.left(),rect.bottom(),rect.right(),rect.bottom());

    //draw shadow
    QColor c1(Qt::black);
    painter->fillRect(QRect(rect.right()+1,rect.top()+2,2,rect.height()),c1.dark(200));
    painter->fillRect(QRect(rect.left()+2,rect.bottom()+2,rect.width(),2),c1.dark(200));

    painter->restore();
}

class BBoxSort
{
public:
    BBoxSort(QGraphicsItem *item, const QRectF &rect, AlignType alignType)
        : m_item(item), m_box(rect), m_align(alignType)
    {
        //topLeft
        m_min = alignType == HORZEVEN_ALIGN ? m_box.topLeft().x() : m_box.topLeft().y();
        //bottomRight
        m_max = alignType == HORZEVEN_ALIGN ? m_box.bottomRight().x() : m_box.bottomRight().y();
        //width or height
        m_extent = alignType == HORZEVEN_ALIGN ? m_box.width() : m_box.height();
        m_anchor =  m_min * 0.5 + m_max * 0.5;
    }
    qreal min() { return m_min;}
    qreal max() { return m_max;}
    qreal extent() { return m_extent;}

    QGraphicsItem *m_item;
    qreal m_extent;
    qreal m_anchor;
    qreal m_min;
    qreal m_max;
    QRectF m_box;
    AlignType m_align;
};

bool operator< (const BBoxSort &a, const BBoxSort &b)
{
    return (a.m_anchor < b.m_anchor);
}




QExtGraphicsScenePrivate::QExtGraphicsScenePrivate(QExtGraphicsScene *q)
    : q_ptr(q)
    , m_dx(0)
    , m_dy(0)
    , m_view(QEXT_NULLPTR)
    , m_grid(new QExtGraphicsGridTool)
{

}

QExtGraphicsScenePrivate::~QExtGraphicsScenePrivate()
{
    delete m_grid;
}



QExtGraphicsScene::QExtGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , dd_ptr(new QExtGraphicsScenePrivate(this))
{
    QGraphicsItem *item = this->addRect(QRectF(0,0,0,0));
    item->setAcceptHoverEvents(true);
}

QExtGraphicsScene::~QExtGraphicsScene()
{
}

QGraphicsView *QExtGraphicsScene::view() const
{
    Q_D(const QExtGraphicsScene);
    return d->m_view;
}

void QExtGraphicsScene::setView(QGraphicsView *view)
{
    Q_D(QExtGraphicsScene);
    d->m_view = view;
}

void QExtGraphicsScene::align(AlignType alignType)
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    if (selectedItems.size() <= 0)
    {
        return;
    }
    QExtGraphicsAbstractShapeItem *firstItem = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(selectedItems.first());
    if (!firstItem)
    {
        return;
    }
    QRectF rectref = firstItem->mapRectToScene(firstItem->boundingRect());
    int nLeft, nRight, nTop, nBottom;
    qreal width = firstItem->width();
    qreal height = firstItem->height();

    nLeft = nRight = rectref.center().x();
    nTop = nBottom = rectref.center().y();
    QPointF pt = rectref.center();
    if (alignType == HORZEVEN_ALIGN || alignType == VERTEVEN_ALIGN)
    {
        std::vector<BBoxSort> sorted;
        foreach (QGraphicsItem *item, this->selectedItems())
        {
            QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
            if (g)
            {
                continue;
            }
            sorted.push_back(BBoxSort(item, item->mapRectToScene(item->boundingRect()), alignType));
        }
        //sort bbox by anchors
        std::sort(sorted.begin(), sorted.end());

        unsigned int len = sorted.size();
        bool changed = false;
        //overall bboxes span
        float dist = (sorted.back().max()-sorted.front().min());
        //space eaten by bboxes
        float span = 0;
        for (unsigned int i = 0; i < len; i++)
        {
            span += sorted[i].extent();
        }
        //new distance between each bbox
        float step = (dist - span) / (len - 1);
        float pos = sorted.front().min();
        for (std::vector<BBoxSort> ::iterator it(sorted.begin()); it < sorted.end(); ++it)
        {
            {
                QPointF t;
                if (alignType == HORZEVEN_ALIGN)
                {
                    t.setX(pos - it->min());
                }
                else
                {
                    t.setY(pos - it->min());
                }
                it->m_item->moveBy(t.x(), t.y());
                emit this->itemMoved(it->m_item, t);
                changed = true;
            }
            pos += it->extent();
            pos += step;
        }
        return;
    }

    int i = 0;
    foreach (QGraphicsItem *item, this->selectedItems())
    {
        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if (g)
        {
            continue;
        }
        QRectF rectItem = item->mapRectToScene(item->boundingRect() );
        QPointF ptNew = rectItem.center();
        switch (alignType)
        {
        case UP_ALIGN:
            ptNew.setY(nTop + (rectItem.height()-rectref.height()) / 2);
            break;
        case HORZ_ALIGN:
            ptNew.setY(pt.y());
            break;
        case VERT_ALIGN:
            ptNew.setX(pt.x());
            break;
        case DOWN_ALIGN:
            ptNew.setY(nBottom - (rectItem.height() - rectref.height()) / 2);
            break;
        case LEFT_ALIGN:
            ptNew.setX(nLeft - (rectref.width() - rectItem.width()) / 2);
            break;
        case RIGHT_ALIGN:
            ptNew.setX(nRight + (rectref.width() - rectItem.width()) / 2);
            break;
        case CENTER_ALIGN:
            ptNew=pt;
            break;
        case ALL_ALIGN:
        {
            QExtGraphicsAbstractShapeItem *aitem = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem *>(item);
            if (aitem)
            {
                qreal fx = width / aitem->width();
                qreal fy = height / aitem->height();
                if (fx == 1.0 && fy == 1.0)
                {
                    break;
                }
                aitem->stretch(QExtGraphicsSizeHandle::Handle_RightBottom, fx, fy,
                               aitem->opposite(QExtGraphicsSizeHandle::Handle_RightBottom));
                aitem->updateCoordinate();
                emit this->itemResize(aitem, QExtGraphicsSizeHandle::Handle_RightBottom, QPointF(fx, fy));
            }
            break;
        }
        case WIDTH_ALIGN:
        {
            QExtGraphicsAbstractShapeItem *aitem = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(item);
            if (aitem)
            {
                qreal fx = width / aitem->width();
                if (fx == 1.0)
                {
                    break;
                }
                aitem->stretch(QExtGraphicsSizeHandle::Handle_Right, fx, 1,
                               aitem->opposite(QExtGraphicsSizeHandle::Handle_Right));
                aitem->updateCoordinate();
                emit this->itemResize(aitem, QExtGraphicsSizeHandle::Handle_Right, QPointF(fx, 1));
            }
            break;
        }
        case HEIGHT_ALIGN:
        {
            QExtGraphicsAbstractShapeItem *aitem = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(item);
            if (aitem)
            {
                qreal fy = height / aitem->height();
                if (fy == 1.0)
                {
                    break;
                }
                aitem->stretch(QExtGraphicsSizeHandle::Handle_Bottom, 1, fy,
                               aitem->opposite(QExtGraphicsSizeHandle::Handle_Bottom));
                aitem->updateCoordinate();
                emit this->itemResize(aitem, QExtGraphicsSizeHandle::Handle_Bottom, QPointF(1, fy));
            }
            break;
        }
        default:
            break;
        }
        QPointF ptLast= rectItem.center();
        QPointF ptMove = ptNew - ptLast;
        if (!ptMove.isNull())
        {
            item->moveBy(ptMove.x(), ptMove.y());
            emit this->itemMoved(item, ptMove);
        }
        i++;
    }
}

void QExtGraphicsScene::mouseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch(mouseEvent->type())
    {
    case QEvent::GraphicsSceneMousePress:
        QGraphicsScene::mousePressEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseMove:
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseRelease:
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        break;
    }
}

QExtGraphicsItemGroup *QExtGraphicsScene::createGroup(const QList<QGraphicsItem *> &items,bool isAdd)
{
    // Build a list of the first item's ancestors
    QList<QGraphicsItem *> ancestors;
    int n = 0;
    QPointF pt = items.first()->pos();
    if (!items.isEmpty())
    {
        QGraphicsItem *parent = items.at(n++);
        while ((parent = parent->parentItem()))
        {
            ancestors.append(parent);
        }
    }
    // Find the common ancestor for all items
    QGraphicsItem *commonAncestor = QEXT_NULLPTR;
    if (!ancestors.isEmpty())
    {
        while (n < items.size())
        {
            int commonIndex = -1;
            QGraphicsItem *parent = items.at(n++);
            do
            {
                int index = ancestors.indexOf(parent, qMax(0, commonIndex));
                if (index != -1)
                {
                    commonIndex = index;
                    break;
                }
            } while ((parent = parent->parentItem()));

            if (commonIndex == -1)
            {
                commonAncestor = 0;
                break;
            }
            commonAncestor = ancestors.at(commonIndex);
        }
    }

    // Create a new group at that level
    QExtGraphicsItemGroup *group = new QExtGraphicsItemGroup(commonAncestor);
    if (!commonAncestor && isAdd)
    {
        this->addItem(group);
    }
    foreach (QGraphicsItem *item, items)
    {
        item->setSelected(false);
        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if (!g)
        {
            group->addToGroup(item);
        }
    }
    group->updateCoordinate();
    return group;
}

void QExtGraphicsScene::destroyGroup(QGraphicsItemGroup *group)
{
    group->setSelected(false);
    foreach (QGraphicsItem *item, group->childItems())
    {
        item->setSelected(true);
        group->removeFromGroup(item);
    }
    this->removeItem(group);
    delete group;
}

void QExtGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_D(QExtGraphicsScene);
    QGraphicsScene::drawBackground(painter,rect);
    painter->fillRect(sceneRect(),Qt::white);
    if(d->m_grid)
    {
        d->m_grid->paintGrid(painter,sceneRect().toRect());
    }
}

void QExtGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QExtGraphicsTool *tool = QExtGraphicsTool::findTool(QExtGraphicsTool::sm_drawShape);
    if (tool)
    {
        tool->mousePressEvent(mouseEvent, this);
    }
}

void QExtGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QExtGraphicsTool *tool = QExtGraphicsTool::findTool(QExtGraphicsTool::sm_drawShape);
    if (tool)
    {
        tool->mouseMoveEvent(mouseEvent, this);
    }
}

void QExtGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QExtGraphicsTool *tool = QExtGraphicsTool::findTool(QExtGraphicsTool::sm_drawShape);
    if (tool)
    {
        tool->mouseReleaseEvent(mouseEvent, this);
    }
}

void QExtGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvet)
{
    QExtGraphicsTool *tool = QExtGraphicsTool::findTool(QExtGraphicsTool::sm_drawShape);
    if (tool)
    {
        tool->mouseDoubleClickEvent(mouseEvet, this);
    }
}

void QExtGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    Q_D(QExtGraphicsScene);
    qreal dx = 0;
    qreal dy = 0;
    d->m_moved = false;
    switch(event->key())
    {
    case Qt::Key_Up:
    {
        dx = 0;
        dy = -1;
        d->m_moved = true;
        break;
    }
    case Qt::Key_Down:
    {
        dx = 0;
        dy = 1;
        d->m_moved = true;
        break;
    }
    case Qt::Key_Left:
    {
        dx = -1;
        dy = 0;
        d->m_moved = true;
        break;
    }
    case Qt::Key_Right:
    {
        dx = 1;
        dy = 0;
        d->m_moved = true;
        break;
    }
    }
    d->m_dx += dx;
    d->m_dy += dy;
    if (d->m_moved)
    {
        foreach (QGraphicsItem *item, this->selectedItems())
        {
            item->moveBy(dx, dy);
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void QExtGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    Q_D(QExtGraphicsScene);
    if (d->m_moved && selectedItems().count() > 0)
    {
        emit itemMoved(NULL,QPointF(d->m_dx, d->m_dy));
    }
    d->m_dx = 0;
    d->m_dy = 0;
    QGraphicsScene::keyReleaseEvent(event);
}

