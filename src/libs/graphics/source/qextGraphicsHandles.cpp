#include <private/qextGraphicsHandles_p.h>

#include <QMenu>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>

enum { SELECTION_HANDLE_SIZE = 6, SELECTION_MARGIN = 10 };

QExtGraphicsSizeHandlePrivate::QExtGraphicsSizeHandlePrivate(QExtGraphicsSizeHandle *q, int dir)
    : q_ptr(q)
    , m_dir(dir)
    , m_state(SelectionHandleOff)
    , m_borderColor("white")
{
}

QExtGraphicsSizeHandlePrivate::~QExtGraphicsSizeHandlePrivate()
{

}



QExtGraphicsSizeHandle::QExtGraphicsSizeHandle(QGraphicsItem *parent, int dir, bool control)
    : QGraphicsRectItem(-SELECTION_HANDLE_SIZE/2,
                        -SELECTION_HANDLE_SIZE/2,
                        SELECTION_HANDLE_SIZE,
                        SELECTION_HANDLE_SIZE, parent)
    , dd_ptr(new QExtGraphicsSizeHandlePrivate(this, dir))
{
    dd_ptr->m_controlPoint = control;
    this->setAcceptHoverEvents(true);
    this->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    this->hide();
}

QExtGraphicsSizeHandle::QExtGraphicsSizeHandle(QExtGraphicsSizeHandlePrivate *d, QGraphicsItem *parent,
                                                       bool control)
    : QGraphicsRectItem(-SELECTION_HANDLE_SIZE/2,
                        -SELECTION_HANDLE_SIZE/2,
                        SELECTION_HANDLE_SIZE,
                        SELECTION_HANDLE_SIZE, parent)
    , dd_ptr(d)
{
    dd_ptr->m_controlPoint = control;
    this->setAcceptHoverEvents(true);
    this->setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    this->hide();
}

QExtGraphicsSizeHandle::~QExtGraphicsSizeHandle()
{

}

int QExtGraphicsSizeHandle::dir() const
{
    Q_D(const QExtGraphicsSizeHandle);
    return d->m_dir;
}

void QExtGraphicsSizeHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(QExtGraphicsSizeHandle);

    painter->save();
    painter->setPen(Qt::SolidLine);
    painter->setBrush(QBrush(d->m_borderColor));
    painter->setRenderHint(QPainter::Antialiasing,false);

    if (d->m_controlPoint)
    {
        painter->setPen(QPen(Qt::red, Qt::SolidLine));
        painter->setBrush(Qt::green);
        painter->drawEllipse(this->rect().center(), 3,3);
    }
    else
    {
        painter->drawRect(this->rect());
    }
    painter->restore();
}


void QExtGraphicsSizeHandle::setState(SelectionHandleState state)
{
    Q_D(QExtGraphicsSizeHandle);
    if (state == d->m_state)
    {
        return;
    }
    switch (state)
    {
    case SelectionHandleOff:
    {
        this->hide();
        break;
    }
    case SelectionHandleInactive:
    case SelectionHandleActive:
    {
        this->show();
        break;
    }
    }
    d->m_borderColor = Qt::white;
    d->m_state = state;
}

void QExtGraphicsSizeHandle::move(qreal x, qreal y)
{
    Q_D(QExtGraphicsSizeHandle);
    this->setPos(x, y);
}

void QExtGraphicsSizeHandle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(QExtGraphicsSizeHandle);
    d->m_borderColor = Qt::blue;
    this->update();
    QGraphicsRectItem::hoverEnterEvent(event);
}

void QExtGraphicsSizeHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(QExtGraphicsSizeHandle);
    d->m_borderColor = Qt::white;
    this->update();
    QGraphicsRectItem::hoverLeaveEvent(event);
}
