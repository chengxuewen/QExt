// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_VIEWPORTITEM_H
#define MVVM_STANDARDITEMS_VIEWPORTITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView {

class QExtMvvmViewportAxisItem;

//! Base class to represent 2D viewport.
//! Contains x,y axis, indended to display graphs or 2d colormaps.

class QEXT_MVVM_API QExtMvvmViewportItem : public QExtMvvmCompoundItem {
public:
    static constexpr const char *P_XAXIS = "P_XAXIS";
    static constexpr const char *P_YAXIS = "P_YAXIS";
    static constexpr const char *T_ITEMS = "T_ITEMS";

    QExtMvvmViewportItem(const QExtMvvmModelType& model);

    QExtMvvmViewportAxisItem* xAxis() const;

    QExtMvvmViewportAxisItem* yAxis() const;

    virtual void setViewportToContent(double left, double top, double right, double bottom);

    virtual void setViewportToContent();

protected:
    void register_xy_axes();

protected:
    virtual std::pair<double, double> data_xaxis_range() const = 0;
    virtual std::pair<double, double> data_yaxis_range() const = 0;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_VIEWPORTITEM_H
