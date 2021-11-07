// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmUtils.h>
#include <qextMvvmAxisItems.h>
#include <qextMvvmViewPortItem.h>



QEXTMvvmViewportItem::QEXTMvvmViewportItem(const QString& model) : QEXTMvvmCompoundItem(model) {}

QEXTMvvmViewportAxisItem* QEXTMvvmViewportItem::xAxis() const
{
    return item<QEXTMvvmViewportAxisItem>(P_XAXIS);
}

QEXTMvvmViewportAxisItem* QEXTMvvmViewportItem::yAxis() const
{
    return item<QEXTMvvmViewportAxisItem>(P_YAXIS);
}

//! Sets range of x,y window to show all data.
//! Allows adding an additional margin to automatically calculated axis range. Margins are
//! given in relative units wrt calculated axis range.
//! Example: setViewportToContent(0.0, 0.1, 0.0, 0.1) will set axes to show all graphs with 10% gap
//! above and below graph's max and min.

void QEXTMvvmViewportItem::setViewportToContent(double left, double top, double right, double bottom)
{
    QEXTMvvmUtils::BeginMacros(this, "setViewportToContent");
    auto [xmin, xmax] = dataXAxisRange();
    xAxis()->set_range(xmin - (xmax - xmin) * left, xmax + (xmax - xmin) * right);

    auto [ymin, ymax] = dataYAxisRange();
    yAxis()->set_range(ymin - (ymax - ymin) * bottom, ymax + (ymax - ymin) * top);
    QEXTMvvmUtils::EndMacros(this);
}

//! Sets range of x,y window to show all data.

void QEXTMvvmViewportItem::setViewportToContent()
{
    QEXTMvvmUtils::BeginMacros(this, "setViewportToContent");
    auto [xmin, xmax] = dataXAxisRange();
    xAxis()->set_range(xmin, xmax);

    auto [ymin, ymax] = dataYAxisRange();
    yAxis()->set_range(ymin, ymax);
    QEXTMvvmUtils::EndMacros(this);
}

void QEXTMvvmViewportItem::register_xy_axes()
{
    addProperty<QEXTMvvmViewportAxisItem>(P_XAXIS)->setDisplayName("X axis");
    addProperty<QEXTMvvmViewportAxisItem>(P_YAXIS)->setDisplayName("Y axis");
}
