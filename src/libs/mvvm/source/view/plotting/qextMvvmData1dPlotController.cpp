#include <qextMvvmData1dPlotController.h>
#include <qextMvvmData1dItem.h>

#include <qcustomplot.h>

#include <stdexcept>

struct QEXTMvvmData1DPlotController::QEXTMvvmData1DPlotControllerImpl {
    QCPGraph* m_graph{nullptr};
    QCPErrorBars* m_errorBars{nullptr};

    QEXTMvvmData1DPlotControllerImpl(QCPGraph* graph) : m_graph(graph)
    {
        if (!m_graph)
            throw std::runtime_error("Uninitialised graph in QEXTMvvmData1DPlotController");
    }

    void initGraphFromItem(QEXTMvvmData1DItem* item)
    {
        assert(item);
        updateGraphPointsFromItem(item);
        updateErrorBarsFromItem(item);
    }

    void updateGraphPointsFromItem(QEXTMvvmData1DItem* item)
    {
        m_graph->setData(item->binCenters(), item->binValues());
        customPlot()->replot();
    }

    void updateErrorBarsFromItem(QEXTMvvmData1DItem* item)
    {
        auto errors = item->binErrors();
        if (errors.empty()) {
            resetErrorBars();
            return;
        }

        if (!m_errorBars)
            m_errorBars = new QCPErrorBars(customPlot()->xAxis, customPlot()->yAxis);

        m_errorBars->setData(errors);
        m_errorBars->setDataPlottable(m_graph);
    }

    void resetGraph()
    {
        m_graph->setData(QVector<double>{}, QVector<double>{});
        customPlot()->replot();
    }

    void resetErrorBars()
    {
        delete m_errorBars;
        m_errorBars = nullptr;
    }

    QCustomPlot* customPlot()
    {
        assert(m_graph);
        return m_graph->parentPlot();
    }
};

QEXTMvvmData1DPlotController::QEXTMvvmData1DPlotController(QCPGraph* graph)
    : p_impl(new QEXTMvvmData1DPlotControllerImpl(graph))
{
}

QEXTMvvmData1DPlotController::~QEXTMvvmData1DPlotController() = default;

void QEXTMvvmData1DPlotController::subscribe()
{
    auto on_property_change = [this](QEXTMvvmItem*, QString property_name) {
        if (property_name == QEXTMvvmData1DItem::P_VALUES)
            p_impl->updateGraphPointsFromItem(currentItem());
        if (property_name == QEXTMvvmData1DItem::P_ERRORS)
            p_impl->updateErrorBarsFromItem(currentItem());
    };
    addItemPropertyChangedListener(on_property_change);

    p_impl->initGraphFromItem(currentItem());
}

void QEXTMvvmData1DPlotController::unsubscribe()
{
    p_impl->resetGraph();
}
