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

#include "qextMVVMGlobal.h"
#include <memory>
#include <string>

namespace ModelView {

class SessionModel;
class ProjectInterface;
struct ProjectContext;

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils {

QEXT_MVVM_API std::string SuggestFileName(const SessionModel& model);

QEXT_MVVM_API bool IsPossibleProjectDir(const std::string& project_dir);

QEXT_MVVM_API QExtUniquePointer<ProjectInterface>
CreateUntitledProject(const ProjectContext& context);

QEXT_MVVM_API std::string ProjectWindowTitle(const ProjectInterface& project);

QEXT_MVVM_API std::string ProjectWindowTitle(const std::string& project_dir, bool is_modified);

} // namespace ProjectUtils

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTUTILS_H
