// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/standarditems/colormapviewportitem.h"
#include "model/standarditems/axisitems.h"
#include "model/standarditems/colormapitem.h"
#include "model/standarditems/data2ditem.h"
#include <algorithm>
#include <vector>

namespace {
const std::pair<double, double> default_axis_range{0.0, 1.0};
}

using namespace ModelView;

QExtMvvmColorMapViewportItem::QExtMvvmColorMapViewportItem() : QExtMvvmViewportItem(Constants::ColorMapViewportItemType)
{
    register_xy_axes();
    addProperty<QExtMvvmViewportAxisItem>(P_ZAXIS)->setDisplayName("color-axis");
    // for the moment allow only one QExtMvvmColorMapItem
    registerTag(QExtMvvmTagInfo(T_ITEMS, 0, 1, {Constants::ColorMapItemType}), /*set_default*/ true);
}

QExtMvvmViewportAxisItem* QExtMvvmColorMapViewportItem::zAxis() const
{
    return item<QExtMvvmViewportAxisItem>(P_ZAXIS);
}

void QExtMvvmColorMapViewportItem::setViewportToContent()
{
    QExtMvvmViewportItem::setViewportToContent();
    update_data_range();
}

//! Returns range of x-axis as defined in underlying QExtMvvmData2DItem.

std::pair<double, double> QExtMvvmColorMapViewportItem::data_xaxis_range() const
{
    auto dataItem = data_item();
    return dataItem && dataItem->xAxis() ? dataItem->xAxis()->range() : default_axis_range;
}

//! Returns range of y-axis as defined in underlying QExtMvvmData2DItem.

std::pair<double, double> QExtMvvmColorMapViewportItem::data_yaxis_range() const
{
    auto dataItem = data_item();
    return dataItem && dataItem->yAxis() ? dataItem->yAxis()->range() : default_axis_range;
}

//! Returns QExtMvvmData2DItem if exists.

QExtMvvmData2DItem* QExtMvvmColorMapViewportItem::data_item() const
{
    auto colormap_item = item<QExtMvvmColorMapItem>(T_ITEMS);
    return colormap_item ? colormap_item->dataItem() : nullptr;
}

//! Updates zAxis to lower, upper values over all data points.

void QExtMvvmColorMapViewportItem::update_data_range()
{
    if (auto dataItem = data_item(); dataItem) {
        auto values = dataItem->content();
        auto [lower, upper] = std::minmax_element(std::begin(values), std::end(values));
        zAxis()->set_range(*lower, *upper);
    }
}
