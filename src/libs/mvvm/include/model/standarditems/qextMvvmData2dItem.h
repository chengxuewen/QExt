#ifndef _QEXTMVVMDATA2DITEM_H
#define _QEXTMVVMDATA2DITEM_H

#include <qextMvvmCompoundItem.h>
#include <vector>

namespace ModelView
{

class QEXTMvvmBinnedAxisItem;

//! Represents two-dimensional data (axes definition and 2d array of values).
//! Values are stored in QEXTMvvmData2DItem itself, axes are attached as children. Corresponding plot
//! properties will be served by QEXTMvvmColorMapItem.

class QEXT_MVVM_API QEXTMvvmData2DItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string T_XAXIS = "T_XAXIS";
    static inline const std::string T_YAXIS = "T_YAXIS";

    QEXTMvvmData2DItem();

    void setAxes(std::unique_ptr<QEXTMvvmBinnedAxisItem> x_axis, std::unique_ptr<QEXTMvvmBinnedAxisItem> y_axis);

    QEXTMvvmBinnedAxisItem* xAxis() const;

    QEXTMvvmBinnedAxisItem* yAxis() const;

    void setContent(const std::vector<double>& data);

    std::vector<double> content() const;

private:
    void insert_axis(std::unique_ptr<QEXTMvvmBinnedAxisItem> axis, const std::string& tag);
};

} // namespace ModelView

#endif // _QEXTMVVMDATA2DITEM_H
