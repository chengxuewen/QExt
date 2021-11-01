#ifndef _QEXTMVVMPROJECTMANAGERFACTORY_H
#define _QEXTMVVMPROJECTMANAGERFACTORY_H

#include <memory>
#include <qextMvvmProjectManagerInterface.h>

namespace ModelView
{

struct QEXTMvvmProjectContext;
struct QEXTMvvmUserInteractionContext;

//! Creates default QEXTMvvmProjectManager to save and load models.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmProjectManagerInterface>
CreateProjectManager(const QEXTMvvmProjectContext& project_context,
                     const QEXTMvvmUserInteractionContext& user_context);

} // namespace ModelView

#endif // _QEXTMVVMPROJECTMANAGERFACTORY_H
