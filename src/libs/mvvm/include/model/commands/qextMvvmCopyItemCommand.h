// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COPYITEMCOMMAND_H
#define MVVM_COMMANDS_COPYITEMCOMMAND_H

#include <commands/qextMvvmItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class TagRow;

//! Command to copy an item.

class QEXT_MVVM_API QEXTMvvmCopyItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmCopyItemCommand(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, TagRow tagrow);
    ~QEXTMvvmCopyItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct CopyItemCommandImpl;
    std::unique_ptr<CopyItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_COPYITEMCOMMAND_H
