#ifndef _QEXTMVVMSTANDARDITEMSAXISITEMS_H
#define _QEXTMVVMSTANDARDITEMSAXISITEMS_H

//! @file axisitems.h
//! Collection of axis items for 1D and 2D data/plotting support.

#include <qextMvvmCompoundItem.h>

#include <memory>
#include <vector>

namespace ModelView
{

//! Base class for all axes items. Has min, max defined, but nothing else.

class QEXT_MVVM_API QEXTMvvmBasicAxisItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_MIN = "P_MIN";
    static inline const std::string P_MAX = "P_MAX";

    explicit QEXTMvvmBasicAxisItem(const std::string& model_type);

protected:
    void register_min_max();
};

//! Item to represent viewport axis.
//! Serves as a counterpart of QCPAxis from QCustomPlot. Intended to cary title, fonts etc.

class QEXT_MVVM_API QEXTMvvmViewportAxisItem : public QEXTMvvmBasicAxisItem
{
public:
    static inline const std::string P_TITLE = "P_TITLE";
    static inline const std::string P_IS_LOG = "P_IS_LOG";
    explicit QEXTMvvmViewportAxisItem(const std::string& model_type = QEXTMvvmConstants::ViewportAxisItemType);

    std::pair<double, double> range() const;

    void set_range(double lower, double upper);

    bool is_in_log() const;
};

//! Item to represent an axis with arbitrary binning.
//! Base class to define an axis with specific binning (fixed, variable). Used in Data1DItem and
//! Data2Ditem to store 1d and 2d data.  Doesn't carry any appearance info (e.g. axis title, label
//! size, etc) and thus not intended for direct plotting.

class QEXT_MVVM_API QEXTMvvmBinnedAxisItem : public QEXTMvvmBasicAxisItem
{
public:
    explicit QEXTMvvmBinnedAxisItem(const std::string& model_type);

    virtual std::pair<double, double> range() const = 0;

    virtual int size() const = 0;

    virtual std::vector<double> binCenters() const = 0;
};

//! Item to represent fixed bin axis.
//! Defines an axis with equidistant binning.

class QEXT_MVVM_API QEXTMvvmFixedBinAxisItem : public QEXTMvvmBinnedAxisItem
{
public:
    static inline const std::string P_NBINS = "P_NBINS";
    QEXTMvvmFixedBinAxisItem(const std::string& model_type = QEXTMvvmConstants::FixedBinAxisItemType);

    void setParameters(int nbins, double xmin, double xmax);

    static std::unique_ptr<QEXTMvvmFixedBinAxisItem> create(int nbins, double xmin, double xmax);

    std::pair<double, double> range() const override;

    int size() const override;

    std::vector<double> binCenters() const override;
};

//! Item to represent pointwise axis.
//! Defines an axis via array of points representing point coordinates.

class QEXT_MVVM_API QEXTMvvmPointwiseAxisItem : public QEXTMvvmBinnedAxisItem
{
public:
    QEXTMvvmPointwiseAxisItem(const std::string& model_type = QEXTMvvmConstants::PointwiseAxisItemType);

    void setParameters(const std::vector<double>& data);

    static std::unique_ptr<QEXTMvvmPointwiseAxisItem> create(const std::vector<double>& data);

    std::pair<double, double> range() const override;

    int size() const override;

    std::vector<double> binCenters() const override;
};

} // namespace ModelView

#endif // _QEXTMVVMSTANDARDITEMSAXISITEMS_H
