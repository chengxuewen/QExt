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

#include <commands/qextMvvmItemCommand.h>
#include <qextMvvmVariant.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Command for unddo/redo framework to set the data of QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmSetValueCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmSetValueCommand(QEXTMvvmSessionItem* item, Variant value, int role);
    ~QEXTMvvmSetValueCommand() override;

private:
    void undo_command() override;
    void execute_command() override;
    void swap_values();

    struct SetValueCommandImpl;
    std::unique_ptr<SetValueCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_SETVALUECOMMAND_H
