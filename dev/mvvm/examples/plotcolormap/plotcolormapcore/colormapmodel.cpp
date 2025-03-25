// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "colormapmodel.h"
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmData2DItem.h>
#include <cmath>

using namespace ModelView;

namespace {
const int nbinsx = 200;
const int nbinsy = 100;

// fills with data point
void fill_data(QExtMvvmData2DItem* data_item, double scale = 1.0)
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

namespace PlotColorMap {

ColorMapModel::ColorMapModel() : QExtMvvmSessionModel("ColorMapModel")
{
    populateModel();
}

//! Updates data.

void ColorMapModel::updateData(double scale)
{
    auto data_item = dataContainer()->item<QExtMvvmData2DItem>(QExtMvvmContainerItem::T_ITEMS);
    fill_data(data_item, scale);
}

void ColorMapModel::addColormap()
{
    auto data_item = insertItem<QExtMvvmData2DItem>(dataContainer());
    data_item->setAxes(QExtMvvmFixedBinAxisItem::create(nbinsx, -5.0, 5.0),
                       QExtMvvmFixedBinAxisItem::create(nbinsy, 0.0, 5.0));
    fill_data(data_item);

    auto viewport_item = insertItem<QExtMvvmColorMapViewportItem>();
    auto colormap_item = insertItem<QExtMvvmColorMapItem>(viewport_item);
    colormap_item->setDataItem(data_item);
}

QExtMvvmContainerItem* ColorMapModel::dataContainer()
{
    return topItem<QExtMvvmContainerItem>();
}

void ColorMapModel::populateModel()
{
    auto container = insertItem<QExtMvvmContainerItem>();
    container->setDisplayName("Data container");

    addColormap();
}

} // namespace PlotColorMap
