// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmAxisItems.h>
#include <qextMvvmPlotTableItems.h>

namespace
{
const double default_axis_min = 0.0;
const double default_axis_max = 1.0;
} // namespace

using namespace ModelView;

QEXTMvvmBasicAxisItem::QEXTMvvmBasicAxisItem(const std::string& model_type) : QEXTMvvmCompoundItem(model_type) {}

void QEXTMvvmBasicAxisItem::register_min_max()
{
    addProperty(P_MIN, default_axis_min)->setDisplayName("Min")->setLimits(QEXTMvvmRealLimits::limitless());
    addProperty(P_MAX, default_axis_max)->setDisplayName("Max")->setLimits(QEXTMvvmRealLimits::limitless());
}

// --- ViewportAxisItem ------------------------------------------------------

QEXTMvvmViewportAxisItem::QEXTMvvmViewportAxisItem(const std::string& model_type) : QEXTMvvmBasicAxisItem(model_type)
{
    addProperty<QEXTMvvmTextItem>(P_TITLE)->setDisplayName("Title");
    register_min_max();
    addProperty(P_IS_LOG, false)->setDisplayName("log10");
}

//! Returns pair of lower, upper axis range.

std::pair<double, double> QEXTMvvmViewportAxisItem::range() const
{
    return std::make_pair(property<double>(P_MIN), property<double>(P_MAX));
}

//! Sets lower, upper range of axis to given values.

void QEXTMvvmViewportAxisItem::set_range(double lower, double upper)
{
    setProperty(P_MIN, lower);
    setProperty(P_MAX, upper);
}

bool QEXTMvvmViewportAxisItem::is_in_log() const
{
    return property<bool>(P_IS_LOG);
}

// --- BinnedAxisItem ------------------------------------------------------

QEXTMvvmBinnedAxisItem::QEXTMvvmBinnedAxisItem(const std::string& model_type) : QEXTMvvmBasicAxisItem(model_type) {}

// --- FixedBinAxisItem ------------------------------------------------------

QEXTMvvmFixedBinAxisItem::QEXTMvvmFixedBinAxisItem(const std::string& model_type) : QEXTMvvmBinnedAxisItem(model_type)
{
    addProperty(P_NBINS, 1)->setDisplayName("Nbins");
    register_min_max();
}

void QEXTMvvmFixedBinAxisItem::setParameters(int nbins, double xmin, double xmax)
{
    setProperty(P_NBINS, nbins);
    setProperty(P_MIN, xmin);
    setProperty(P_MAX, xmax);
}

std::unique_ptr<QEXTMvvmFixedBinAxisItem> QEXTMvvmFixedBinAxisItem::create(int nbins, double xmin, double xmax)
{
    auto result = make_unique<QEXTMvvmFixedBinAxisItem>();
    result->setParameters(nbins, xmin, xmax);
    return result;
}

std::pair<double, double> QEXTMvvmFixedBinAxisItem::range() const
{
    return std::make_pair(property<double>(P_MIN), property<double>(P_MAX));
}

int QEXTMvvmFixedBinAxisItem::size() const
{
    return property<int>(P_NBINS);
}

std::vector<double> QEXTMvvmFixedBinAxisItem::binCenters() const
{
    std::vector<double> result;
    int nbins = property<int>(P_NBINS);
    double start = property<double>(P_MIN);
    double end = property<double>(P_MAX);
    double step = (end - start) / nbins;

    result.resize(static_cast<size_t>(nbins), 0.0);
    for (size_t i = 0; i < static_cast<size_t>(nbins); ++i)
        result[i] = start + step * (i + 0.5);

    return result;
}

// --- PointwiseAxisItem ------------------------------------------------------

QEXTMvvmPointwiseAxisItem::QEXTMvvmPointwiseAxisItem(const std::string& model_type) : QEXTMvvmBinnedAxisItem(model_type)
{
    // vector of points matching default xmin, xmax
    setData(std::vector<double>{default_axis_min, default_axis_max});
    setEditable(false); // prevent editing in widgets, since there is no corresponding editor
}

void QEXTMvvmPointwiseAxisItem::setParameters(const std::vector<double>& data)
{
    setData(data);
}

std::unique_ptr<QEXTMvvmPointwiseAxisItem> QEXTMvvmPointwiseAxisItem::create(const std::vector<double>& data)
{
    auto result = make_unique<QEXTMvvmPointwiseAxisItem>();
    result->setParameters(data);
    return result;
}

std::pair<double, double> QEXTMvvmPointwiseAxisItem::range() const
{
    auto data = binCenters();
    return binCenters().empty() ? std::make_pair(default_axis_min, default_axis_max)
                                : std::make_pair(data.front(), data.back());
}

int QEXTMvvmPointwiseAxisItem::size() const
{
    return binCenters().size();
}

std::vector<double> QEXTMvvmPointwiseAxisItem::binCenters() const
{
    return data<std::vector<double>>();
}
