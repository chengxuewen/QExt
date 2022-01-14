#ifndef _QEXTMVVMCOMMANDSREMOVEITEMCOMMAND_H
#define _QEXTMVVMCOMMANDSREMOVEITEMCOMMAND_H

#include <qextMvvmItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.

class QEXT_MVVM_API QEXTMvvmRemoveItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmRemoveItemCommand(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    ~QEXTMvvmRemoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct RemoveItemCommandImpl;
    std::unique_ptr<RemoveItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDSREMOVEITEMCOMMAND_H
