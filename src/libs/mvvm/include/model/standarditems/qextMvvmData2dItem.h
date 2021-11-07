#ifndef _QEXTMVVMDATA2DITEM_H
#define _QEXTMVVMDATA2DITEM_H

#include <qextMvvmCompoundItem.h>

#include <QVector>

class QEXTMvvmBinnedAxisItem;

//! Represents two-dimensional data (axes definition and 2d array of values).
//! Values are stored in QEXTMvvmData2DItem itself, axes are attached as children. Corresponding plot
//! properties will be served by QEXTMvvmColorMapItem.

class QEXT_MVVM_API QEXTMvvmData2DItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString T_XAXIS = "T_XAXIS";
    static inline const QString T_YAXIS = "T_YAXIS";

    QEXTMvvmData2DItem();

    void setAxes(QEXTMvvmBinnedAxisItem *xAxis, QEXTMvvmBinnedAxisItem *yAxis);

    QEXTMvvmBinnedAxisItem *xAxis() const;

    QEXTMvvmBinnedAxisItem *yAxis() const;

    void setContent(const QVector<double> &data);

    QVector<double> content() const;

private:
    void insertAxis(QEXTMvvmBinnedAxisItem *axis, const QString &tag);
};

#endif // _QEXTMVVMDATA2DITEM_H
