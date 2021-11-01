#ifndef _QEXTMVVMMOVEITEMCOMMAND_H
#define _QEXTMVVMMOVEITEMCOMMAND_H

#include <memory>
#include <qextMvvmAbstractItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo framework to move item from one parent to another.

class QEXT_MVVM_API QEXTMoveItemCommand : public QEXTAbstractItemCommand
{
public:
    QEXTMoveItemCommand(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, QEXTMvvmTagRow tagrow);
    ~QEXTMoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct MoveItemCommandImpl;
    std::unique_ptr<MoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMMOVEITEMCOMMAND_H
