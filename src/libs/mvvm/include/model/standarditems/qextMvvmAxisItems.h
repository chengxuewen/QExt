#ifndef _QEXTMVVMAXISITEMS_H
#define _QEXTMVVMAXISITEMS_H

//! @file axisitems.h
//! Collection of axis items for 1D and 2D data/plotting support.

#include <memory>
#include <qextMvvmCompoundItem.h>
#include <QVector>

//! Base class for all axes items. Has min, max defined, but nothing else.

class QEXT_MVVM_API QEXTMvvmBasicAxisItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_MIN = "P_MIN";
    static inline const QString P_MAX = "P_MAX";

    explicit QEXTMvvmBasicAxisItem(const QString& QString);

protected:
    void register_min_max();
};

//! Item to represent viewport axis.
//! Serves as a counterpart of QCPAxis from QCustomPlot. Intended to cary title, fonts etc.

class QEXT_MVVM_API QEXTMvvmViewportAxisItem : public QEXTMvvmBasicAxisItem
{
public:
    static inline const QString P_TITLE = "P_TITLE";
    static inline const QString P_IS_LOG = "P_IS_LOG";
    explicit QEXTMvvmViewportAxisItem(const QString& QString = QEXTMvvmConstants::ViewportAxisItemType);

    QPair<double, double> range() const;

    void set_range(double lower, double upper);

    bool is_in_log() const;
};

//! Item to represent an axis with arbitrary binning.
//! Base class to define an axis with specific binning (fixed, variable). Used in QEXTMvvmData1DItem and
//! Data2Ditem to store 1d and 2d data.  Doesn't carry any appearance info (e.g. axis title, label
//! size, etc) and thus not intended for direct plotting.

class QEXT_MVVM_API QEXTMvvmBinnedAxisItem : public QEXTMvvmBasicAxisItem
{
public:
    explicit QEXTMvvmBinnedAxisItem(const QString& QString);

    virtual QPair<double, double> range() const = 0;

    virtual int size() const = 0;

    virtual QVector<double> binCenters() const = 0;
};

//! Item to represent fixed bin axis.
//! Defines an axis with equidistant binning.

class QEXT_MVVM_API QEXTMvvmFixedBinAxisItem : public QEXTMvvmBinnedAxisItem
{
public:
    static inline const QString P_NBINS = "P_NBINS";
    QEXTMvvmFixedBinAxisItem(const QString& QString = QEXTMvvmConstants::FixedBinAxisItemType);

    void setParameters(int nbins, double xmin, double xmax);

    static QEXTMvvmFixedBinAxisItem *create(int nbins, double xmin, double xmax);

    QPair<double, double> range() const QEXT_DECL_OVERRIDE;

    int size() const QEXT_DECL_OVERRIDE;

    QVector<double> binCenters() const QEXT_DECL_OVERRIDE;
};

//! Item to represent pointwise axis.
//! Defines an axis via array of points representing point coordinates.

class QEXT_MVVM_API QEXTMvvmPointwiseAxisItem : public QEXTMvvmBinnedAxisItem
{
public:
    QEXTMvvmPointwiseAxisItem(const QString& QString = QEXTMvvmConstants::PointwiseAxisItemType);

    void setParameters(const QVector<double>& data);

    static QEXTMvvmPointwiseAxisItem *create(const QVector<double>& data);

    QPair<double, double> range() const QEXT_DECL_OVERRIDE;

    int size() const QEXT_DECL_OVERRIDE;

    QVector<double> binCenters() const QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMAXISITEMS_H
