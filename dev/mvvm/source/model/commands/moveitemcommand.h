// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_MOVEITEMCOMMAND_H
#define MVVM_COMMANDS_MOVEITEMCOMMAND_H

#include "model/commands/abstractitemcommand.h"
#include <memory>

namespace ModelView {

// class QExtMvvmSessionItem;
// class QExtMvvmTagRow;

// //! Command for unddo/redo framework to move item from one parent to another.

// class QEXT_MVVM_API QExtMvvmMoveItemCommand : public QExtMvvmAbstractItemCommand {
// public:
//     QExtMvvmMoveItemCommand(QExtMvvmSessionItem* item, QExtMvvmSessionItem* new_parent, QExtMvvmTagRow tagrow);
//     ~QExtMvvmMoveItemCommand() override;

// private:
//     void undo_command() override;
//     void execute_command() override;

//     struct MoveItemCommandImpl;
//     QExtUniquePointer<MoveItemCommandImpl> p_impl;
// };

} // namespace ModelView

#endif // MVVM_COMMANDS_MOVEITEMCOMMAND_H
