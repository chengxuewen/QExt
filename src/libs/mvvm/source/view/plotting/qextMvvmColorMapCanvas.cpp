// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <plotting/qextMvvmColorMapCanvas.h>
#include <plotting/qextMvvmColorMapViewPortPlotController.h>
#include <plotting/qextMvvmCustomPlotSceneAdapter.h>
#include <plotting/qextMvvmStatusStringReporter.h>
#include <plotting/qextMvvmStatusStringReporterFactory.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmStatusLabel.h>

using namespace ModelView;

struct QEXTMvvmColorMapCanvas::ColorMapCanvasImpl {
    QCustomPlot* custom_plot{nullptr};
    std::unique_ptr<QEXTMvvmColorMapViewportPlotController> viewport_controller;
    std::unique_ptr<QEXTMvvmStatusStringReporter> reporter;
    QEXTMvvmStatusLabel* status_label{nullptr};

    ColorMapCanvasImpl() : custom_plot(new QCustomPlot), status_label(new QEXTMvvmStatusLabel)
    {
        viewport_controller = make_unique<QEXTMvvmColorMapViewportPlotController>(custom_plot);

        auto on_mouse_move = [this](const std::string& str) {
            status_label->setText(QString::fromStdString(str));
        };
        reporter = CreateColorMapReporter(custom_plot, on_mouse_move);
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

QEXTMvvmColorMapCanvas::QEXTMvvmColorMapCanvas(QWidget* parent)
    : QWidget(parent), p_impl(make_unique<ColorMapCanvasImpl>())
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(p_impl->custom_plot);
    layout->addWidget(p_impl->status_label);
    setLayout(layout);

    p_impl->customPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    p_impl->customPlot()->axisRect()->setupFullAxesBox(true);
}

QEXTMvvmColorMapCanvas::~QEXTMvvmColorMapCanvas() = default;

void QEXTMvvmColorMapCanvas::setItem(QEXTMvvmColorMapViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}

//! Creates adapter to convert widget coordinates, to QCustomPlot internal coordinate system
//! (defined by its axes).

std::unique_ptr<QEXTMvvmSceneAdapterInterface> QEXTMvvmColorMapCanvas::createSceneAdapter() const
{
    return make_unique<QEXTMvvmCustomPlotSceneAdapter>(p_impl->customPlot());
}
