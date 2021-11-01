#ifndef _QEXTMVVMJSONUTILS_H
#define _QEXTMVVMJSONUTILS_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmRealLimits;

namespace JsonUtils
{

//! Returns multiline string representing model content as json.
QEXT_MVVM_API std::string ModelToJsonString(const QEXTMvvmSessionModel& model);

//! Returns string representation of QEXTMvvmRealLimits.
QEXT_MVVM_API std::string ToString(const QEXTMvvmRealLimits& limits);

QEXT_MVVM_API QEXTMvvmRealLimits CreateLimits(const std::string& text, double min = 0.0,
                                          double max = 0.0);

} // namespace JsonUtils

} // namespace ModelView

#endif // _QEXTMVVMJSONUTILS_H
