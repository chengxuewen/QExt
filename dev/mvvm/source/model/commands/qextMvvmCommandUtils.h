// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDUTILS_H
#define MVVM_COMMANDS_COMMANDUTILS_H

//! @file commandutils.h
//! Collection of various utility functions for command service.

#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmItemCopyStrategy.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionModel;

//! Creates strategy suitable for item saving/restoring. Restored item will have same identifiers
//! as original.

QEXT_MVVM_API QExtUniquePointer<QExtMvvmItemBackupStrategy>
qextMvvmCreateItemBackupStrategy(const QExtMvvmSessionModel* model);

//! Returns strategy for item copying. Identifiers of the copy will be different from identifiers
//! of the original.

QEXT_MVVM_API QExtUniquePointer<QExtMvvmItemCopyStrategy>
qextMvvmCreateItemCopyStrategy(const QExtMvvmSessionModel* model);

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDUTILS_H
