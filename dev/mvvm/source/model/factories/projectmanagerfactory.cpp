// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/factories/projectmanagerfactory.h"
#include "model/project/projectmanagerdecorator.h"

namespace ModelView {
QExtUniquePointer<ProjectManagerInterface>
CreateProjectManager(const ProjectContext& project_context,
                     const UserInteractionContext& user_context)
{
    return qextMakeUnique<ProjectManagerDecorator>(project_context, user_context);
}

} // namespace ModelView
