#include <qextMvvmGraphPlotController.h>
#include <qextMvvmGraphViewPortPlotController.h>
#include <qextMvvmViewPortAxisPlotController.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmGraphViewPortItem.h>

#include <QList>

#include <qcustomplot.h>

#include <stdexcept>

struct QEXTMvvmGraphViewportPlotController::GraphViewportPlotControllerImpl {
    QEXTMvvmGraphViewportPlotController *m_master{nullptr};
    QCustomPlot *m_customPlot{nullptr};
    QList<QSharedPointer<QEXTMvvmGraphPlotController> > m_graphControllers;
    QScopedPointer<QEXTMvvmViewportAxisPlotController> m_xAxisController;
    QScopedPointer<QEXTMvvmViewportAxisPlotController> m_yAxisController;

    GraphViewportPlotControllerImpl(QEXTMvvmGraphViewportPlotController *master, QCustomPlot* plot)
        : m_master(master), m_customPlot(plot)
    {
    }

    QEXTMvvmGraphViewportItem* viewport_item() { return m_master->currentItem(); }

    //! Setup controller components.
    void setup_components()
    {
        create_axis_controllers();
        create_graph_controllers();
    }

    //! Creates axes controllers.

    void create_axis_controllers()
    {
        auto viewport = viewport_item();

        m_xAxisController.reset(new QEXTMvvmViewportAxisPlotController(m_customPlot->xAxis));
        m_xAxisController->setItem(viewport->xAxis());

        m_yAxisController.reset(new QEXTMvvmViewportAxisPlotController(m_customPlot->yAxis));
        m_yAxisController->setItem(viewport->yAxis());
    }

    //! Run through all QEXTMvvmGraphItem's and create graph controllers for QCustomPlot.

    void create_graph_controllers()
    {
        m_graphControllers.clear();
        auto viewport = viewport_item();
        for (auto graph_item : viewport->graphItems()) {
            QSharedPointer<QEXTMvvmGraphPlotController> controller(new QEXTMvvmGraphPlotController(m_customPlot));
            controller->setItem(graph_item);
            m_graphControllers.append(controller);
        }
        viewport->setViewportToContent();
    }

    //! Adds controller for item.
    void addControllerForItem(QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow)
    {
        QEXTMvvmGraphItem *addedChild = dynamic_cast<QEXTMvvmGraphItem *>(parent->item(tagrow.tag, tagrow.row));

        for (auto& controller : m_graphControllers)
            if (controller->currentItem() == addedChild)
                throw std::runtime_error("Attempt to create second controller");

        QSharedPointer<QEXTMvvmGraphPlotController> controller(new QEXTMvvmGraphPlotController(m_customPlot));
        controller->setItem(addedChild);
        m_graphControllers.append(controller);
        m_customPlot->replot();
    }

    //! Remove QEXTMvvmGraphPlotController corresponding to QEXTMvvmGraphItem.

    void remove_controller_for_item(QEXTMvvmItem* parent, const QEXTMvvmTagRow& tagrow)
    {
        QEXTMvvmItem *childAboutToBeRemoved = parent->item(tagrow.tag, tagrow.row);
        QMutableListIterator<QSharedPointer<QEXTMvvmGraphPlotController> > iter(m_graphControllers);
        while (iter.hasNext())
        {
           QSharedPointer<QEXTMvvmGraphPlotController> controller = iter.value();
           if (controller->currentItem() == childAboutToBeRemoved)
           {
               iter.remove();
           }
        }
        m_customPlot->replot();
    }
};

QEXTMvvmGraphViewportPlotController::QEXTMvvmGraphViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(new GraphViewportPlotControllerImpl(this, custom_plot))
{
}

QEXTMvvmGraphViewportPlotController::~QEXTMvvmGraphViewportPlotController()
{

}

void QEXTMvvmGraphViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow) {
        p_impl->addControllerForItem(parent, tagrow);
    };
    addItemInsertedListener(on_item_inserted);

    auto on_about_to_remove_item = [this](QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow) {
        p_impl->remove_controller_for_item(parent, tagrow);
    };
    addItemAboutToBeRemovedListener(on_about_to_remove_item);

    p_impl->setup_components();
}
