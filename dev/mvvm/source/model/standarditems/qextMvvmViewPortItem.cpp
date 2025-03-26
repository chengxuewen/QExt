// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmViewPortItem.h>
#include <qextMvvmModelUtils.h>
#include <qextMvvmAxisItems.h>

using namespace ModelView;

QExtMvvmViewportItem::QExtMvvmViewportItem(const ModelView::QExtMvvmModelType& model) : QExtMvvmCompoundItem(model) {}

QExtMvvmViewportAxisItem* QExtMvvmViewportItem::xAxis() const
{
    return item<QExtMvvmViewportAxisItem>(P_XAXIS);
}

QExtMvvmViewportAxisItem* QExtMvvmViewportItem::yAxis() const
{
    return item<QExtMvvmViewportAxisItem>(P_YAXIS);
}

//! Sets range of x,y window to show all data.
//! Allows adding an additional margin to automatically calculated axis range. Margins are
//! given in relative units wrt calculated axis range.
//! Example: setViewportToContent(0.0, 0.1, 0.0, 0.1) will set axes to show all graphs with 10% gap
//! above and below graph's max and min.

void QExtMvvmViewportItem::setViewportToContent(double left, double top, double right, double bottom)
{
    Utils::BeginMacros(this, "setViewportToContent");
    auto xAxisRange = data_xaxis_range();
    xAxis()->set_range(xAxisRange.first - (xAxisRange.second - xAxisRange.first) * left,
                       xAxisRange.second + (xAxisRange.second - xAxisRange.first) * right);

    auto yAxisRange = data_yaxis_range();
    yAxis()->set_range(yAxisRange.first - (yAxisRange.second - yAxisRange.first) * bottom,
                       yAxisRange.second + (yAxisRange.second - yAxisRange.first) * top);
    Utils::EndMacros(this);
}

//! Sets range of x,y window to show all data.

void QExtMvvmViewportItem::setViewportToContent()
{
    Utils::BeginMacros(this, "setViewportToContent");
    auto xAxisRange = data_xaxis_range();
    xAxis()->set_range(xAxisRange.first, xAxisRange.second);

    auto yAxisRange = data_yaxis_range();
    yAxis()->set_range(yAxisRange.first, yAxisRange.second);
    Utils::EndMacros(this);
}

void QExtMvvmViewportItem::register_xy_axes()
{
    addProperty<QExtMvvmViewportAxisItem>(P_XAXIS)->setDisplayName("X axis");
    addProperty<QExtMvvmViewportAxisItem>(P_YAXIS)->setDisplayName("Y axis");
}
