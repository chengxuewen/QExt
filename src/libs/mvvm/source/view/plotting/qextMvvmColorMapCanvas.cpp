#include <qextMvvmColorMapCanvas.h>
#include <qextMvvmColorMapViewPortPlotController.h>
#include <qextMvvmCustomPlotSceneAdapter.h>
#include <qextMvvmStatusStringReporter.h>
#include <qextMvvmStatusStringReporterFactory.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmStatusLabel.h>

#include "qcustomplot.h"


struct QEXTMvvmColorMapCanvas::ColorMapCanvasImpl {
    QCustomPlot* custom_plot{nullptr};
    QScopedPointer<QEXTMvvmColorMapViewportPlotController> viewport_controller;
    QScopedPointer<QEXTMvvmStatusStringReporter> reporter;
    QEXTMvvmStatusLabel* status_label{nullptr};

    ColorMapCanvasImpl() : custom_plot(new QCustomPlot), status_label(new QEXTMvvmStatusLabel)
    {
        viewport_controller.reset(new QEXTMvvmColorMapViewportPlotController(custom_plot));

        auto on_mouse_move = [this](const QString& str) {
            status_label->setText(str);
        };
        reporter.reset(CreateColorMapReporter(custom_plot, on_mouse_move));
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

QEXTMvvmColorMapCanvas::QEXTMvvmColorMapCanvas(QWidget* parent)
    : QWidget(parent), p_impl(new ColorMapCanvasImpl)
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

QEXTMvvmSceneAdapterInterface *QEXTMvvmColorMapCanvas::createSceneAdapter() const
{
    return new QEXTMvvmCustomPlotSceneAdapter(p_impl->customPlot());
}
