#ifndef _QEXTMVVMUTILSNUMERICUTILS_H
#define _QEXTMVVMUTILSNUMERICUTILS_H

#include <qextMvvmGlobal.h>

namespace ModelView
{

namespace QEXTMvvmUtils
{

//! Returns true if two doubles agree within epsilon*tolerance.
QEXT_MVVM_API bool AreAlmostEqual(double a, double b, double tolerance_factor = 1.0);

//! Produces random integer values uniformly distributed on the closed interval [low, high].
QEXT_MVVM_API int RandInt(int low, int high);

//! Produces random FLOAT values uniformly distributed on the  interval [low, high).
QEXT_MVVM_API double RandDouble(double low, double high);

} // namespace Utils

} // namespace ModelView

#endif // _QEXTMVVMUTILSNUMERICUTILS_H
