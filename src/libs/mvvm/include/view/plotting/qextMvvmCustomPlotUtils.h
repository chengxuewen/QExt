#ifndef _QEXTMVVMPLOTTINGCUSTOMPLOTUTILS_H
#define _QEXTMVVMPLOTTINGCUSTOMPLOTUTILS_H

#include <qextMvvmGlobal.h>

class QCPColorScale;
class QCPAxis;

namespace ModelView
{

namespace QEXTMvvmUtils
{

//! Switch axis to logarithmic scale mode.

QEXT_MVVM_API void SetLogarithmicScale(QCPColorScale* axis, bool is_log_scale);

//! Switch axis to logarithmic scale mode.

QEXT_MVVM_API void SetLogarithmicScale(QCPAxis* axis, bool is_log_scale);

} // namespace Utils

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGCUSTOMPLOTUTILS_H
