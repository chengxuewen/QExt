// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H
#define MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H

#include <qextMvvmViewPortItem.h>

namespace ModelView {

class QExtMvvmData2DItem;

//! Container with viewport and collection of QExtMvvmColorMapItem's to plot.

class QEXT_MVVM_API QExtMvvmColorMapViewportItem : public QExtMvvmViewportItem {
public:
    static constexpr const char *P_ZAXIS = "P_ZAXIS";

    QExtMvvmColorMapViewportItem();

    QExtMvvmViewportAxisItem* zAxis() const;

    using QExtMvvmViewportItem::setViewportToContent;
    void setViewportToContent() override;

protected:
    virtual std::pair<double, double> data_xaxis_range() const override;
    virtual std::pair<double, double> data_yaxis_range() const override;

private:
    QExtMvvmData2DItem* data_item() const;
    void update_data_range();
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H
