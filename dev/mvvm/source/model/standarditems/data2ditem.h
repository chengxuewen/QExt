// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_DATA2DITEM_H
#define MVVM_STANDARDITEMS_DATA2DITEM_H

#include "model/model/compounditem.h"
#include <vector>

namespace ModelView {

class QExtMvvmBinnedAxisItem;

//! Represents two-dimensional data (axes definition and 2d array of values).
//! Values are stored in QExtMvvmData2DItem itself, axes are attached as children. Corresponding plot
//! properties will be served by QExtMvvmColorMapItem.

class QEXT_MVVM_API QExtMvvmData2DItem : public QExtMvvmCompoundItem {
public:
    static inline const std::string P_VALUES = "P_VALUES";
    static inline const std::string T_XAXIS = "T_XAXIS";
    static inline const std::string T_YAXIS = "T_YAXIS";

    QExtMvvmData2DItem();

    void setAxes(QExtUniquePointer<QExtMvvmBinnedAxisItem> x_axis, QExtUniquePointer<QExtMvvmBinnedAxisItem> y_axis);

    QExtMvvmBinnedAxisItem* xAxis() const;

    QExtMvvmBinnedAxisItem* yAxis() const;

    void setContent(const std::vector<double>& data);

    std::vector<double> content() const;

private:
    void insert_axis(QExtUniquePointer<QExtMvvmBinnedAxisItem> axis, const std::string& tag);
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_DATA2DITEM_H
