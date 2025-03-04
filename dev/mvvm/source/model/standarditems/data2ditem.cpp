// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/standarditems/data2ditem.h"
#include "model/standarditems/axisitems.h"
#include <stdexcept>

using namespace ModelView;

namespace {
size_t total_bin_count(QExtMvvmData2DItem* item)
{
    if (auto xaxis = item->xAxis(); xaxis)
        if (auto yaxis = item->yAxis(); yaxis)
            return static_cast<size_t>(xaxis->size() * yaxis->size());
    return 0;
}
} // namespace

QExtMvvmData2DItem::QExtMvvmData2DItem() : QExtMvvmCompoundItem(Constants::Data2DItemType)
{
    // prevent editing in widgets, since there is no corresponding editor
    addProperty(P_VALUES, std::vector<double>())->setDisplayName("Values")->setEditable(false);

    registerTag(QExtMvvmTagInfo(T_XAXIS, 0, 1, {Constants::FixedBinAxisItemType}));
    registerTag(QExtMvvmTagInfo(T_YAXIS, 0, 1, {Constants::FixedBinAxisItemType}));
}

//! Sets axes and put data points to zero.

void QExtMvvmData2DItem::setAxes(QExtUniquePointer<QExtMvvmBinnedAxisItem> x_axis,
                         QExtUniquePointer<QExtMvvmBinnedAxisItem> y_axis)
{
    insert_axis(std::move(x_axis), T_XAXIS);
    insert_axis(std::move(y_axis), T_YAXIS);
    setContent(std::vector<double>(total_bin_count(this), 0.0));
}

//! Returns x-axis (nullptr if it doesn't exist).

QExtMvvmBinnedAxisItem* QExtMvvmData2DItem::xAxis() const
{
    return item<QExtMvvmBinnedAxisItem>(T_XAXIS);
}

//! Returns y-axis (nullptr if it doesn't exist).

QExtMvvmBinnedAxisItem* QExtMvvmData2DItem::yAxis() const
{
    return item<QExtMvvmBinnedAxisItem>(T_YAXIS);
}

void QExtMvvmData2DItem::setContent(const std::vector<double>& data)
{
    if (total_bin_count(this) != data.size())
        throw std::runtime_error("QExtMvvmData1DItem::setContent() -> Data doesn't match size of axis");
    setProperty(P_VALUES, data);
}

//! Returns 1d buffer representing 2d data.

std::vector<double> QExtMvvmData2DItem::content() const
{
    return property<std::vector<double>>(P_VALUES);
}

//! Insert axis under given tag. Previous axis will be deleted and data points invalidated.

void QExtMvvmData2DItem::insert_axis(QExtUniquePointer<QExtMvvmBinnedAxisItem> axis, const std::string& tag)
{
    // removing current axis
    if (getItem(tag, 0))
        takeItem({tag, 0});

    insertItem(std::move(axis), {tag, 0});
}
