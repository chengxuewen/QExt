// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_COLORMAPITEM_H
#define MVVM_STANDARDITEMS_COLORMAPITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView {

class QExtMvvmData2DItem;

//! Two-dimensional color map representation of QExtMvvmData2DItem.
//! Contains plot properties (i.e. color, gradient etc) and link to QExtMvvmData2DItem, which will provide
//! actual data to plot. QExtMvvmColorMapItem is intended for plotting only via QExtMvvmColorMapViewportItem.

class QEXT_MVVM_API QExtMvvmColorMapItem : public QExtMvvmCompoundItem {
public:
    static constexpr const char *P_LINK = "P_LINK";
    static constexpr const char *P_TITLE = "P_TITLE";
    static constexpr const char *P_GRADIENT = "P_GRADIENT";
    static constexpr const char *P_INTERPOLATION = "P_INTERPOLATION";

    QExtMvvmColorMapItem();

    void setDataItem(const QExtMvvmData2DItem* item);

    QExtMvvmData2DItem* dataItem() const;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_COLORMAPITEM_H
