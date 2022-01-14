// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <list>
#include <plotting/qextMvvmColorMapPlotController.h>
#include <plotting/qextMvvmColorMapViewPortPlotController.h>
#include <plotting/qextMvvmColorScalePlotController.h>
#include <plotting/qextMvvmViewPortAxisPlotController.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qcustomplot.h>

using namespace ModelView;

struct QEXTMvvmColorMapViewportPlotController::ColorMapViewportPlotControllerImpl {
    QEXTMvvmColorMapViewportPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPColorScale* m_colorScale{nullptr};
    std::unique_ptr<QEXTMvvmViewportAxisPlotController> m_xAxisController;
    std::unique_ptr<QEXTMvvmViewportAxisPlotController> m_yAxisController;
    std::unique_ptr<QEXTMvvmColorScalePlotController> m_colorScaleController;
    std::unique_ptr<QEXTMvvmColorMapPlotController> m_colorMapController;

    ColorMapViewportPlotControllerImpl(QEXTMvvmColorMapViewportPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot), m_colorScale(new QCPColorScale(m_customPlot))
    {
        m_xAxisController = make_unique<QEXTMvvmViewportAxisPlotController>(m_customPlot->xAxis);
        m_yAxisController = make_unique<QEXTMvvmViewportAxisPlotController>(m_customPlot->yAxis);
        m_colorScaleController = make_unique<QEXTMvvmColorScalePlotController>(m_colorScale);
        m_colorMapController = make_unique<QEXTMvvmColorMapPlotController>(m_customPlot, m_colorScale);
    }

    QEXTMvvmColorMapViewportItem* viewportItem() { return m_self->currentItem(); }

    //! Setup controller components.

    void setup_components()
    {
        auto viewport = viewportItem();
        m_xAxisController->setItem(viewport->xAxis());
        m_yAxisController->setItem(viewport->yAxis());
        m_colorScaleController->setItem(viewport->zAxis());
        auto colormap_item = viewportItem()->item<QEXTMvvmColorMapItem>(QEXTMvvmColorMapViewportItem::T_ITEMS);
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

QEXTMvvmColorMapViewportPlotController::QEXTMvvmColorMapViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(make_unique<ColorMapViewportPlotControllerImpl>(this, custom_plot))
{
}

void QEXTMvvmColorMapViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](QEXTMvvmSessionItem*, QEXTMvvmTagRow) { p_impl->setup_components(); };
    setOnItemInserted(on_item_inserted);

    p_impl->setup_components();
}

void QEXTMvvmColorMapViewportPlotController::unsubscribe()
{
    p_impl->unsubscribe_components();
}

QEXTMvvmColorMapViewportPlotController::~QEXTMvvmColorMapViewportPlotController() = default;
