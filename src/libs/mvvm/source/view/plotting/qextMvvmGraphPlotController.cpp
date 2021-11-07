#include <qextMvvmComboProperty.h>
#include <qextMvvmData1dPlotController.h>
#include <qextMvvmGraphPlotController.h>
#include <qextMvvmPenController.h>
#include <qextMvvmData1dItem.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmPlotTableItems.h>

#include "qcustomplot.h"


struct QEXTMvvmGraphPlotController::GraphItemControllerImpl {
    QEXTMvvmGraphPlotController* m_self{nullptr};
    QCustomPlot* m_customPlot{nullptr};
    QCPGraph* m_graph{nullptr};
    QScopedPointer<QEXTMvvmData1DPlotController> m_dataController;
    QScopedPointer<QEXTMvvmPenController> m_penController;

    GraphItemControllerImpl(QEXTMvvmGraphPlotController* master, QCustomPlot* plot)
        : m_self(master), m_customPlot(plot)
    {
    }

    //! Setups controllers and updates graph properties.

    void init_graph()
    {
        m_graph = m_customPlot->addGraph();
        m_dataController.reset(new QEXTMvvmData1DPlotController(m_graph));
        m_penController.reset(new QEXTMvvmPenController(m_graph));

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

    //! Updates graph pen from QEXTMvvmGraphItem.

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
    : p_impl(new GraphItemControllerImpl(this, custom_plot))
{
}

void QEXTMvvmGraphPlotController::subscribe()
{
    auto on_property_change = [this](QEXTMvvmItem*, const QString& property_name) {
        if (property_name == QEXTMvvmGraphItem::P_LINK)
            p_impl->update_data_controller();

        if (property_name == QEXTMvvmGraphItem::P_DISPLAYED)
            p_impl->update_visible();
    };
    addItemPropertyChangedListener(on_property_change);

    p_impl->init_graph();
}

void QEXTMvvmGraphPlotController::unsubscribe()
{
    p_impl->reset_graph();
}

QEXTMvvmGraphPlotController::~QEXTMvvmGraphPlotController() = default;
