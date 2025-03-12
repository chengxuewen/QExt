#ifndef _QEXTNUMERIC_H
#define _QEXTNUMERIC_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>

#include <QObject>

#include <limits>
#include <cmath>

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
            typedef typename QExtMakeSigned<T>::Type ST;
            supremum = -2.0 * std::numeric_limits<ST>::min();   // -2 * (-2^63) = 2^64, exact (for T = quint64)
            v = std::fabs(v);
        }

        *value = std::numeric_limits<T>::max();
        if (v >= supremum)
        {
            return false;
        }

        // Now we can convert, these two conversions cannot be UB
        *value = T(v);

        QEXT_WARNING_PUSH
        QEXT_WARNING_DISABLE_GCC("-Wfloat-equal")
        QEXT_WARNING_DISABLE_CLANG("-Wfloat-equal")
        return *value == v;
        QEXT_WARNING_POP
    }

    static bool isValueEqual(double val1, double val2)
    {
        return std::abs(val1 - val2) < std::numeric_limits<double>::epsilon();
    }

    /**
     * @brief Reduce floating-point accuracy.
     * @param value Double precision floating-point data variable
     * @param places Precision value
     * @code Floating-point numbers with reduced precision.
     *  reducePrecision(111111.111111, -6) // return 000000.000000
     *  reducePrecision(111111.111111, -5) // return 100000.000000
     *  reducePrecision(111111.111111, -4) // return 110000.000000
     *  reducePrecision(111111.111111, -3) // return 111000.000000
     *  reducePrecision(111111.111111, -2) // return 111100.000000
     *  reducePrecision(111111.111111, -1) // return 111110.000000
     *  reducePrecision(111111.111111, 0) // return 111111.000000
     *  reducePrecision(111111.111111, 1) // return 111111.100000
     *  reducePrecision(111111.111111, 2) // return 111111.110000
     *  reducePrecision(111111.111111, 3) // return 111111.111000
     *  reducePrecision(111111.111111, 4) // return 111111.111100
     *  reducePrecision(111111.111111, 5) // return 111111.111110
     *  reducePrecision(111111.111111, 6) // return 111111.111111
     * @endcode
     * @return
     */
    static double reducePrecision(double value, short places);

    static QString doubleFixedString(double value, int precision = 6);
};

#endif // _QEXTNUMERIC_H
