// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "scenemodel.h"
#include "regionofinterestitem.h"
#include "model/standarditems/axisitems.h"
#include "model/standarditems/colormapitem.h"
#include "model/standarditems/colormapviewportitem.h"
#include "model/standarditems/containeritem.h"
#include "model/standarditems/data2ditem.h"
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

namespace GraphicsProxy {

SceneModel::SceneModel() : QExtMvvmSessionModel("ColorMapModel")
{
    registerItem<RegionOfInterestItem>();

    create_roi();
    create_data();
    create_colormap();
}

//! Recalculates data points in QExtMvvmData2DItem according to scale provided.

void SceneModel::update_data(double scale)
{
    fill_data(topItem<QExtMvvmData2DItem>(), scale);
}

//! Creates item representing region of interest in the context of color map and graphics scene.

void SceneModel::create_roi()
{
    auto roi = insertItem<RegionOfInterestItem>();
    roi->setCorners(-2.0, 1.0, 2.0, 2.0);
}

//! Creates item to store 2D data and fills it with values.

void SceneModel::create_data()
{
    auto data_item = insertItem<QExtMvvmData2DItem>();
    data_item->setAxes(QExtMvvmFixedBinAxisItem::create(nbinsx, -5.0, 5.0),
                       QExtMvvmFixedBinAxisItem::create(nbinsy, 0.0, 5.0));
    fill_data(data_item);
}

//! Creates items for graphical representation of 2D data in the form of a colormap.

void SceneModel::create_colormap()
{
    auto viewport_item = insertItem<QExtMvvmColorMapViewportItem>();
    auto colormap_item = insertItem<QExtMvvmColorMapItem>(viewport_item);
    colormap_item->setDataItem(topItem<QExtMvvmData2DItem>());
}

} // namespace GraphicsProxy
