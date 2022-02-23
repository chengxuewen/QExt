#include <qextQmlQuickWidgetProxyItem.h>

#include <QDebug>
#include <QTimer>

QEXTQmlQuickWidgetProxyItem::QEXTQmlQuickWidgetProxyItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    connect(this, &QQuickPaintedItem::widthChanged, this, &QEXTQmlQuickWidgetProxyItem::updateWidgetSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &QEXTQmlQuickWidgetProxyItem::updateWidgetSize);
    this->setFlag(QQuickItem::ItemAcceptsInputMethod, true);
    this->setFlag(QQuickItem::ItemHasContents, true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    this->setAcceptHoverEvents(true);
}

QEXTQmlQuickWidgetProxyItem::QEXTQmlQuickWidgetProxyItem(QWidget *widget, QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    connect(this, &QQuickPaintedItem::widthChanged, this, &QEXTQmlQuickWidgetProxyItem::updateWidgetSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &QEXTQmlQuickWidgetProxyItem::updateWidgetSize);
    this->setFlag(QQuickItem::ItemAcceptsInputMethod, true);
    this->setFlag(QQuickItem::ItemHasContents, true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    this->setAcceptHoverEvents(true);
    this->setWidget(widget);
}

QEXTQmlQuickWidgetProxyItem::~QEXTQmlQuickWidgetProxyItem()
{

}

void QEXTQmlQuickWidgetProxyItem::initWidget()
{

}

QWidget *QEXTQmlQuickWidgetProxyItem::widget() const
{
    return m_widget.data();
}

void QEXTQmlQuickWidgetProxyItem::setWidget(QWidget *widget)
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

void QEXTQmlQuickWidgetProxyItem::updateWidgetSize()
{
    if (!m_widget.isNull())
    {
        m_widget->resize(this->width(), this->height());
    }
}

void QEXTQmlQuickWidgetProxyItem::routeHoverEnterEvents(QHoverEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::routeHoverEnterEvents";
    if (!m_widget.isNull())
    {
        QEnterEvent *newEvent = new QEnterEvent(event->pos(), event->pos(), event->pos());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQmlQuickWidgetProxyItem::routeHoverLeaveEvents(QHoverEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::routeHoverLeaveEvents";
    if (!m_widget.isNull())
    {
        QEvent *newEvent = new QEvent(QEvent::Leave);
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQmlQuickWidgetProxyItem::routeHoverMoveEvents(QHoverEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::routeHoverMoveEvents";
    if (!m_widget.isNull())
    {
        QMoveEvent *newEvent = new QMoveEvent(event->pos(), event->oldPos());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQmlQuickWidgetProxyItem::routeMouseEvents(QMouseEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::routeMouseEvents";
    if (!m_widget.isNull())
    {
        QMouseEvent *newEvent = new QMouseEvent(event->type(), event->localPos(), event->windowPos(),
                                                event->screenPos(), event->button(), event->buttons(),
                                                event->modifiers(), event->source());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQmlQuickWidgetProxyItem::routeWheelEvents(QWheelEvent *event)
{
    if (!m_widget.isNull())
    {
        QWheelEvent *newEvent = new QWheelEvent(event->posF(), event->globalPosF(), event->delta(),
                                                event->buttons(), event->modifiers(), event->orientation());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

void QEXTQmlQuickWidgetProxyItem::routeTimerEvents(QTimerEvent *event)
{
    if (!m_widget.isNull())
    {
        QTimerEvent *newEvent = new QTimerEvent(event->timerId());
        QCoreApplication::postEvent(m_widget.data(), newEvent);
    }
}

bool QEXTQmlQuickWidgetProxyItem::eventFilter(QObject *watched, QEvent *event)
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

void QEXTQmlQuickWidgetProxyItem::hoverEnterEvent(QHoverEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::hoverEnterEvent";
    this->routeHoverEnterEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::hoverLeaveEvent(QHoverEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::hoverLeaveEvent";
    this->routeHoverLeaveEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::hoverMoveEvent(QHoverEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::hoverMoveEvent";
    this->routeHoverMoveEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::mousePressEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::mousePressEvent";
    this->routeMouseEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::mouseReleaseEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::mouseReleaseEvent";
    this->routeMouseEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::mouseMoveEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::mouseMoveEvent";
    this->routeMouseEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::mouseDoubleClickEvent";
    this->routeMouseEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::wheelEvent(QWheelEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::wheelEvent";
    this->routeWheelEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::timerEvent(QTimerEvent *event)
{
    qCritical() << "QEXTQmlQuickWidgetProxyItem::timerEvent";
    this->routeTimerEvents(event);
}

void QEXTQmlQuickWidgetProxyItem::paint(QPainter *painter)
{
    //    qCritical() << "QEXTQmlQuickWidgetProxyItem::paint()";
    if (!m_widget.isNull())
    {
        m_widget->render(painter);
    }
}
