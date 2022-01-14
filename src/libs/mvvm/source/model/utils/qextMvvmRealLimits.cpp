// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <limits>
#include <qextMvvmNumericUtils.h>
#include <qextMvvmRealLimits.h>

namespace
{
const double lmin = std::numeric_limits<double>::lowest();
const double lmax = std::numeric_limits<double>::max();
const double poszero = std::numeric_limits<double>::min();
} // namespace

using namespace ModelView;

QEXTMvvmRealLimits::QEXTMvvmRealLimits()
    : m_has_lower_limit(false), m_has_upper_limit(false), m_lower_limit(lmin), m_upper_limit(lmax)
{
}

QEXTMvvmRealLimits::QEXTMvvmRealLimits(bool has_lower_limit, bool has_upper_limit, double lower_limit,
                       double upper_limit)
    : m_has_lower_limit(has_lower_limit)
    , m_has_upper_limit(has_upper_limit)
    , m_lower_limit(lower_limit)
    , m_upper_limit(upper_limit)
{
}

QEXTMvvmRealLimits QEXTMvvmRealLimits::lowerLimited(double bound_value)
{
    return QEXTMvvmRealLimits(true, false, bound_value, lmax);
}

QEXTMvvmRealLimits QEXTMvvmRealLimits::positive()
{
    return lowerLimited(poszero);
}

QEXTMvvmRealLimits QEXTMvvmRealLimits::nonnegative()
{
    return lowerLimited(0.);
}

QEXTMvvmRealLimits QEXTMvvmRealLimits::upperLimited(double bound_value)
{
    return QEXTMvvmRealLimits(false, true, lmin, bound_value);
}

QEXTMvvmRealLimits QEXTMvvmRealLimits::limited(double left_bound_value, double right_bound_value)
{
    return QEXTMvvmRealLimits(true, true, left_bound_value, right_bound_value);
}

QEXTMvvmRealLimits QEXTMvvmRealLimits::limitless()
{
    return QEXTMvvmRealLimits();
}

bool QEXTMvvmRealLimits::hasLowerLimit() const
{
    return m_has_lower_limit;
}

double QEXTMvvmRealLimits::lowerLimit() const
{
    return m_lower_limit;
}

bool QEXTMvvmRealLimits::hasUpperLimit() const
{
    return m_has_upper_limit;
}

double QEXTMvvmRealLimits::upperLimit() const
{
    return m_upper_limit;
}

bool QEXTMvvmRealLimits::hasLowerAndUpperLimits() const
{
    return (m_has_lower_limit && m_has_upper_limit);
}

bool QEXTMvvmRealLimits::isInRange(double value) const
{
    if (hasLowerLimit() && value < m_lower_limit)
        return false;
    if (hasUpperLimit() && value >= m_upper_limit)
        return false;
    return true;
}

bool QEXTMvvmRealLimits::operator==(const QEXTMvvmRealLimits& other) const
{
    // Intenional 'unsafe' double comparison to have RealLimits::positive and
    // RealLimits::nonnegative different.
    // FIXME Is there better solution? Can we drop either positive or non-negative?
    return (m_has_lower_limit == other.m_has_lower_limit)
           && (m_has_upper_limit == other.m_has_upper_limit) && m_lower_limit == other.m_lower_limit
           && m_upper_limit == other.m_upper_limit;
}

bool QEXTMvvmRealLimits::operator!=(const QEXTMvvmRealLimits& other) const
{
    return !(*this == other);
}

bool QEXTMvvmRealLimits::operator<(const QEXTMvvmRealLimits& other) const
{
    return m_lower_limit < other.m_lower_limit && m_upper_limit < other.m_upper_limit;
}

bool QEXTMvvmRealLimits::isLimitless() const
{
    return !hasLowerLimit() && !hasUpperLimit();
}

bool QEXTMvvmRealLimits::isPositive() const
{
    // intenional 'unsafe' double comparison
    return hasLowerLimit() && !hasUpperLimit() && lowerLimit() == poszero;
}

bool QEXTMvvmRealLimits::isNonnegative() const
{
    return hasLowerLimit() && !hasUpperLimit() && lowerLimit() == 0.0;
}

bool QEXTMvvmRealLimits::isLowerLimited() const
{
    return !isPositive() && !isNonnegative() && hasLowerLimit() && !hasUpperLimit();
}

bool QEXTMvvmRealLimits::isUpperLimited() const
{
    return !hasLowerLimit() && hasUpperLimit();
}

bool QEXTMvvmRealLimits::isLimited() const
{
    return hasLowerLimit() && hasUpperLimit();
}
