#include <private/qextGraphicsScene_p.h>

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <vector>

QExtGraphicsGridTool::QExtGraphicsGridTool(const QSize &grid, const QSize &space)
    : m_sizeGrid(grid)
    , m_sizeGridSpace(space)
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

}

void QExtGraphicsScene::mouseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

QExtGraphicsItemGroup *QExtGraphicsScene::createGroup(const QList<QGraphicsItem *> &items, bool isAdd)
{

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

