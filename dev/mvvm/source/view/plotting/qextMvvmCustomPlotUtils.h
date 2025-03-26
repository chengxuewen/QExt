// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_CUSTOMPLOTUTILS_H
#define MVVM_PLOTTING_CUSTOMPLOTUTILS_H

#include <qextMvvmGlobal.h>

class QCPColorScale;
class QCPAxis;

namespace ModelView
{
namespace Utils
{

//! Switch axis to logarithmic scale mode.
QEXT_MVVM_API void SetLogarithmicScale(QCPColorScale* axis, bool is_log_scale);

//! Switch axis to logarithmic scale mode.
QEXT_MVVM_API void SetLogarithmicScale(QCPAxis* axis, bool is_log_scale);

}
} // namespace ModelView::Utils

#endif // MVVM_PLOTTING_CUSTOMPLOTUTILS_H
