// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <qextMvvmComboProperty.h>
#include <plotting/qextMvvmData1DPlotController.h>
#include <plotting/qextMvvmGraphPlotController.h>
#include <plotting/qextMvvmPenController.h>
#include <qextMvvmData1DItem.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmPlotTableItems.h>

using namespace ModelView;

struct QEXTMvvmGraphPlotController::GraphItemControllerImpl {
    QEXTMvvmGraphPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPGraph* m_graph{nullptr};
    std::unique_ptr<QEXTMvvmData1DPlotController> m_dataController;
    std::unique_ptr<QEXTMvvmPenController> m_penController;

    GraphItemControllerImpl(QEXTMvvmGraphPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot)
    {
    }

    //! Setups controllers and updates graph properties.

    void init_graph()
    {
        m_graph = m_customPlot->addGraph();
        m_dataController = make_unique<QEXTMvvmData1DPlotController>(m_graph);
        m_penController = make_unique<QEXTMvvmPenController>(m_graph);

        update_data_controller();
        update_graph_pen();
        update_visible();
    }

    ~GraphItemControllerImpl()
    {
        if (m_graph)
            m_customPlot->removePlottable(m_graph);
    }

    QEXTMvvmGraphItem* graph_item() { return m_self->currentItem(); }

    void update_data_controller() { m_dataController->setItem(graph_item()->dataItem()); }

    //! Updates graph pen from GraphItem.

    void update_graph_pen()
    {
        m_penController->setItem(graph_item()->penItem());
    }

    //! Update visible
    void update_visible()
    {
        m_graph->setVisible(graph_item()->property<bool>(QEXTMvvmGraphItem::P_DISPLAYED));
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

QEXTMvvmGraphPlotController::QEXTMvvmGraphPlotController(QCustomPlot* custom_plot)
    : p_impl(make_unique<GraphItemControllerImpl>(this, custom_plot))
{
}

void QEXTMvvmGraphPlotController::subscribe()
{
    auto on_property_change = [this](QEXTMvvmSessionItem*, const std::string& property_name) {
        if (property_name == QEXTMvvmGraphItem::P_LINK)
            p_impl->update_data_controller();

        if (property_name == QEXTMvvmGraphItem::P_DISPLAYED)
            p_impl->update_visible();
    };
    setOnPropertyChange(on_property_change);

    p_impl->init_graph();
}

void QEXTMvvmGraphPlotController::unsubscribe()
{
    p_impl->reset_graph();
}

QEXTMvvmGraphPlotController::~QEXTMvvmGraphPlotController() = default;
