// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_SETVALUECOMMAND_H
#define MVVM_COMMANDS_SETVALUECOMMAND_H

#include "model/commands/abstractitemcommand.h"
#include "model/core/variant.h"

namespace ModelView {

// class QExtMvvmSessionItem;

// //! Command for unddo/redo framework to set the data of QExtMvvmSessionItem.

// class QEXT_MVVM_API QExtMvvmSetValueCommand : public QExtMvvmAbstractItemCommand {
// public:
//     QExtMvvmSetValueCommand(QExtMvvmSessionItem* item, QVariant value, int role);
//     ~QExtMvvmSetValueCommand() override;

// private:
//     void undo_command() override;
//     void execute_command() override;
//     void swap_values();

//     struct SetValueCommandImpl;
//     QExtUniquePointer<SetValueCommandImpl> p_impl;
// };

} // namespace ModelView

#endif // MVVM_COMMANDS_SETVALUECOMMAND_H
