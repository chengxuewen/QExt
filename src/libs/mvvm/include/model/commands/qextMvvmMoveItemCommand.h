#ifndef _QEXTMVVMMOVEITEMCOMMAND_H
#define _QEXTMVVMMOVEITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>

class QEXTMvvmItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo framework to move item from one parent to another.
class QEXTMvvmMoveItemCommandPrivate;
class QEXT_MVVM_API QEXTMvvmMoveItemCommand : public QEXTMvvmAbstractItemCommand
{
public:
    QEXTMvvmMoveItemCommand(QEXTMvvmItem *item, QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    ~QEXTMvvmMoveItemCommand() QEXT_DECL_OVERRIDE;

protected:
    void undoCommand() QEXT_DECL_OVERRIDE;
    void executeCommand() QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmMoveItemCommand)
    QEXT_DECL_PRIVATE(QEXTMvvmMoveItemCommand)
};


#endif // _QEXTMVVMMOVEITEMCOMMAND_H
