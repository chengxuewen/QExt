#include <private/qextQuickQwtPlot_p.h>
#include <private/qextQuickQwtPlotCurve_p.h>

#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_scaleitem.h>

#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>

QExtQuickQwtPlotPrivate::QExtQuickQwtPlotPrivate(QExtQuickQwtPlot *q)
    : q_ptr(q)
{
}

QExtQuickQwtPlotPrivate::~QExtQuickQwtPlotPrivate()
{
}

QExtQuickQwtPlot::AxisEnum QExtQuickQwtPlotPrivate::fromQwt(QwtPlot::Axis axis)
{
    switch (axis)
    {
    case QwtPlot::yLeft: return QExtQuickQwtPlot::AxisLeft;
    case QwtPlot::yRight: return QExtQuickQwtPlot::AxisRight;
    case QwtPlot::xBottom: return QExtQuickQwtPlot::AxisBottom;
    case QwtPlot::xTop: return QExtQuickQwtPlot::AxisTop;
    default: break;
    }
    return QExtQuickQwtPlot::AxisLeft;
}

QwtPlot::Axis QExtQuickQwtPlotPrivate::toQwt(QExtQuickQwtPlot::AxisEnum axis)
{
    switch (axis)
    {
    case QExtQuickQwtPlot::AxisLeft: return QwtPlot::yLeft;
    case QExtQuickQwtPlot::AxisRight: return QwtPlot::yRight;
    case QExtQuickQwtPlot::AxisBottom: return QwtPlot::xBottom;
    case QExtQuickQwtPlot::AxisTop: return QwtPlot::xTop;
    default: break;
    }
    return QwtPlot::yLeft;
}

QwtPlot *QExtQuickQwtPlotPrivate::qwtPlot()
{
    if (!mQwtPlot)
    {
        mQwtPlot.reset(new QwtPlot);
        mQwtPlot->setAutoReplot(false);
        mQwtPlot->setAttribute(Qt::WA_OpaquePaintEvent);
        mQwtPlot->setAttribute(Qt::WA_NoSystemBackground);
        mQwtPlot->setAttribute(Qt::WA_TranslucentBackground);
        mQwtPlot->setPalette(QPalette(Qt::transparent));
        mQwtPlot->setCanvasBackground(Qt::transparent);
    }
    return mQwtPlot.data();
}

const QwtPlot *QExtQuickQwtPlotPrivate::qwtPlot() const
{
    return const_cast<QExtQuickQwtPlotPrivate *>(this)->qwtPlot();
}

QExtQuickQwtPlot::QExtQuickQwtPlot(QQuickItem* parent)
    : QExtQuickQwtPlot(new QExtQuickQwtPlotPrivate(this), parent)
{
}

QExtQuickQwtPlot::QExtQuickQwtPlot(QExtQuickQwtPlotPrivate *d, QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , dd_ptr(d)
{
    this->setFlag(QQuickItem::ItemHasContents, true);
    this->setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, &QQuickPaintedItem::widthChanged, this, &QExtQuickQwtPlot::updatePlotSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &QExtQuickQwtPlot::updatePlotSize);
    this->updatePlotSize();
    this->replotAndUpdate();
}

QExtQuickQwtPlot::~QExtQuickQwtPlot()
{
}

void QExtQuickQwtPlot::paint(QPainter* painter)
{
    Q_D(QExtQuickQwtPlot);
    if (d->mQwtPlot)
    {
        QPixmap picture(this->boundingRect().size().toSize());
        picture.fill(Qt::transparent);

        QwtPlotRenderer renderer;
        renderer.renderTo(d->mQwtPlot.get(), picture);
        painter->drawPixmap(QPoint(), picture);
    }
}

bool QExtQuickQwtPlot::autoReplot() const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->autoReplot();
}

void QExtQuickQwtPlot::setAutoReplot(bool value)
{
    Q_D(QExtQuickQwtPlot);
    if (d->qwtPlot()->autoReplot() != value)
    {
        d->qwtPlot()->setAutoReplot(value);
        emit this->autoReplotChanged(value);
    }
}

QString QExtQuickQwtPlot::styleSheet() const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->styleSheet();
}

void QExtQuickQwtPlot::setStyleSheet(const QString &styleSheet)
{
    Q_D(QExtQuickQwtPlot);
    if (d->qwtPlot()->styleSheet() != styleSheet)
    {
        d->qwtPlot()->setStyleSheet(styleSheet);
        emit this->styleSheetChanged(styleSheet);
    }
}

QColor QExtQuickQwtPlot::backgroundColor() const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->palette().color(QPalette::Window);
}

void QExtQuickQwtPlot::setBackgroundColor(const QColor &color)
{
    Q_D(QExtQuickQwtPlot);
    if (this->backgroundColor() != color)
    {
        auto palette = d->qwtPlot()->palette();
        palette.setColor(QPalette::Window, color);
        d->qwtPlot()->setPalette(palette);
        emit this->canvasBackgroundColorChanged(color);
    }
}

QColor QExtQuickQwtPlot::canvasBackgroundColor() const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->canvasBackground().color();
}

void QExtQuickQwtPlot::setCanvasBackgroundColor(const QColor &color)
{
    Q_D(QExtQuickQwtPlot);
    if (this->canvasBackgroundColor() != color)
    {
        auto brush = d->qwtPlot()->canvasBackground();
        brush.setColor(color);
        d->qwtPlot()->setCanvasBackground(brush);
        emit this->canvasBackgroundColorChanged(color);
    }
}

double QExtQuickQwtPlot::axisMin(AxisEnum axis) const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->axisScaleDiv(d->toQwt(axis)).lowerBound();
}

void QExtQuickQwtPlot::setAxisMin(AxisEnum axis, double value)
{
    Q_D(QExtQuickQwtPlot);
    if (!qFuzzyCompare(this->axisMin(axis), value))
    {
        d->qwtPlot()->setAxisScale(d->toQwt(axis), value, this->axisMax(axis));
        emit this->axisMinChanged(axis, value);
    }
}

double QExtQuickQwtPlot::axisMax(AxisEnum axis) const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->axisScaleDiv(d->toQwt(axis)).upperBound();
}

void QExtQuickQwtPlot::setAxisMax(AxisEnum axis, double value)
{
    Q_D(QExtQuickQwtPlot);
    if (!qFuzzyCompare(this->axisMax(axis), value))
    {
        d->qwtPlot()->setAxisScale(d->toQwt(axis), this->axisMin(axis), value);
        emit this->axisMaxChanged(axis, value);
    }
}

void QExtQuickQwtPlot::setAxisRange(AxisEnum axis, double min, double max)
{
    this->setAxisMin(axis, min);
    this->setAxisMax(axis, max);
}

bool QExtQuickQwtPlot::isAxisValid(AxisEnum axis) const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->isAxisValid(d->toQwt(axis));
}

bool QExtQuickQwtPlot::isAxisVisible(AxisEnum axis) const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->isAxisVisible(d->toQwt(axis));
}

void QExtQuickQwtPlot::setAxisVisible(AxisEnum axis, bool on)
{
    Q_D(QExtQuickQwtPlot);
    if (d->qwtPlot()->isAxisVisible(d->toQwt(axis)) != on)
    {
        d->qwtPlot()->setAxisVisible(d->toQwt(axis), on);
        emit this->axisVisibleChanged(axis, on);
    }
}

bool QExtQuickQwtPlot::axisAutoScale(AxisEnum axis) const
{
    Q_D(const QExtQuickQwtPlot);
    return d->qwtPlot()->axisAutoScale(d->toQwt(axis));
}

void QExtQuickQwtPlot::setAxisAutoScale(AxisEnum axis, bool on)
{
    Q_D(QExtQuickQwtPlot);
    if (d->qwtPlot()->axisAutoScale(d->toQwt(axis)) != on)
    {
        d->qwtPlot()->setAxisAutoScale(d->toQwt(axis), on);
        emit this->axisAutoScaleChanged(axis, on);
    }
}

void QExtQuickQwtPlot::mousePressEvent(QMouseEvent* event)
{
    //    qDebug() << Q_FUNC_INFO;
    this->routeMouseEvents(event);
}

void QExtQuickQwtPlot::mouseReleaseEvent(QMouseEvent* event)
{
    //    qDebug() << Q_FUNC_INFO;
    this->routeMouseEvents(event);
}

void QExtQuickQwtPlot::mouseMoveEvent(QMouseEvent* event)
{
    this->routeMouseEvents(event);
}

void QExtQuickQwtPlot::mouseDoubleClickEvent(QMouseEvent* event)
{
    //    qDebug() << Q_FUNC_INFO;
    this->routeMouseEvents(event);
}

void QExtQuickQwtPlot::wheelEvent(QWheelEvent* event)
{
    this->routeWheelEvents(event);
}

void QExtQuickQwtPlot::updatePlotSize()
{
    Q_D(QExtQuickQwtPlot);
    if (d->mQwtPlot)
    {
        d->mQwtPlot->setGeometry(0, 0, static_cast<int>(this->width()), static_cast<int>(this->height()));
    }
}

void QExtQuickQwtPlot::replotAndUpdate()
{
    Q_D(QExtQuickQwtPlot);
    if (d->mQwtPlot)
    {
        d->mQwtPlot->replot();
    }
    this->update();
}

void QExtQuickQwtPlot::routeMouseEvents(QMouseEvent* event)
{
    Q_D(QExtQuickQwtPlot);
    if (d->mQwtPlot)
    {
        QMouseEvent *newEvent = new QMouseEvent(event->type(), event->localPos(),
                                                event->button(), event->buttons(),
                                                event->modifiers());
        QCoreApplication::postEvent(d->mQwtPlot.get(), newEvent);
    }
}

void QExtQuickQwtPlot::routeWheelEvents(QWheelEvent* event)
{
    Q_D(QExtQuickQwtPlot);
    if (d->mQwtPlot)
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
        QWheelEvent* newEvent = new QWheelEvent(event->pos(), event->globalPos(),
                                                event->pixelDelta(), event->angleDelta(),
                                                event->buttons(), event->modifiers(),
                                                event->phase(), event->inverted(),
                                                event->source());
#else
        QWheelEvent* newEvent = new QWheelEvent(event->position(), event->globalPosition(),
                                                event->pixelDelta(), event->angleDelta(),
                                                event->buttons(), event->modifiers(),
                                                event->phase(), event->inverted(),
                                                event->source());
#endif
        QCoreApplication::postEvent(d->mQwtPlot.get(), newEvent);
    }
}
