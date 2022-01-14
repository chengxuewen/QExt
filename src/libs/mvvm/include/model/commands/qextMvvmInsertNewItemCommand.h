#ifndef _QEXTMVVMCOMMANDSINSERTNEWITEMCOMMAND_H
#define _QEXTMVVMCOMMANDSINSERTNEWITEMCOMMAND_H

#include <qextMvvmItemCommand.h>
#include <qextMvvmFunctionTypes.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo to insert new item.

class QEXT_MVVM_API QEXTMvvmInsertNewItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmInsertNewItemCommand(item_factory_func_t func, QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow);
    ~QEXTMvvmInsertNewItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertNewItemCommandImpl;
    std::unique_ptr<InsertNewItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDSINSERTNEWITEMCOMMAND_H
