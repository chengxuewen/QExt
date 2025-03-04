// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECTUTILS_H
#define MVVM_PROJECT_PROJECTUTILS_H

#include <qextMvvmGlobal.h>
#include <memory>
#include <string>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmProjectInterface;
struct QExtMvvmProjectContext;

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils {

QEXT_MVVM_API std::string SuggestFileName(const QExtMvvmSessionModel& model);

QEXT_MVVM_API bool IsPossibleProjectDir(const std::string& project_dir);

QEXT_MVVM_API QExtUniquePointer<QExtMvvmProjectInterface>
CreateUntitledProject(const QExtMvvmProjectContext& context);

QEXT_MVVM_API std::string ProjectWindowTitle(const QExtMvvmProjectInterface& project);

QEXT_MVVM_API std::string ProjectWindowTitle(const std::string& project_dir, bool is_modified);

} // namespace ProjectUtils

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTUTILS_H
