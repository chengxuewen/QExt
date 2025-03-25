// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmColorMapViewPortPlotController.h>
#include <qextMvvmColorMapPlotController.h>
#include <qextMvvmColorScalePlotController.h>
#include <qextMvvmViewPortAxisPlotController.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qcustomplot.h>

using namespace ModelView;

struct QExtMvvmColorMapViewportPlotController::ColorMapViewportPlotControllerImpl {
    QExtMvvmColorMapViewportPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPColorScale* m_colorScale{nullptr};
    QExtUniquePointer<QExtMvvmViewportAxisPlotController> m_xAxisController;
    QExtUniquePointer<QExtMvvmViewportAxisPlotController> m_yAxisController;
    QExtUniquePointer<QExtMvvmColorScalePlotController> m_colorScaleController;
    QExtUniquePointer<QExtMvvmColorMapPlotController> m_colorMapController;

    ColorMapViewportPlotControllerImpl(QExtMvvmColorMapViewportPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot), m_colorScale(new QCPColorScale(m_customPlot))
    {
        m_xAxisController = qextMakeUnique<QExtMvvmViewportAxisPlotController>(m_customPlot->xAxis);
        m_yAxisController = qextMakeUnique<QExtMvvmViewportAxisPlotController>(m_customPlot->yAxis);
        m_colorScaleController = qextMakeUnique<QExtMvvmColorScalePlotController>(m_colorScale);
        m_colorMapController = qextMakeUnique<QExtMvvmColorMapPlotController>(m_customPlot, m_colorScale);
    }

    QExtMvvmColorMapViewportItem* viewportItem() { return m_self->currentItem(); }

    //! Setup controller components.

    void setup_components()
    {
        auto viewport = viewportItem();
        m_xAxisController->setItem(viewport->xAxis());
        m_yAxisController->setItem(viewport->yAxis());
        m_colorScaleController->setItem(viewport->zAxis());
        auto colormap_item = viewportItem()->item<QExtMvvmColorMapItem>(QExtMvvmColorMapViewportItem::T_ITEMS);
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

QExtMvvmColorMapViewportPlotController::QExtMvvmColorMapViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(qextMakeUnique<ColorMapViewportPlotControllerImpl>(this, custom_plot))
{
}

void QExtMvvmColorMapViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](QExtMvvmSessionItem*, QExtMvvmTagRow) { p_impl->setup_components(); };
    setOnItemInserted(on_item_inserted);

    p_impl->setup_components();
}

void QExtMvvmColorMapViewportPlotController::unsubscribe()
{
    p_impl->unsubscribe_components();
}

QExtMvvmColorMapViewportPlotController::~QExtMvvmColorMapViewportPlotController() = default;
