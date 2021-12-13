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

#include <commands/qextMvvmItemCommand.h>
#include <qextMvvmFunctionTypes.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class TagRow;

//! Command for unddo/redo to insert new item.

class QEXT_MVVM_API QEXTMvvmInsertNewItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmInsertNewItemCommand(item_factory_func_t func, QEXTMvvmSessionItem* parent, const TagRow& tagrow);
    ~QEXTMvvmInsertNewItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertNewItemCommandImpl;
    std::unique_ptr<InsertNewItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_INSERTNEWITEMCOMMAND_H
