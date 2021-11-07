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
#include <QColor>
#include <qextMvvmAxisItems.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmData1dItem.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmGraphViewPortItem.h>
#include <qextMvvmUtils.h>
#include <qextMvvmWidgetUtils.h>

namespace
{

auto simulation_result(double amp_factor = 1.0)
{
    ToySimulation simulation(amp_factor);
    simulation.runSimulation();
    return simulation.simulationResult();
}

} // namespace



GraphModel::GraphModel() : QEXTMvvmModel("GraphModel")
{
    init_model();
}

//! Sets new values for existing data item.

void GraphModel::set_data(const QVector<double>& data)
{
    auto item = topItem<QEXTMvvmContainerItem>()->item<QEXTMvvmData1DItem>(QEXTMvvmContainerItem::T_ITEMS);
    item->setValues(data);
}

//! Creates data container, QEXTMvvmData1DItem, viewport and QEXTMvvmGraphItem.

void GraphModel::init_model()
{
    auto container = insertItem<QEXTMvvmContainerItem>();
    container->setDisplayName("Data container");

    auto viewport = insertItem<QEXTMvvmGraphViewportItem>();
    viewport->setDisplayName("Graph container");

    add_graph(container, viewport);
}

//! Adds Graph1DItem with some random points.

void GraphModel::add_graph(QEXTMvvmContainerItem* container,
                           QEXTMvvmGraphViewportItem* viewport)
{
    auto [xmin, xmax, points] = simulation_result(QEXTMvvmUtils::RandDouble(0.5, 1.0));

    auto data = insertItem<QEXTMvvmData1DItem>(container);
    data->setAxis<QEXTMvvmFixedBinAxisItem>(static_cast<int>(points.size()), xmin, xmax);
    data->setValues(points);

    auto graph = insertItem<QEXTMvvmGraphItem>(viewport);
    graph->setDataItem(data);
    graph->setNamedColor(QEXTMvvmWidgetUtils::RandomNamedColor());
}
