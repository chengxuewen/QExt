// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmProjectManagerFactory.h>
#include <project/qextMvvmProjectTypes.h>
#include <project/qextMvvmProjectManagerDecorator.h>

namespace ModelView
{
std::unique_ptr<QEXTMvvmProjectManagerInterface>
CreateProjectManager(const QEXTMvvmProjectContext& project_context,
                     const UserInteractionContext& user_context)
{
    return make_unique<QEXTMvvmProjectManagerDecorator>(project_context, user_context);
}

} // namespace ModelView
