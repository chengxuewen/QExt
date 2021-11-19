#ifndef _QEXTMVVMREMOVEITEMCOMMAND_H
#define _QEXTMVVMREMOVEITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>

class QEXTMvvmItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.
class QEXTMvvmRemoveItemCommandPrivate;
class QEXT_MVVM_API QEXTMvvmRemoveItemCommand : public QEXTMvvmAbstractItemCommand
{
public:
    QEXTMvvmRemoveItemCommand(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    ~QEXTMvvmRemoveItemCommand() QEXT_DECL_OVERRIDE;

protected:
    void undoCommand() QEXT_DECL_OVERRIDE;
    void executeCommand() QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmRemoveItemCommand)
    Q_DECLARE_PRIVATE(QEXTMvvmRemoveItemCommand)
};


#endif // _QEXTMVVMREMOVEITEMCOMMAND_H
