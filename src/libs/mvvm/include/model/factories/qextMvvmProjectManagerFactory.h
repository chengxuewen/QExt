#ifndef _QEXTMVVMFACTORIESPROJECTMANAGERFACTORY_H
#define _QEXTMVVMFACTORIESPROJECTMANAGERFACTORY_H

#include <qextMvvmProjectManagerInterface.h>

#include <memory>

namespace ModelView
{

struct QEXTMvvmProjectContext;
struct UserInteractionContext;

//! Creates default ProjectManager to save and load models.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmProjectManagerInterface>
CreateProjectManager(const QEXTMvvmProjectContext& project_context,
                     const UserInteractionContext& user_context);

} // namespace ModelView

#endif // _QEXTMVVMFACTORIESPROJECTMANAGERFACTORY_H
