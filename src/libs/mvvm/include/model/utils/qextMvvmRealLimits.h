#ifndef _QEXTMVVMUTILSREALLIMITS_H
#define _QEXTMVVMUTILSREALLIMITS_H

#include <qextMvvmGlobal.h>

namespace ModelView
{

//! Limits for double.
//! @ingroup fitting

class QEXT_MVVM_API QEXTMvvmRealLimits
{
public:
    QEXTMvvmRealLimits();

    //! Creates an object bounded from the left
    static QEXTMvvmRealLimits lowerLimited(double bound_value);

    //! Creates an object which can have only positive values (>0., zero is not included)
    static QEXTMvvmRealLimits positive();

    //! Creates an object which can have only positive values with 0. included
    static QEXTMvvmRealLimits nonnegative();

    //! Creates an object bounded from the right
    static QEXTMvvmRealLimits upperLimited(double bound_value);

    //! Creates an object bounded from the left and right
    static QEXTMvvmRealLimits limited(double left_bound_value, double right_bound_value);

    //! Creates an object withoud bounds (default)
    static QEXTMvvmRealLimits limitless();

    //! if has lower limit
    bool hasLowerLimit() const;

    //! Returns lower limit
    double lowerLimit() const;

    //! if has upper limit
    bool hasUpperLimit() const;

    //! Returns upper limit
    double upperLimit() const;

    //! if has lower and upper limit
    bool hasLowerAndUpperLimits() const;

    //! returns true if proposed value is in limits range
    bool isInRange(double value) const;

    bool operator==(const QEXTMvvmRealLimits& other) const;
    bool operator!=(const QEXTMvvmRealLimits& other) const;
    bool operator<(const QEXTMvvmRealLimits& other) const;

    bool isLimitless() const;
    bool isPositive() const;
    bool isNonnegative() const;
    bool isLowerLimited() const;
    bool isUpperLimited() const;
    bool isLimited() const;

protected:
    QEXTMvvmRealLimits(bool has_lower_limit, bool has_upper_limit, double lower_limit, double upper_limit);

    bool m_has_lower_limit; //! parameter has lower bound
    bool m_has_upper_limit; //! parameter has upper bound
    double m_lower_limit;   //! minimum allowed value
    double m_upper_limit;   //! maximum allowed value
};

} // namespace ModelView

#endif // _QEXTMVVMUTILSREALLIMITS_H
