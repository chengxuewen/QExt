#ifndef _QEXTMVVMVIEWPORTITEM_H
#define _QEXTMVVMVIEWPORTITEM_H

#include <qextMvvmCompoundItem.h>

class QEXTMvvmViewportAxisItem;

//! Base class to represent 2D viewport.
//! Contains x,y axis, indended to display graphs or 2d colormaps.

class QEXT_MVVM_API QEXTMvvmViewportItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_XAXIS = "P_XAXIS";
    static inline const QString P_YAXIS = "P_YAXIS";
    static inline const QString T_ITEMS = "T_ITEMS";

    QEXTMvvmViewportItem(const QString& model);

    QEXTMvvmViewportAxisItem* xAxis() const;

    QEXTMvvmViewportAxisItem* yAxis() const;

    virtual void setViewportToContent(double left, double top, double right, double bottom);

    virtual void setViewportToContent();

protected:
    void register_xy_axes();

protected:
    virtual QPair<double, double> dataXAxisRange() const = 0;
    virtual QPair<double, double> dataYAxisRange() const = 0;
};

#endif // _QEXTMVVMVIEWPORTITEM_H
