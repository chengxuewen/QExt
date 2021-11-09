#include <qextQuickWidgetProxyItem.h>

#include <QDebug>
#include <QTimer>

QEXTQuickWidgetProxyItem::QEXTQuickWidgetProxyItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    connect(this, &QQuickPaintedItem::widthChanged, this, &QEXTQuickWidgetProxyItem::updateWidgetSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &QEXTQuickWidgetProxyItem::updateWidgetSize);
    this->setFlag(QQuickItem::ItemAcceptsInputMethod, true);
    this->setFlag(QQuickItem::ItemHasContents, true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    this->setAcceptHoverEvents(true);
}

QEXTQuickWidgetProxyItem::QEXTQuickWidgetProxyItem(QWidget *widget, QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    connect(this, &QQuickPaintedItem::widthChanged, this, &QEXTQuickWidgetProxyItem::updateWidgetSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &QEXTQuickWidgetProxyItem::updateWidgetSize);
    this->setFlag(QQuickItem::ItemAcceptsInputMethod, true);
    this->setFlag(QQuickItem::ItemHasContents, true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    this->setAcceptHoverEvents(true);
    this->setWidget(widget);
}

QEXTQuickWidgetProxyItem::~QEXTQuickWidgetProxyItem()
{

}

void QEXTQuickWidgetProxyItem::initWidget()
{

}

QWidget *QEXTQuickWidgetProxyItem::widget() const
{
    return m_widget.data();
}

void QEXTQuickWidgetProxyItem::setWidget(QWidget *widget)
{
    if (m_widget.data() != widget)
    {
        if (!m_widget.isNull())
        {
            m_widget->disconnect(this);
            m_widget->removeEventFilter(this);
            this->disconnect(m_widget.data());
        }
        m_widget.reset(widget);
        if (!m_widget.isNull())
        {
            m_widget->installEventFilter(this);
        }
        QTimer::singleShot(0, this, SLOT(update()));
    }
}

void QEXTQuickWidgetProxyItem::updateWidgetSize()
{
    if (!m_widget.isNull())
    {
        m_widget->resize(this->width(), this->height());
    }
}

void QEXTQuickWidgetProxyItem::routeHoverEnterEvents(QHoverEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::routeHoverEnterEvents";
    if (!m_widget.isNull())
    {
        QEnterEvent *newEvent = new QEnterEvent(event->pos(), event->pos(), event->pos());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQuickWidgetProxyItem::routeHoverLeaveEvents(QHoverEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::routeHoverLeaveEvents";
    if (!m_widget.isNull())
    {
        QEvent *newEvent = new QEvent(QEvent::Leave);
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQuickWidgetProxyItem::routeHoverMoveEvents(QHoverEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::routeHoverMoveEvents";
    if (!m_widget.isNull())
    {
        QMoveEvent *newEvent = new QMoveEvent(event->pos(), event->oldPos());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQuickWidgetProxyItem::routeMouseEvents(QMouseEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::routeMouseEvents";
    if (!m_widget.isNull())
    {
        QMouseEvent *newEvent = new QMouseEvent(event->type(), event->localPos(), event->windowPos(),
                                                event->screenPos(), event->button(), event->buttons(),
                                                event->modifiers(), event->source());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQuickWidgetProxyItem::routeWheelEvents(QWheelEvent *event)
{
    if (!m_widget.isNull())
    {
        QWheelEvent *newEvent = new QWheelEvent(event->posF(), event->globalPosF(), event->delta(),
                                                event->buttons(), event->modifiers(), event->orientation());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQuickWidgetProxyItem::routeTimerEvents(QTimerEvent *event)
{
    if (!m_widget.isNull())
    {
        QTimerEvent *newEvent = new QTimerEvent(event->timerId());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

bool QEXTQuickWidgetProxyItem::eventFilter(QObject *watched, QEvent *event)
{
    if (m_widget.data() == watched)
    {
        if (event->type() == QEvent::Paint)
        {
            QPaintEvent *paintEvent = dynamic_cast<QPaintEvent *>(event);
            if (paintEvent)
            {
                //                qCritical() << "paintEvent->rect()=" << paintEvent->rect();
                this->update(paintEvent->rect());
            }
        }
    }
    return QQuickPaintedItem::eventFilter(watched, event);
}

void QEXTQuickWidgetProxyItem::hoverEnterEvent(QHoverEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::hoverEnterEvent";
    this->routeHoverEnterEvents(event);
}

void QEXTQuickWidgetProxyItem::hoverLeaveEvent(QHoverEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::hoverLeaveEvent";
    this->routeHoverLeaveEvents(event);
}

void QEXTQuickWidgetProxyItem::hoverMoveEvent(QHoverEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::hoverMoveEvent";
    this->routeHoverMoveEvents(event);
}

void QEXTQuickWidgetProxyItem::mousePressEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::mousePressEvent";
    this->routeMouseEvents(event);
}

void QEXTQuickWidgetProxyItem::mouseReleaseEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::mouseReleaseEvent";
    this->routeMouseEvents(event);
}

void QEXTQuickWidgetProxyItem::mouseMoveEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::mouseMoveEvent";
    this->routeMouseEvents(event);
}

void QEXTQuickWidgetProxyItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::mouseDoubleClickEvent";
    this->routeMouseEvents(event);
}

void QEXTQuickWidgetProxyItem::wheelEvent(QWheelEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::wheelEvent";
    this->routeWheelEvents(event);
}

void QEXTQuickWidgetProxyItem::timerEvent(QTimerEvent *event)
{
    qCritical() << "QEXTQuickWidgetProxyItem::timerEvent";
    this->routeTimerEvents(event);
}

void QEXTQuickWidgetProxyItem::paint(QPainter *painter)
{
    //    qCritical() << "QEXTQuickWidgetProxyItem::paint()";
    if (!m_widget.isNull())
    {
        m_widget->render(painter);
    }
}
