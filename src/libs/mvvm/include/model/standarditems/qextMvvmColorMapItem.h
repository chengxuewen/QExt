#ifndef _QEXTMVVMCOLORMAPITEM_H
#define _QEXTMVVMCOLORMAPITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

class QEXTMvvmData2DItem;

//! Two-dimensional color map representation of QEXTMvvmData2DItem.
//! Contains plot properties (i.e. color, gradient etc) and link to QEXTMvvmData2DItem, which will provide
//! actual data to plot. QEXTMvvmColorMapItem is intended for plotting only via QEXTMvvmColorMapViewportItem.

class QEXT_MVVM_API QEXTMvvmColorMapItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_LINK = "P_LINK";
    static inline const std::string P_TITLE = "P_TITLE";
    static inline const std::string P_GRADIENT = "P_GRADIENT";
    static inline const std::string P_INTERPOLATION = "P_INTERPOLATION";

    QEXTMvvmColorMapItem();

    void setDataItem(const QEXTMvvmData2DItem* item);

    QEXTMvvmData2DItem* dataItem() const;
};

} // namespace ModelView

#endif // _QEXTMVVMCOLORMAPITEM_H
