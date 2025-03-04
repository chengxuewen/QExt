// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphmodel.h"
#include "toysimulation.h"
#include "model/standarditems/axisitems.h"
#include "model/standarditems/containeritem.h"
#include "model/standarditems/data1ditem.h"
#include "model/standarditems/graphitem.h"
#include "model/standarditems/graphviewportitem.h"
#include "model/utils/numericutils.h"
#include "view/widgets/widgetutils.h"
#include <QColor>

namespace {

ToySimulation::Result simulation_result(double amp_factor = 1.0)
{
    ToySimulation simulation(amp_factor);
    simulation.runSimulation();
    return simulation.simulationResult();
}

} // namespace

using namespace ModelView;

GraphModel::GraphModel() : QExtMvvmSessionModel("GraphModel")
{
    init_model();
}

//! Sets new values for existing data item.

void GraphModel::set_data(const std::vector<double>& data)
{
    auto item = topItem<QExtMvvmContainerItem>()->item<QExtMvvmData1DItem>(QExtMvvmContainerItem::T_ITEMS);
    item->setValues(data);
}

//! Creates data container, QExtMvvmData1DItem, viewport and QExtMvvmGraphItem.

void GraphModel::init_model()
{
    auto container = insertItem<QExtMvvmContainerItem>();
    container->setDisplayName("Data container");

    auto viewport = insertItem<QExtMvvmGraphViewportItem>();
    viewport->setDisplayName("Graph container");

    add_graph(container, viewport);
}

//! Adds Graph1DItem with some random points.

void GraphModel::add_graph(ModelView::QExtMvvmContainerItem* container,
                           ModelView::QExtMvvmGraphViewportItem* viewport)
{
    auto [xmin, xmax, points] = simulation_result(ModelView::Utils::RandDouble(0.5, 1.0));

    auto data = insertItem<QExtMvvmData1DItem>(container);
    data->setAxis<QExtMvvmFixedBinAxisItem>(static_cast<int>(points.size()), xmin, xmax);
    data->setValues(points);

    auto graph = insertItem<QExtMvvmGraphItem>(viewport);
    graph->setDataItem(data);
    graph->setNamedColor(ModelView::Utils::RandomNamedColor());
}
