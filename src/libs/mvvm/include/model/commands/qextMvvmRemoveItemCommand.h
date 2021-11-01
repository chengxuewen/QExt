#ifndef _QEXTMVVMREMOVEITEMCOMMAND_H
#define _QEXTMVVMREMOVEITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.

class QEXT_MVVM_API QEXTRemoveItemCommand : public QEXTAbstractItemCommand
{
public:
    QEXTRemoveItemCommand(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    ~QEXTRemoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct RemoveItemCommandImpl;
    std::unique_ptr<RemoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMREMOVEITEMCOMMAND_H
