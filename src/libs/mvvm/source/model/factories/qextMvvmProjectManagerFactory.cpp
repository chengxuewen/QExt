#include <qextMvvmProjectManagerFactory.h>
#include <project/qextMvvmProjectTypes.h>
#include <project/qextMvvmProjectManagerDecorator.h>

namespace ModelView
{
    std::unique_ptr<QEXTMvvmProjectManagerInterface>
    CreateProjectManager(const QEXTMvvmProjectContext &project_context,
                         const QEXTMvvmUserInteractionContext &user_context)
    {
        return std::make_unique<QEXTMvvmProjectManagerDecorator>(project_context, user_context);
    }

} // namespace ModelView
