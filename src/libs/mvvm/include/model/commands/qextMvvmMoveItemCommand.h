#ifndef _QEXTMVVMCOMMANDSMOVEITEMCOMMAND_H
#define _QEXTMVVMCOMMANDSMOVEITEMCOMMAND_H

#include <qextMvvmItemCommand.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo framework to move item from one parent to another.

class QEXT_MVVM_API QEXTMvvmMoveItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmMoveItemCommand(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, QEXTMvvmTagRow tagrow);
    ~QEXTMvvmMoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct MoveItemCommandImpl;
    std::unique_ptr<MoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDSMOVEITEMCOMMAND_H
