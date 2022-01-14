#ifndef _QEXTMVVMSTANDARDITEMSCOLORMAPVIEWPORTITEM_H
#define _QEXTMVVMSTANDARDITEMSCOLORMAPVIEWPORTITEM_H

#include <qextMvvmViewPortItem.h>

namespace ModelView
{

class QEXTMvvmData2DItem;

//! Container with viewport and collection of ColorMapItem's to plot.

class QEXT_MVVM_API QEXTMvvmColorMapViewportItem : public QEXTMvvmViewportItem
{
public:
    static inline const std::string P_ZAXIS = "P_ZAXIS";

    QEXTMvvmColorMapViewportItem();

    QEXTMvvmViewportAxisItem* zAxis() const;

    void setViewportToContent() override;

protected:
    virtual std::pair<double, double> data_xaxis_range() const override;
    virtual std::pair<double, double> data_yaxis_range() const override;

private:
    QEXTMvvmData2DItem* data_item() const;
    void update_data_range();
};

} // namespace ModelView

#endif // _QEXTMVVMSTANDARDITEMSCOLORMAPVIEWPORTITEM_H
