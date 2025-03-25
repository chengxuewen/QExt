// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGraphCanvas.h>
#include <qextMvvmCustomPlotSceneAdapter.h>
#include <qextMvvmGraphViewPortPlotController.h>
#include <qextMvvmStatusStringReporter.h>
#include <qextMvvmStatusStringReporterFactory.h>
#include <qextMvvmGraphViewPortItem.h>
#include <qextMvvmStatusLabel.h>
#include <qcustomplot.h>
#include <QBoxLayout>

namespace {

//! Returns policy to which side of the axes box margins can be applied.
//! If number is negative, this side will be callulated automatically.

// FIXME move to utils, provide unit tests
QCP::MarginSides autoMarginPolicy(int left, int top, int right, int bottom)
{
    QCP::MarginSides result{QCP::msAll};
    if (left >= 0)
        result &= ~QCP::msLeft;
    if (top >= 0)
        result &= ~QCP::msTop;
    if (right >= 0)
        result &= ~QCP::msRight;
    if (bottom >= 0)
        result &= ~QCP::msBottom;
    return result;
}
} // namespace

using namespace ModelView;

struct QExtMvvmGraphCanvas::GraphCanvasImpl {
    QCustomPlot* custom_plot{nullptr};
    QExtUniquePointer<QExtMvvmGraphViewportPlotController> viewport_controller;
    QExtUniquePointer<QExtMvvmStatusStringReporter> reporter;
    QExtMvvmStatusLabel* status_label{nullptr};

    GraphCanvasImpl() : custom_plot(new QCustomPlot), status_label(new QExtMvvmStatusLabel)
    {
        viewport_controller = qextMakeUnique<QExtMvvmGraphViewportPlotController>(custom_plot);

        auto on_mouse_move = [this](const std::string& str) {
            status_label->setText(QString::fromStdString(str));
        };
        reporter = CreateGraphReporter(custom_plot, on_mouse_move);
    }

    //! Updates viewport.
    void setViewportToContent()
    {
        if (!viewport_controller->currentItem())
            return;
        viewport_controller->currentItem()->setViewportToContent();
    }

    //! Updates viewport.
    void setViewportToContent(double left, double top, double right, double bottom)
    {
        if (!viewport_controller->currentItem())
            return;
        viewport_controller->currentItem()->setViewportToContent(left, top, right, bottom);
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

QExtMvvmGraphCanvas::QExtMvvmGraphCanvas(QWidget* parent)
    : QWidget(parent), p_impl(qextMakeUnique<GraphCanvasImpl>())
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(p_impl->custom_plot);
    layout->addWidget(p_impl->status_label);
    setLayout(layout);

    setMouseTracking(true);
    p_impl->customPlot()->setMouseTracking(true);
    p_impl->customPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_impl->customPlot()->axisRect()->setupFullAxesBox(true);

    auto on_replot = [this]() {
        QMargins margins = p_impl->customPlot()->axisRect()->margins();
        axisMarginsChanged(margins.left(), margins.top(), margins.right(), margins.bottom());
    };
    connect(p_impl->customPlot(), &QCustomPlot::afterReplot, this, on_replot);
}

QExtMvvmGraphCanvas::~QExtMvvmGraphCanvas() = default;

void QExtMvvmGraphCanvas::setItem(QExtMvvmGraphViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}

QExtUniquePointer<QExtMvvmSceneAdapterInterface> QExtMvvmGraphCanvas::createSceneAdapter() const
{
    return qextMakeUnique<QExtMvvmCustomPlotSceneAdapter>(p_impl->customPlot());
}

void QExtMvvmGraphCanvas::setViewportToContent(double left, double top, double right, double bottom)
{
    p_impl->setViewportToContent(left, top, right, bottom);
}

void QExtMvvmGraphCanvas::setViewportToContent()
{
    p_impl->setViewportToContent();
}

//! Set margins between axes rectangle and widget borders.
//! If the value is negative, leave old margin intact and allow automatic margin adjustment.

void QExtMvvmGraphCanvas::setAxisMargins(int left, int top, int right, int bottom)
{
    auto customPlot = p_impl->customPlot();
    customPlot->axisRect()->setAutoMargins(autoMarginPolicy(left, top, right, bottom));

    QMargins orig = customPlot->axisRect()->margins();
    int new_left = left >= 0 ? left : orig.left();
    int new_top = top >= 0 ? top : orig.top();
    int new_right = right >= 0 ? right : orig.right();
    int new_bottom = bottom >= 0 ? bottom : orig.bottom();
    customPlot->axisRect()->setMargins(QMargins(new_left, new_top, new_right, new_bottom));

    customPlot->replot();
}
