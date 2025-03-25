// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONUTILS_H
#define MVVM_SERIALIZATION_JSONUTILS_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmRealLimits;

namespace JsonUtils {

//! Returns multiline string representing model content as json.
QEXT_MVVM_API std::string ModelToJsonString(const QExtMvvmSessionModel& model);

//! Returns string representation of QExtMvvmRealLimits.
QEXT_MVVM_API std::string ToString(const QExtMvvmRealLimits& limits);

QEXT_MVVM_API QExtMvvmRealLimits CreateLimits(const std::string& text, double min = 0.0,
                                          double max = 0.0);

} // namespace JsonUtils

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONUTILS_H
