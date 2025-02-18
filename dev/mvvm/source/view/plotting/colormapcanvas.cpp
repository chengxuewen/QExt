// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/plotting/colormapcanvas.h"
#include "view/plotting/colormapviewportplotcontroller.h"
#include "view/plotting/customplotsceneadapter.h"
#include "view/plotting/statusstringreporter.h"
#include "view/plotting/statusstringreporterfactory.h"
#include "model/standarditems/colormapviewportitem.h"
#include "view/widgets/statuslabel.h"
#include <qcustomplot.h>

using namespace ModelView;

struct ColorMapCanvas::ColorMapCanvasImpl {
    QCustomPlot* custom_plot{nullptr};
    QExtUniquePointer<ColorMapViewportPlotController> viewport_controller;
    QExtUniquePointer<StatusStringReporter> reporter;
    StatusLabel* status_label{nullptr};

    ColorMapCanvasImpl() : custom_plot(new QCustomPlot), status_label(new StatusLabel)
    {
        viewport_controller = qextMakeUnique<ColorMapViewportPlotController>(custom_plot);

        auto on_mouse_move = [this](const std::string& str) {
            status_label->setText(QString::fromStdString(str));
        };
        reporter = CreateColorMapReporter(custom_plot, on_mouse_move);
    }

    QCustomPlot* customPlot() { return custom_plot; }
};

ColorMapCanvas::ColorMapCanvas(QWidget* parent)
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

ColorMapCanvas::~ColorMapCanvas() = default;

void ColorMapCanvas::setItem(ColorMapViewportItem* viewport_item)
{
    p_impl->viewport_controller->setItem(viewport_item);
}

//! Creates adapter to convert widget coordinates, to QCustomPlot internal coordinate system
//! (defined by its axes).

QExtUniquePointer<SceneAdapterInterface> ColorMapCanvas::createSceneAdapter() const
{
    return qextMakeUnique<CustomPlotSceneAdapter>(p_impl->customPlot());
}
