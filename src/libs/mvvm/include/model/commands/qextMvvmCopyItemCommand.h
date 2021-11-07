#ifndef _QEXTMVVMCOPYITEMCOMMAND_H
#define _QEXTMVVMCOPYITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>

class QEXTMvvmItem;
class QEXTMvvmTagRow;

//! Command to copy an item.
class QEXTMvvmCopyItemCommandPrivate;
class QEXT_MVVM_API QEXTMvvmCopyItemCommand : public QEXTMvvmAbstractItemCommand
{
public:
    QEXTMvvmCopyItemCommand(QEXTMvvmItem *item, QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    ~QEXTMvvmCopyItemCommand() QEXT_DECL_OVERRIDE;

protected:
    void undoCommand() QEXT_DECL_OVERRIDE;
    void executeCommand() QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmCopyItemCommand)
    QEXT_DECL_PRIVATE(QEXTMvvmCopyItemCommand)
};


#endif // _QEXTMVVMCOPYITEMCOMMAND_H
