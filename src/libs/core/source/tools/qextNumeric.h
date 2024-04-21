#ifndef _QEXTNUMERIC_H
#define _QEXTNUMERIC_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>

#include <QObject>

#include <limits>

class QEXT_CORE_API QExtNumeric
{
public:
    QExtNumeric();

    /**
     * Returns true if the double @a v can be converted to type @c T, false if it's out of range.
     * If the conversion is successful, the converted value is stored in @a value; if it was not successful,
     * @a value will contain the minimum or maximum of T, depending on the sign of @a d.
     * If @c T is unsigned, then @a value contains the absolute value of @a v.
     *
     * This function works for v containing infinities, but not NaN.
     * It's the caller's responsibility to exclude that possibility before calling it.
     */
    template <typename T>
    static inline bool convertDoubleTo(double v, T *value)
    {
        Q_STATIC_ASSERT(QExtIsIntegral<T>::value);

        // The [conv.fpint] (7.10 Floating-integral conversions) section of the C++
        // standard says only exact conversions are guaranteed. Converting
        // integrals to floating-point with loss of precision has implementation-
        // defined behavior whether the next higher or next lower is returned;
        // converting FP to integral is UB if it can't be represented.
        //
        // That means we can't write UINT64_MAX+1. Writing ldexp(1, 64) would be
        // correct, but Clang, ICC and MSVC don't realize that it's a constant and
        // the math call stays in the compiled code.

        double supremum;
        if (QExtIsSigned<T>::value)
        {
            supremum = -1.0 * std::numeric_limits<T>::min();    // -1 * (-2^63) = 2^63, exact (for T = qint64)
            *value = std::numeric_limits<T>::min();
            if (v < std::numeric_limits<T>::min())
            {
                return false;
            }
        }
        else
        {
            using ST = typename QExtMakeSigned<T>::Type;
            supremum = -2.0 * std::numeric_limits<ST>::min();   // -2 * (-2^63) = 2^64, exact (for T = quint64)
            v = fabs(v);
        }

        *value = std::numeric_limits<T>::max();
        if (v >= supremum)
        {
            return false;
        }

        // Now we can convert, these two conversions cannot be UB
        *value = T(v);

        QT_WARNING_PUSH
        QT_WARNING_DISABLE_GCC("-Wfloat-equal")
        QT_WARNING_DISABLE_CLANG("-Wfloat-equal")
        return *value == v;
        QT_WARNING_POP
    }
};

#endif // _QEXTNUMERIC_H
