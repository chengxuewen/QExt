// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGraphPlotController.h>
#include <qextMvvmData1DPlotController.h>
#include <qextMvvmPenController.h>
#include <qextMvvmData1DItem.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmPlotTableItems.h>
#include <qcustomplot.h>

using namespace ModelView;

struct QExtMvvmGraphPlotController::GraphItemControllerImpl {
    QExtMvvmGraphPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPGraph* m_graph{nullptr};
    QExtUniquePointer<QExtMvvmData1DPlotController> m_dataController;
    QExtUniquePointer<QExtMvvmPenController> m_penController;

    GraphItemControllerImpl(QExtMvvmGraphPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot)
    {
    }

    //! Setups controllers and updates graph properties.

    void init_graph()
    {
        m_graph = m_customPlot->addGraph();
        m_dataController = qextMakeUnique<QExtMvvmData1DPlotController>(m_graph);
        m_penController = qextMakeUnique<QExtMvvmPenController>(m_graph);

        update_data_controller();
        update_graph_pen();
        update_visible();
    }

    ~GraphItemControllerImpl()
    {
        if (m_graph)
            m_customPlot->removePlottable(m_graph);
    }

    QExtMvvmGraphItem* graph_item() { return m_self->currentItem(); }

    void update_data_controller() { m_dataController->setItem(graph_item()->dataItem()); }

    //! Updates graph pen from QExtMvvmGraphItem.

    void update_graph_pen() { m_penController->setItem(graph_item()->penItem()); }

    //! Update visible
    void update_visible()
    {
        m_graph->setVisible(graph_item()->property<bool>(QExtMvvmGraphItem::P_DISPLAYED));
        m_customPlot->replot();
    }

    void reset_graph()
    {
        m_dataController->setItem(nullptr);
        m_penController->setItem(nullptr);
        m_customPlot->removePlottable(m_graph);
        m_graph = nullptr;
        m_customPlot->replot();
    }
};

QExtMvvmGraphPlotController::QExtMvvmGraphPlotController(QCustomPlot* custom_plot)
    : p_impl(qextMakeUnique<GraphItemControllerImpl>(this, custom_plot))
{
}

void QExtMvvmGraphPlotController::subscribe()
{
    auto on_property_change = [this](QExtMvvmSessionItem*, const std::string& property_name) {
        if (property_name == QExtMvvmGraphItem::P_LINK)
            p_impl->update_data_controller();

        if (property_name == QExtMvvmGraphItem::P_DISPLAYED)
            p_impl->update_visible();
    };
    setOnPropertyChange(on_property_change);

    p_impl->init_graph();
}

void QExtMvvmGraphPlotController::unsubscribe()
{
    p_impl->reset_graph();
}

QExtMvvmGraphPlotController::~QExtMvvmGraphPlotController() = default;
