// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_PROJECTMANAGERFACTORY_H
#define MVVM_FACTORIES_PROJECTMANAGERFACTORY_H

#include "model/interfaces/projectmanagerinterface.h"
#include <memory>

namespace ModelView {

struct QExtMvvmProjectContext;
struct QExtMvvmUserInteractionContext;

//! Creates default QExtMvvmProjectManager to save and load models.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmProjectManagerInterface>
qextMvvmCreateProjectManager(const QExtMvvmProjectContext& project_context,
                     const QExtMvvmUserInteractionContext& user_context);

} // namespace ModelView

#endif // MVVM_FACTORIES_PROJECTMANAGERFACTORY_H
