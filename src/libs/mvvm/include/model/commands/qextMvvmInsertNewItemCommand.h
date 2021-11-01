#ifndef _QEXTMVVMINSERTNEWITEMCOMMAND_H
#define _QEXTMVVMINSERTNEWITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmFunctionTypes.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo to insert new item.

class QEXT_MVVM_API QEXTInsertNewItemCommand : public QEXTAbstractItemCommand
{
public:
    QEXTInsertNewItemCommand(item_factory_func_t func, QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow);
    ~QEXTInsertNewItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertNewItemCommandImpl;
    std::unique_ptr<InsertNewItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMINSERTNEWITEMCOMMAND_H
