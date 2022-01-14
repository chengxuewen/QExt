#ifndef _QEXTMVVMCOMMANDSCOPYITEMCOMMAND_H
#define _QEXTMVVMCOMMANDSCOPYITEMCOMMAND_H

#include <commands/qextMvvmItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command to copy an item.

class QEXT_MVVM_API QEXTMvvmCopyItemCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmCopyItemCommand(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    ~QEXTMvvmCopyItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct CopyItemCommandImpl;
    std::unique_ptr<CopyItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDSCOPYITEMCOMMAND_H
