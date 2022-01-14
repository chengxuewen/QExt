// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "scenemodel.h"
#include "sceneitems.h"
#include <cmath>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmData2DItem.h>

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

std::unique_ptr<ModelView::QEXTMvvmItemCatalogue> CreateItemCatalogue()
{
    auto result = make_unique<QEXTMvvmItemCatalogue>();
    result->registerItem<RegionOfInterestItem>();
    return result;
}

} // namespace

SceneModel::SceneModel() : QEXTMvvmSessionModel("ColorMapModel")
{
    setItemCatalogue(CreateItemCatalogue());

    create_roi();
    create_data();
    create_colormap();
}

//! Recalculates data points in Data2DItem according to scale provided.

void SceneModel::update_data(double scale)
{
    fill_data(topItem<QEXTMvvmData2DItem>(), scale);
}

//! Creates item representing region of interest in the context of color map and graphics scene.

void SceneModel::create_roi()
{
    auto roi = insertItem<RegionOfInterestItem>();
    roi->setProperty(RegionOfInterestItem::P_XLOW, -2.0);
    roi->setProperty(RegionOfInterestItem::P_YLOW, 1.0);
    roi->setProperty(RegionOfInterestItem::P_XUP, 2.0);
    roi->setProperty(RegionOfInterestItem::P_YUP, 2.0);
}

//! Creates item to store 2D data and fills it with values.

void SceneModel::create_data()
{
    auto data_item = insertItem<QEXTMvvmData2DItem>();
    data_item->setAxes(QEXTMvvmFixedBinAxisItem::create(nbinsx, -5.0, 5.0),
                       QEXTMvvmFixedBinAxisItem::create(nbinsy, 0.0, 5.0));
    fill_data(data_item);
}

//! Creates items for graphical representation of 2D data in the form of a colormap.

void SceneModel::create_colormap()
{
    auto viewport_item = insertItem<QEXTMvvmColorMapViewportItem>();
    auto colormap_item = insertItem<QEXTMvvmColorMapItem>(viewport_item);
    colormap_item->setDataItem(topItem<QEXTMvvmData2DItem>());
}
