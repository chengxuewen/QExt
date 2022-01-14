#ifndef _QEXTMVVMPROJECTPROJECTUTILS_H
#define _QEXTMVVMPROJECTPROJECTUTILS_H

#include <qextMvvmGlobal.h>

#include <memory>
#include <string>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmProjectInterface;
struct QEXTMvvmProjectContext;

//! Collection of utility functions to handle project saving and loading.

namespace QEXTMvvmProjectUtils
{

QEXT_MVVM_API std::string SuggestFileName(const QEXTMvvmSessionModel& model);

QEXT_MVVM_API bool IsPossibleProjectDir(const std::string& project_dir);

QEXT_MVVM_API std::unique_ptr<QEXTMvvmProjectInterface>
CreateUntitledProject(const QEXTMvvmProjectContext& context);

QEXT_MVVM_API std::string ProjectWindowTitle(const QEXTMvvmProjectInterface& project);

QEXT_MVVM_API std::string ProjectWindowTitle(const std::string& project_dir, bool is_modified);

} // namespace ProjectUtils

} // namespace ModelView

#endif // _QEXTMVVMPROJECTPROJECTUTILS_H
