// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmRealLimits.h>
#include <limits>

namespace {
const double lmin = std::numeric_limits<double>::lowest();
const double lmax = std::numeric_limits<double>::max();
const double poszero = std::numeric_limits<double>::min();
} // namespace

using namespace ModelView;

QExtMvvmRealLimits::QExtMvvmRealLimits()
    : m_has_lower_limit(false), m_has_upper_limit(false), m_lower_limit(lmin), m_upper_limit(lmax)
{
}

QExtMvvmRealLimits::QExtMvvmRealLimits(bool has_lower_limit, bool has_upper_limit, double lower_limit,
                       double upper_limit)
    : m_has_lower_limit(has_lower_limit)
    , m_has_upper_limit(has_upper_limit)
    , m_lower_limit(lower_limit)
    , m_upper_limit(upper_limit)
{
}

QExtMvvmRealLimits QExtMvvmRealLimits::lowerLimited(double bound_value)
{
    return QExtMvvmRealLimits(true, false, bound_value, lmax);
}

QExtMvvmRealLimits QExtMvvmRealLimits::positive()
{
    return lowerLimited(poszero);
}

QExtMvvmRealLimits QExtMvvmRealLimits::nonnegative()
{
    return lowerLimited(0.);
}

QExtMvvmRealLimits QExtMvvmRealLimits::upperLimited(double bound_value)
{
    return QExtMvvmRealLimits(false, true, lmin, bound_value);
}

QExtMvvmRealLimits QExtMvvmRealLimits::limited(double left_bound_value, double right_bound_value)
{
    return QExtMvvmRealLimits(true, true, left_bound_value, right_bound_value);
}

QExtMvvmRealLimits QExtMvvmRealLimits::limitless()
{
    return QExtMvvmRealLimits();
}

bool QExtMvvmRealLimits::hasLowerLimit() const
{
    return m_has_lower_limit;
}

double QExtMvvmRealLimits::lowerLimit() const
{
    return m_lower_limit;
}

bool QExtMvvmRealLimits::hasUpperLimit() const
{
    return m_has_upper_limit;
}

double QExtMvvmRealLimits::upperLimit() const
{
    return m_upper_limit;
}

bool QExtMvvmRealLimits::hasLowerAndUpperLimits() const
{
    return (m_has_lower_limit && m_has_upper_limit);
}

bool QExtMvvmRealLimits::isInRange(double value) const
{
    if (hasLowerLimit() && value < m_lower_limit)
        return false;
    if (hasUpperLimit() && value >= m_upper_limit)
        return false;
    return true;
}

bool QExtMvvmRealLimits::operator==(const QExtMvvmRealLimits& other) const
{
    // Intenional 'unsafe' double comparison to have QExtMvvmRealLimits::positive and
    // QExtMvvmRealLimits::nonnegative different.
    // FIXME Is there better solution? Can we drop either positive or non-negative?
    return (m_has_lower_limit == other.m_has_lower_limit)
           && (m_has_upper_limit == other.m_has_upper_limit) && m_lower_limit == other.m_lower_limit
           && m_upper_limit == other.m_upper_limit;
}

bool QExtMvvmRealLimits::operator!=(const QExtMvvmRealLimits& other) const
{
    return !(*this == other);
}

bool QExtMvvmRealLimits::operator<(const QExtMvvmRealLimits& other) const
{
    return m_lower_limit < other.m_lower_limit && m_upper_limit < other.m_upper_limit;
}

bool QExtMvvmRealLimits::isLimitless() const
{
    return !hasLowerLimit() && !hasUpperLimit();
}

bool QExtMvvmRealLimits::isPositive() const
{
    // intenional 'unsafe' double comparison
    return hasLowerLimit() && !hasUpperLimit() && lowerLimit() == poszero;
}

bool QExtMvvmRealLimits::isNonnegative() const
{
    return hasLowerLimit() && !hasUpperLimit() && lowerLimit() == 0.0;
}

bool QExtMvvmRealLimits::isLowerLimited() const
{
    return !isPositive() && !isNonnegative() && hasLowerLimit() && !hasUpperLimit();
}

bool QExtMvvmRealLimits::isUpperLimited() const
{
    return !hasLowerLimit() && hasUpperLimit();
}

bool QExtMvvmRealLimits::isLimited() const
{
    return hasLowerLimit() && hasUpperLimit();
}
