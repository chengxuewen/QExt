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

#include <memory>
#include <commands/qextMvvmItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class TagRow;

//! Command for unddo/redo framework to move item from one parent to another.

class QEXT_MVVM_API QEXTMvvmMoveItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmMoveItemCommand(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, TagRow tagrow);
    ~QEXTMvvmMoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct MoveItemCommandImpl;
    std::unique_ptr<MoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_MOVEITEMCOMMAND_H
