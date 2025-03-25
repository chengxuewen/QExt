// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGraphViewPortPlotController.h>
#include <qextMvvmGraphPlotController.h>
#include <qextMvvmViewPortAxisPlotController.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmGraphViewPortItem.h>
#include <qcustomplot.h>
#include <list>
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmGraphViewportPlotController::GraphViewportPlotControllerImpl {
    QExtMvvmGraphViewportPlotController* master{nullptr};
    QCustomPlot* custom_plot{nullptr};
    std::list<QExtUniquePointer<QExtMvvmGraphPlotController>> graph_controllers;
    QExtUniquePointer<QExtMvvmViewportAxisPlotController> xAxisController;
    QExtUniquePointer<QExtMvvmViewportAxisPlotController> yAxisController;

    GraphViewportPlotControllerImpl(QExtMvvmGraphViewportPlotController* master, QCustomPlot* plot)
        : master(master), custom_plot(plot)
    {
    }

    QExtMvvmGraphViewportItem* viewport_item() { return master->currentItem(); }

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

        xAxisController = qextMakeUnique<QExtMvvmViewportAxisPlotController>(custom_plot->xAxis);
        xAxisController->setItem(viewport->xAxis());

        yAxisController = qextMakeUnique<QExtMvvmViewportAxisPlotController>(custom_plot->yAxis);
        yAxisController->setItem(viewport->yAxis());
    }

    //! Run through all QExtMvvmGraphItem's and create graph controllers for QCustomPlot.

    void create_graph_controllers()
    {
        graph_controllers.clear();
        auto viewport = viewport_item();
        for (auto graph_item : viewport->graphItems()) {
            auto controller = qextMakeUnique<QExtMvvmGraphPlotController>(custom_plot);
            controller->setItem(graph_item);
            graph_controllers.push_back(std::move(controller));
        }
        viewport->setViewportToContent();
    }

    //! Adds controller for item.
    void add_controller_for_item(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow)
    {
        auto added_child = dynamic_cast<QExtMvvmGraphItem*>(parent->getItem(tagrow.tag, tagrow.row));

        for (auto& controller : graph_controllers)
            if (controller->currentItem() == added_child)
                throw std::runtime_error("Attempt to create second controller");

        auto controller = qextMakeUnique<QExtMvvmGraphPlotController>(custom_plot);
        controller->setItem(added_child);
        graph_controllers.push_back(std::move(controller));
        custom_plot->replot();
    }

    //! Remove QExtMvvmGraphPlotController corresponding to QExtMvvmGraphItem.

    void remove_controller_for_item(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow)
    {
        auto child_about_to_be_removed = parent->getItem(tagrow.tag, tagrow.row);
        auto if_func = [&](const QExtUniquePointer<QExtMvvmGraphPlotController>& cntrl) -> bool {
            return cntrl->currentItem() == child_about_to_be_removed;
        };
        graph_controllers.remove_if(if_func);
        custom_plot->replot();
    }
};

QExtMvvmGraphViewportPlotController::QExtMvvmGraphViewportPlotController(QCustomPlot* custom_plot)
    : p_impl(qextMakeUnique<GraphViewportPlotControllerImpl>(this, custom_plot))
{
}

void QExtMvvmGraphViewportPlotController::subscribe()
{
    auto on_item_inserted = [this](QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow) {
        p_impl->add_controller_for_item(parent, tagrow);
    };
    setOnItemInserted(on_item_inserted);

    auto on_about_to_remove_item = [this](QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow) {
        p_impl->remove_controller_for_item(parent, tagrow);
    };
    setOnAboutToRemoveItem(on_about_to_remove_item);

    p_impl->setup_components();
}

QExtMvvmGraphViewportPlotController::~QExtMvvmGraphViewportPlotController() = default;
