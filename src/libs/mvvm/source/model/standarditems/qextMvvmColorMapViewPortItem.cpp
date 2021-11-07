// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <qextMvvmAxisItems.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmColorMapViewPortItem.h>
#include <qextMvvmData2dItem.h>
#include <QVector>

namespace
{
const QPair<double, double> default_axis_range{0.0, 1.0};
}



QEXTMvvmColorMapViewportItem::QEXTMvvmColorMapViewportItem() : QEXTMvvmViewportItem(QEXTMvvmConstants::ColorMapViewportItemType)
{
    register_xy_axes();
    addProperty<QEXTMvvmViewportAxisItem>(P_ZAXIS)->setDisplayName("color-axis");
    // for the moment allow only one QEXTMvvmColorMapItem
    registerTag(QEXTMvvmTagInfo(T_ITEMS, 0, 1, {QEXTMvvmConstants::ColorMapItemType}), /*set_default*/ true);
}

QEXTMvvmViewportAxisItem* QEXTMvvmColorMapViewportItem::zAxis() const
{
    return item<QEXTMvvmViewportAxisItem>(P_ZAXIS);
}

void QEXTMvvmColorMapViewportItem::setViewportToContent()
{
    QEXTMvvmViewportItem::setViewportToContent();
    update_data_range();
}

//! Returns range of x-axis as defined in underlying QEXTMvvmData2DItem.

QPair<double, double> QEXTMvvmColorMapViewportItem::dataXAxisRange() const
{
    auto dataItem = data_item();
    return dataItem && dataItem->xAxis() ? dataItem->xAxis()->range() : default_axis_range;
}

//! Returns range of y-axis as defined in underlying QEXTMvvmData2DItem.

QPair<double, double> QEXTMvvmColorMapViewportItem::dataYAxisRange() const
{
    auto dataItem = data_item();
    return dataItem && dataItem->yAxis() ? dataItem->yAxis()->range() : default_axis_range;
}

//! Returns QEXTMvvmData2DItem if exists.

QEXTMvvmData2DItem* QEXTMvvmColorMapViewportItem::data_item() const
{
    auto colormap_item = item<QEXTMvvmColorMapItem>(T_ITEMS);
    return colormap_item ? colormap_item->dataItem() : nullptr;
}

//! Updates zAxis to lower, upper values over all data points.

void QEXTMvvmColorMapViewportItem::update_data_range()
{
    if (auto dataItem = data_item(); dataItem) {
        auto values = dataItem->content();
        auto [lower, upper] = std::minmax_element(std::begin(values), std::end(values));
        zAxis()->set_range(*lower, *upper);
    }
}
