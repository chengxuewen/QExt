#ifndef _QEXTMVVMJSONUTILS_H
#define _QEXTMVVMJSONUTILS_H

#include <qextMvvmGlobal.h>
#include <string>

class QEXTMvvmModel;
class QEXTMvvmRealLimits;

namespace JsonUtils
{

//! Returns multiline string representing model content as json.
QEXT_MVVM_API QString ModelToJsonString(const QEXTMvvmModel& model);

//! Returns string representation of QEXTMvvmRealLimits.
QEXT_MVVM_API QString ToString(const QEXTMvvmRealLimits& limits);

QEXT_MVVM_API QEXTMvvmRealLimits CreateLimits(const QString& text, double min = 0.0,
                                          double max = 0.0);

} // namespace JsonUtils

#endif // _QEXTMVVMJSONUTILS_H
