#ifndef _QEXTLIMITS_H
#define _QEXTLIMITS_H

#include <qextGlobal.h>

#include <limits>

#define QEXT_INT_MIN std::numeric_limits<int>::min()
#define QEXT_INT_MAX std::numeric_limits<int>::max()

#define QEXT_FLOAT_MIN std::numeric_limits<double>::min()
#define QEXT_FLOAT_MAX std::numeric_limits<double>::max()
#define QEXT_FLOAT_NAN std::numeric_limits<float>::quiet_NaN()

#define QEXT_DOUBLE_MIN std::numeric_limits<double>::min()
#define QEXT_DOUBLE_MAX std::numeric_limits<double>::max()
#define QEXT_DOUBLE_NAN std::numeric_limits<double>::quiet_NaN()

#define QEXT_IS_NAN(x) std::isnan(x)

#endif // _QEXTLIMITS_H
