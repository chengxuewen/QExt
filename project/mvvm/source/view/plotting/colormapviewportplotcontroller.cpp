// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/plotting/colormapviewportplotcontroller.h"
#include "view/plotting/colormapplotcontroller.h"
#include "view/plotting/colorscaleplotcontroller.h"
#include "view/plotting/viewportaxisplotcontroller.h"
#include "model/standarditems/axisitems.h"
#include "model/standarditems/colormapitem.h"
#include "model/standarditems/colormapviewportitem.h"
#include <qcustomplot.h>

using namespace ModelView;

struct ColorMapViewportPlotController::ColorMapViewportPlotControllerImpl {
    ColorMapViewportPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPColorScale* m_colorScale{nullptr};
    QExtUniquePointer<ViewportAxisPlotController> m_xAxisController;
    QExtUniquePointer<ViewportAxisPlotController> m_yAxisController;
    QExtUniquePointer<ColorScalePlotController> m_colorScaleController;
    QExtUniquePointer<ColorMapPlotController> m_colorMapController;

    ColorMapViewportPlotControllerImpl(ColorMapViewportPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot), m_colorScale(new QCPColorScale(m_customPlot))
    {
        m_xAxisController = qextMakeUnique<ViewportAxisPlotController>(m_customPlot->xAxis);
        m_yAxisController = qextMakeUnique<ViewportAxisPlotController>(m_customPlot->yAxis);
        m_colorScaleController = qextMakeUnique<ColorScalePlotController>(m_colorScale);
        m_colorMapController = qextMakeUnique<ColorMapPlotController>(m_customPlot, m_colorScale);
    }

    ColorMapViewportItem* viewportItem() { return m_self->currentItem(); }

    //! Setup controller components.

    void setup_components()
    {
        auto viewport = viewportItem();
        m_xAxisController->setItem(viewport->xAxis());
        m_yAxisController->setItem(viewport->yAxis());
        m_colorScaleController->setItem(viewport->zAxis());
        auto colormap_item = viewportItem()->item<ColorMapItem>(ColorMapViewportItem::T_ITEMS);
        m_colorMapController->setItem(colormap_item);
        viewportItem()->setViewportToContent();
    }

    void unsubscribe_components()
    {
        m_xAxisController->setItem(nullptr);
        m_yAxisController->setItem(nullptr);
        m_colorScaleController->setItem(nullptr);
        m_colorMapController->setItem(nullptr);
    }
};

ColorMapViewportPlotController::ColorMapViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(qextMakeUnique<ColorMapViewportPlotControllerImpl>(this, custom_plot))
{
}

void ColorMapViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](SessionItem*, TagRow) { p_impl->setup_components(); };
    setOnItemInserted(on_item_inserted);

    p_impl->setup_components();
}

void ColorMapViewportPlotController::unsubscribe()
{
    p_impl->unsubscribe_components();
}

ColorMapViewportPlotController::~ColorMapViewportPlotController() = default;
