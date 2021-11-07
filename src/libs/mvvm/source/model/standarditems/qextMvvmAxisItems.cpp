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



QEXTMvvmBasicAxisItem::QEXTMvvmBasicAxisItem(const QString &QString) : QEXTMvvmCompoundItem(QString) {}

void QEXTMvvmBasicAxisItem::register_min_max()
{
    addProperty(P_MIN, default_axis_min)->setDisplayName("Min")->setLimits(QEXTMvvmRealLimits::limitless());
    addProperty(P_MAX, default_axis_max)->setDisplayName("Max")->setLimits(QEXTMvvmRealLimits::limitless());
}

// --- QEXTMvvmViewportAxisItem ------------------------------------------------------

QEXTMvvmViewportAxisItem::QEXTMvvmViewportAxisItem(const QString &QString) : QEXTMvvmBasicAxisItem(QString)
{
    addProperty<QEXTMvvmTextItem>(P_TITLE)->setDisplayName("Title");
    register_min_max();
    addProperty(P_IS_LOG, false)->setDisplayName("log10");
}

//! Returns pair of lower, upper axis range.

QPair<double, double> QEXTMvvmViewportAxisItem::range() const
{
    return QPair<double, double>(property<double>(P_MIN), property<double>(P_MAX));
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

// --- QEXTMvvmBinnedAxisItem ------------------------------------------------------

QEXTMvvmBinnedAxisItem::QEXTMvvmBinnedAxisItem(const QString &QString) : QEXTMvvmBasicAxisItem(QString) {}

// --- QEXTMvvmFixedBinAxisItem ------------------------------------------------------

QEXTMvvmFixedBinAxisItem::QEXTMvvmFixedBinAxisItem(const QString &QString) : QEXTMvvmBinnedAxisItem(QString)
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

QEXTMvvmFixedBinAxisItem *QEXTMvvmFixedBinAxisItem::create(int nbins, double xmin, double xmax)
{
    QEXTMvvmFixedBinAxisItem *result = new QEXTMvvmFixedBinAxisItem;
    result->setParameters(nbins, xmin, xmax);
    return result;
}

QPair<double, double> QEXTMvvmFixedBinAxisItem::range() const
{
    return QPair<double, double>(property<double>(P_MIN), property<double>(P_MAX));
}

int QEXTMvvmFixedBinAxisItem::size() const
{
    return property<int>(P_NBINS);
}

QVector<double> QEXTMvvmFixedBinAxisItem::binCenters() const
{
    QVector<double> result;
    int nbins = property<int>(P_NBINS);
    double start = property<double>(P_MIN);
    double end = property<double>(P_MAX);
    double step = (end - start) / nbins;

    result.resize(nbins);
    result.fill(0.0);
    for (size_t i = 0; i < static_cast<size_t>(nbins); ++i)
    {
        result[i] = start + step * (i + 0.5);
    }

    return result;
}

// --- QEXTMvvmPointwiseAxisItem ------------------------------------------------------

QEXTMvvmPointwiseAxisItem::QEXTMvvmPointwiseAxisItem(const QString &QString) : QEXTMvvmBinnedAxisItem(QString)
{
    // vector of points matching default xmin, xmax
    setData(QVector<double> {default_axis_min, default_axis_max});
    setEditable(false); // prevent editing in widgets, since there is no corresponding editor
}

void QEXTMvvmPointwiseAxisItem::setParameters(const QVector<double> &data)
{
    setData(data);
}

QEXTMvvmPointwiseAxisItem *QEXTMvvmPointwiseAxisItem::create(const QVector<double> &data)
{
    QEXTMvvmPointwiseAxisItem *result = new QEXTMvvmPointwiseAxisItem;
    result->setParameters(data);
    return result;
}

QPair<double, double> QEXTMvvmPointwiseAxisItem::range() const
{
    auto data = binCenters();
    return this->binCenters().empty() ? QPair<double, double>(default_axis_min, default_axis_max)
                                      : QPair<double, double>(data.front(), data.back());
}

int QEXTMvvmPointwiseAxisItem::size() const
{
    return binCenters().size();
}

QVector<double> QEXTMvvmPointwiseAxisItem::binCenters() const
{
    return data<QVector<double>>();
}
