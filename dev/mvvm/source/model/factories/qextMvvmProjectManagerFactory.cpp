// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmProjectManagerFactory.h>
#include <qextMvvmProjectManagerDecorator.h>

namespace ModelView {
QExtUniquePointer<QExtMvvmProjectManagerInterface>
qextMvvmCreateProjectManager(const QExtMvvmProjectContext& project_context,
                     const QExtMvvmUserInteractionContext& user_context)
{
    return qextMakeUnique<QExtMvvmProjectManagerDecorator>(project_context, user_context);
}

} // namespace ModelView
