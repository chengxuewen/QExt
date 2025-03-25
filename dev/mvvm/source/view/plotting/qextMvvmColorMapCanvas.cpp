// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmColorMapCanvas.h>
#include <qextMvvmColorMapViewPortPlotController.h>
#include <qextMvvmCustomPlotSceneAdapter.h>
#include <qextMvvmStatusStringReporter.h>
#include <qextMvvmStatusStringReporterFactory.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmStatusLabel.h>
#include <qcustomplot.h>

using namespace ModelView;

struct QExtMvvmColorMapCanvas::ColorMapCanvasImpl {
    QCustomPlot* custom_plot{nullptr};
    QExtUniquePointer<QExtMvvmColorMapViewportPlotController> viewport_controller;
    QExtUniquePointer<QExtMvvmStatusStringReporter> reporter;
    QExtMvvmStatusLabel* status_label{nullptr};

    ColorMapCanvasImpl() : custom_plot(new QCustomPlot), status_label(new QExtMvvmStatusLabel)
    {
        viewport_controller = qextMakeUnique<QExtMvvmColorMapViewportPlotController>(custom_plot);

        auto on_mouse_move = [this](const std::string& str) {
            status_label->setText(QString::fromStdString(str));
        };
        reporter = CreateColorMapReporter(custom_plot, on_mouse_move);
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

QExtMvvmColorMapCanvas::QExtMvvmColorMapCanvas(QWidget* parent)
    : QWidget(parent), p_impl(qextMakeUnique<ColorMapCanvasImpl>())
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(p_impl->custom_plot);
    layout->addWidget(p_impl->status_label);
    setLayout(layout);

    p_impl->customPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_impl->customPlot()->axisRect()->setupFullAxesBox(true);
}

QExtMvvmColorMapCanvas::~QExtMvvmColorMapCanvas() = default;

void QExtMvvmColorMapCanvas::setItem(QExtMvvmColorMapViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}

//! Creates adapter to convert widget coordinates, to QCustomPlot internal coordinate system
//! (defined by its axes).

QExtUniquePointer<QExtMvvmSceneAdapterInterface> QExtMvvmColorMapCanvas::createSceneAdapter() const
{
    return qextMakeUnique<QExtMvvmCustomPlotSceneAdapter>(p_impl->customPlot());
}
