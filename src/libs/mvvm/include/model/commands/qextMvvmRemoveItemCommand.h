// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_REMOVEITEMCOMMAND_H
#define MVVM_COMMANDS_REMOVEITEMCOMMAND_H

#include <commands/qextMvvmItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class TagRow;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.

class QEXT_MVVM_API QEXTMvvmRemoveItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmRemoveItemCommand(QEXTMvvmSessionItem* parent, TagRow tagrow);
    ~QEXTMvvmRemoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct RemoveItemCommandImpl;
    std::unique_ptr<RemoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_REMOVEITEMCOMMAND_H
