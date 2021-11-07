#ifndef _QEXTMVVMCUSTOMPLOTUTILS_H
#define _QEXTMVVMCUSTOMPLOTUTILS_H

#include <qextMvvmGlobal.h>

class QCPColorScale;
class QCPAxis;

namespace QEXTMvvmCustomPlotUtils
{

//! Switch axis to logarithmic scale mode.

QEXT_MVVM_API void SetLogarithmicScale(QCPColorScale* axis, bool is_log_scale);

//! Switch axis to logarithmic scale mode.

QEXT_MVVM_API void SetLogarithmicScale(QCPAxis* axis, bool is_log_scale);

} // namespace Utils

#endif // _QEXTMVVMCUSTOMPLOTUTILS_H
