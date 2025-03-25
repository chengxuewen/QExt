// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_AXISITEMS_H
#define MVVM_STANDARDITEMS_AXISITEMS_H

//! @file axisitems.h
//! Collection of axis items for 1D and 2D data/plotting support.

#include <qextMvvmCompoundItem.h>

#include <vector>

namespace ModelView {

//! Base class for all axes items. Has min, max defined, but nothing else.

class QEXT_MVVM_API QExtMvvmBasicAxisItem : public QExtMvvmCompoundItem {
public:
    static constexpr const char *P_MIN = "P_MIN";
    static constexpr const char *P_MAX = "P_MAX";

    explicit QExtMvvmBasicAxisItem(const std::string& QExtMvvmModelType);

protected:
    void register_min_max();
};

//! Item to represent viewport axis.
//! Serves as a counterpart of QCPAxis from QCustomPlot. Intended to cary title, fonts etc.

class QEXT_MVVM_API QExtMvvmViewportAxisItem : public QExtMvvmBasicAxisItem {
public:
    static constexpr const char *P_TITLE = "P_TITLE";
    static constexpr const char *P_IS_LOG = "P_IS_LOG";
    explicit QExtMvvmViewportAxisItem(const std::string& QExtMvvmModelType = Constants::ViewportAxisItemType);

    std::pair<double, double> range() const;

    void set_range(double lower, double upper);

    bool is_in_log() const;
};

//! Item to represent an axis with arbitrary binning.
//! Base class to define an axis with specific binning (fixed, variable). Used in QExtMvvmData1DItem and
//! Data2Ditem to store 1d and 2d data.  Doesn't carry any appearance info (e.g. axis title, label
//! size, etc) and thus not intended for direct plotting.

class QEXT_MVVM_API QExtMvvmBinnedAxisItem : public QExtMvvmBasicAxisItem {
public:
    explicit QExtMvvmBinnedAxisItem(const std::string& QExtMvvmModelType);

    virtual std::pair<double, double> range() const = 0;

    virtual int size() const = 0;

    virtual std::vector<double> binCenters() const = 0;
};

//! Item to represent fixed bin axis.
//! Defines an axis with equidistant binning.

class QEXT_MVVM_API QExtMvvmFixedBinAxisItem : public QExtMvvmBinnedAxisItem {
public:
    static constexpr const char *P_NBINS = "P_NBINS";
    explicit QExtMvvmFixedBinAxisItem(const std::string& QExtMvvmModelType = Constants::FixedBinAxisItemType);

    void setParameters(int nbins, double xmin, double xmax);

    static QExtUniquePointer<QExtMvvmFixedBinAxisItem> create(int nbins, double xmin, double xmax);

    std::pair<double, double> range() const override;

    int size() const override;

    std::vector<double> binCenters() const override;
};

//! Item to represent pointwise axis.
//! Defines an axis via array of points representing point coordinates.

class QEXT_MVVM_API QExtMvvmPointwiseAxisItem : public QExtMvvmBinnedAxisItem {
public:
    explicit QExtMvvmPointwiseAxisItem(const std::string& QExtMvvmModelType = Constants::PointwiseAxisItemType);

    void setParameters(const std::vector<double>& data);

    static QExtUniquePointer<QExtMvvmPointwiseAxisItem> create(const std::vector<double>& data);

    std::pair<double, double> range() const override;

    int size() const override;

    std::vector<double> binCenters() const override;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_AXISITEMS_H
