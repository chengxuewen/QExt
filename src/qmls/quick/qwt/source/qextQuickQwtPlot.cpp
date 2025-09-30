#include <qextQuickQwtPlot.h>
#include "plotdata.h"

#include <qextGlobal.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_renderer.h>

#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QWheelEvent>

QExtQuickQwtPlot::QExtQuickQwtPlot(QQuickItem* parent) : QQuickPaintedItem(parent)
    , m_qwtPlot(nullptr), m_timerId(0)
{
    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, &QQuickPaintedItem::widthChanged, this, &QExtQuickQwtPlot::updatePlotSize);
    connect(this, &QQuickPaintedItem::heightChanged, this, &QExtQuickQwtPlot::updatePlotSize);
}

QExtQuickQwtPlot::~QExtQuickQwtPlot()
{
    delete m_qwtPlot;
    m_qwtPlot = nullptr;

    if (m_timerId != 0) {
        killTimer(m_timerId);
    }
}

void QExtQuickQwtPlot::replotAndUpdate()
{
    m_qwtPlot->replot();
    update();
}

void QExtQuickQwtPlot::initQwtPlot()
{
    m_qwtPlot = new QwtPlot();
    // after replot() we need to call update() - so disable auto replot
    m_qwtPlot->setAutoReplot(false);
    m_qwtPlot->setStyleSheet("background: white");

    updatePlotSize();

    m_curve1 = new QwtPlotCurve("Curve 1");

    m_curve1->setPen(QPen(Qt::red));
    m_curve1->setStyle(QwtPlotCurve::Lines);
    m_curve1->setRenderHint(QwtPlotItem::RenderAntialiased);

    m_curve1->setData(new PlotData(&m_curve1_data));

    m_qwtPlot->setAxisTitle(m_qwtPlot->xBottom, tr("t"));
    m_qwtPlot->setAxisTitle(m_qwtPlot->yLeft, tr("S"));

    m_curve1->attach(m_qwtPlot);

    startTimer(500);

    replotAndUpdate();
}


void QExtQuickQwtPlot::paint(QPainter* painter)
{
    if (m_qwtPlot) {
        QPixmap picture(boundingRect().size().toSize());

        QwtPlotRenderer renderer;
        renderer.renderTo(m_qwtPlot, picture);

        painter->drawPixmap(QPoint(), picture);
    }
}

void QExtQuickQwtPlot::mousePressEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents(event);
}

void QExtQuickQwtPlot::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents(event);
}

void QExtQuickQwtPlot::mouseMoveEvent(QMouseEvent* event)
{
    routeMouseEvents(event);
}

void QExtQuickQwtPlot::mouseDoubleClickEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    routeMouseEvents(event);
}

void QExtQuickQwtPlot::wheelEvent(QWheelEvent* event)
{
    routeWheelEvents(event);
}

void QExtQuickQwtPlot::timerEvent(QTimerEvent* /*event*/)
{
    static double t, U;
    U = (static_cast<double>(QEXT_RANDOM_INT()) / RAND_MAX) * 5;

    m_curve1_data.append(QPointF(t, U));

    qDebug() << Q_FUNC_INFO << QString("Adding dot t = %1, S = %2").arg(t).arg(U);
    t++;
    replotAndUpdate();
}

void QExtQuickQwtPlot::routeMouseEvents(QMouseEvent* event)
{
    if (m_qwtPlot) {
        QMouseEvent* newEvent = new QMouseEvent(event->type(), event->localPos(),
                                                event->button(), event->buttons(),
                                                event->modifiers());
        QCoreApplication::postEvent(m_qwtPlot, newEvent);
    }
}

void QExtQuickQwtPlot::routeWheelEvents(QWheelEvent* event)
{
    if (m_qwtPlot) {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
        QWheelEvent* newEvent = new QWheelEvent(event->position(), event->globalPosition(),
                                                event->pixelDelta(), event->angleDelta(),
                                                event->buttons(), event->modifiers(),
                                                event->phase(), event->inverted(),
                                                event->source(), event->pointingDevice());
#else
        QWheelEvent* newEvent = new QWheelEvent(event->position(), event->globalPosition(),
                                                event->pixelDelta(), event->angleDelta(),
                                                event->buttons(), event->modifiers(),
                                                event->phase(), event->inverted(),
                                                event->source());
#endif
        QCoreApplication::postEvent(m_qwtPlot, newEvent);
    }
}

void QExtQuickQwtPlot::updatePlotSize()
{
    if (m_qwtPlot) {
        m_qwtPlot->setGeometry(0, 0, static_cast<int>(width()), static_cast<int>(height()));
    }
}
