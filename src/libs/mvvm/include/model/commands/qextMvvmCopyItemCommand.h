#ifndef _QEXTMVVMCOPYITEMCOMMAND_H
#define _QEXTMVVMCOPYITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Command to copy an item.

class QEXT_MVVM_API QEXTCopyItemCommand : public QEXTAbstractItemCommand
{
public:
    QEXTCopyItemCommand(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    ~QEXTCopyItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct CopyItemCommandImpl;
    std::unique_ptr<CopyItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMCOPYITEMCOMMAND_H
