#ifndef _QEXTMVVMSTANDARDITEMSCOLORMAPITEM_H
#define _QEXTMVVMSTANDARDITEMSCOLORMAPITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

class QEXTMvvmData2DItem;

//! Two-dimensional color map representation of Data2DItem.
//! Contains plot properties (i.e. color, gradient etc) and link to Data2DItem, which will provide
//! actual data to plot. ColorMapItem is intended for plotting only via ColorMapViewportItem.

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

#endif // _QEXTMVVMSTANDARDITEMSCOLORMAPITEM_H
