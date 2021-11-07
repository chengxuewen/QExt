#include <list>
#include <qextMvvmColorMapPlotController.h>
#include <qextMvvmColorMapViewPortPlotController.h>
#include <qextMvvmColorScalePlotController.h>
#include <qextMvvmViewPortAxisPlotController.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qcustomplot.h>



struct QEXTMvvmColorMapViewportPlotController::ColorMapViewportPlotControllerImpl {
    QEXTMvvmColorMapViewportPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPColorScale* m_colorScale{nullptr};
    QScopedPointer<QEXTMvvmViewportAxisPlotController> m_xAxisController;
    QScopedPointer<QEXTMvvmViewportAxisPlotController> m_yAxisController;
    QScopedPointer<QEXTMvvmColorScalePlotController> m_colorScaleController;
    QScopedPointer<QEXTMvvmColorMapPlotController> m_colorMapController;

    ColorMapViewportPlotControllerImpl(QEXTMvvmColorMapViewportPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot), m_colorScale(new QCPColorScale(m_customPlot))
    {
        m_xAxisController.reset(new QEXTMvvmViewportAxisPlotController(m_customPlot->xAxis));
        m_yAxisController.reset(new QEXTMvvmViewportAxisPlotController(m_customPlot->yAxis));
        m_colorScaleController.reset(new QEXTMvvmColorScalePlotController(m_colorScale));
        m_colorMapController.reset(new QEXTMvvmColorMapPlotController(m_customPlot, m_colorScale));
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
    : p_impl(new ColorMapViewportPlotControllerImpl(this, custom_plot))
{
}

QEXTMvvmColorMapViewportPlotController::~QEXTMvvmColorMapViewportPlotController()
{

}

void QEXTMvvmColorMapViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](QEXTMvvmItem*, QEXTMvvmTagRow) { p_impl->setup_components(); };
    addItemInsertedListener(on_item_inserted);

    p_impl->setup_components();
}

void QEXTMvvmColorMapViewportPlotController::unsubscribe()
{
    p_impl->unsubscribe_components();
}
