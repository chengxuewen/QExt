#ifndef _QEXTMVVMSERIALIZATIONJSONUTILS_H
#define _QEXTMVVMSERIALIZATIONJSONUTILS_H

#include <qextMvvmGlobal.h>

#include <string>

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmRealLimits;

namespace QEXTMvvmJsonUtils
{

//! Returns multiline string representing model content as json.
QEXT_MVVM_API std::string ModelToJsonString(const QEXTMvvmSessionModel& model);

//! Returns string representation of RealLimits.
QEXT_MVVM_API std::string ToString(const QEXTMvvmRealLimits& limits);

QEXT_MVVM_API QEXTMvvmRealLimits CreateLimits(const std::string& text, double min = 0.0,
                                          double max = 0.0);

} // namespace JsonUtils

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONUTILS_H
