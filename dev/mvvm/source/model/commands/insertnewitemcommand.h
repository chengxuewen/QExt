// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_INSERTNEWITEMCOMMAND_H
#define MVVM_COMMANDS_INSERTNEWITEMCOMMAND_H

#include "model/commands/abstractitemcommand.h"
#include "model/model/function_types.h"

namespace ModelView {

// class QExtMvvmSessionItem;
// class QExtMvvmTagRow;

// //! Command for unddo/redo to insert new item.

// class QEXT_MVVM_API QExtMvvmInsertNewItemCommand : public QExtMvvmAbstractItemCommand {
// public:
//     QExtMvvmInsertNewItemCommand(QExtMvvmItemFactoryFunc func, QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);
//     ~QExtMvvmInsertNewItemCommand() override;

// private:
//     void undo_command() override;
//     void execute_command() override;

//     struct InsertNewItemCommandImpl;
//     QExtUniquePointer<InsertNewItemCommandImpl> p_impl;
// };

} // namespace ModelView

#endif // MVVM_COMMANDS_INSERTNEWITEMCOMMAND_H
