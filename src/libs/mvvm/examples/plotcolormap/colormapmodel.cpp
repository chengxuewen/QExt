// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "colormapmodel.h"
#include <cmath>
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmData2dItem.h>

using namespace ModelView;

namespace
{
const int nbinsx = 200;
const int nbinsy = 100;

// fills with data point
void fill_data(QEXTMvvmData2DItem* data_item, double scale = 1.0)
{
    const auto xAxis = data_item->xAxis();
    const auto yAxis = data_item->yAxis();
    std::vector<double> values;
    for (auto y : yAxis->binCenters()) {
        for (auto x : xAxis->binCenters()) {
            double r = scale * (3.0 * std::sqrt(x * x + y * y) + 1e-2);
            double z = 2 * x * (std::cos(r + 2) / r - std::sin(r + 2) / r);
            values.push_back(z);
        }
    }

    data_item->setContent(values);
}
} // namespace

namespace PlotColorMap
{

ColorMapModel::ColorMapModel() : QEXTMvvmSessionModel("ColorMapModel")
{
    init_model();
}

//! Updates data.

void ColorMapModel::update_data(double scale)
{
    auto data_item = data_container()->item<QEXTMvvmData2DItem>(QEXTMvvmContainerItem::T_ITEMS);
    fill_data(data_item, scale);
}

void ColorMapModel::add_colormap()
{
    auto data_item = insertItem<QEXTMvvmData2DItem>(data_container());
    data_item->setAxes(QEXTMvvmFixedBinAxisItem::create(nbinsx, -5.0, 5.0),
                       QEXTMvvmFixedBinAxisItem::create(nbinsy, 0.0, 5.0));
    fill_data(data_item);

    auto viewport_item = insertItem<QEXTMvvmColorMapViewportItem>();
    auto colormap_item = insertItem<QEXTMvvmColorMapItem>(viewport_item);
    colormap_item->setDataItem(data_item);
}

QEXTMvvmContainerItem* ColorMapModel::data_container()
{
    return topItem<QEXTMvvmContainerItem>();
}

void ColorMapModel::init_model()
{
    auto container = insertItem<QEXTMvvmContainerItem>();
    container->setDisplayName("Data container");

    add_colormap();
}

} // namespace PlotColorMap
