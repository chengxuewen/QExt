#ifndef _QEXTMVVMCOLORMAPVIEWPORTITEM_H
#define _QEXTMVVMCOLORMAPVIEWPORTITEM_H

#include <qextMvvmViewPortItem.h>

class QEXTMvvmData2DItem;

//! Container with viewport and collection of QEXTMvvmColorMapItem's to plot.

class QEXT_MVVM_API QEXTMvvmColorMapViewportItem : public QEXTMvvmViewportItem
{
public:
    static inline const QString P_ZAXIS = "P_ZAXIS";

    QEXTMvvmColorMapViewportItem();

    QEXTMvvmViewportAxisItem* zAxis() const;

    void setViewportToContent() QEXT_DECL_OVERRIDE;

protected:
    virtual QPair<double, double> dataXAxisRange() const QEXT_DECL_OVERRIDE;
    virtual QPair<double, double> dataYAxisRange() const QEXT_DECL_OVERRIDE;

private:
    QEXTMvvmData2DItem* data_item() const;
    void update_data_range();
};

#endif // _QEXTMVVMCOLORMAPVIEWPORTITEM_H
