#ifndef _QEXTMVVMVIEWPORTITEM_H
#define _QEXTMVVMVIEWPORTITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

class QEXTMvvmViewportAxisItem;

//! Base class to represent 2D viewport.
//! Contains x,y axis, indended to display graphs or 2d colormaps.

class QEXT_MVVM_API QEXTMvvmViewportItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_XAXIS = "P_XAXIS";
    static inline const std::string P_YAXIS = "P_YAXIS";
    static inline const std::string T_ITEMS = "T_ITEMS";

    QEXTMvvmViewportItem(const QEXTMvvmModelType& model);

    QEXTMvvmViewportAxisItem* xAxis() const;

    QEXTMvvmViewportAxisItem* yAxis() const;

    virtual void setViewportToContent(double left, double top, double right, double bottom);

    virtual void setViewportToContent();

protected:
    void register_xy_axes();

protected:
    virtual std::pair<double, double> data_xaxis_range() const = 0;
    virtual std::pair<double, double> data_yaxis_range() const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWPORTITEM_H
