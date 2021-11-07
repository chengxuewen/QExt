#ifndef _QEXTMVVMPROJECTUTILS_H
#define _QEXTMVVMPROJECTUTILS_H

#include <qextMvvmGlobal.h>

#include <QString>
#include <QVector>

class QEXTMvvmModel;
class QEXTMvvmProjectInterface;
struct QEXTMvvmProjectContext;

//! Collection of utility functions to handle project saving and loading.
namespace ProjectUtils
{

    QEXT_MVVM_API QString SuggestFileName(const QEXTMvvmModel &model);

    QEXT_MVVM_API bool IsPossibleProjectDir(const QString &project_dir);

    QEXT_MVVM_API QEXTMvvmProjectInterface *CreateUntitledProject(const QEXTMvvmProjectContext &context);

    QEXT_MVVM_API QString ProjectWindowTitle(const QEXTMvvmProjectInterface &project);

    QEXT_MVVM_API QString ProjectWindowTitle(const QString &project_dir, bool is_modified);

} // namespace ProjectUtils



#endif // _QEXTMVVMPROJECTUTILS_H
