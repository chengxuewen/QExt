#ifndef _QEXTMVVMINSERTNEWITEMCOMMAND_H
#define _QEXTMVVMINSERTNEWITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmTypes.h>

class QEXTMvvmItem;
class QEXTMvvmTagRow;

//! Command for unddo/redo to insert new item.
class QEXTMvvmInsertNewItemCommandPrivate;
class QEXT_MVVM_API QEXTMvvmInsertNewItemCommand : public QEXTMvvmAbstractItemCommand
{
public:
    QEXTMvvmInsertNewItemCommand(QEXTMvvmItemFactoryFunction func, QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow);
    ~QEXTMvvmInsertNewItemCommand() QEXT_DECL_OVERRIDE;

protected:
    void undoCommand() QEXT_DECL_OVERRIDE;
    void executeCommand() QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmInsertNewItemCommand)
    Q_DECLARE_PRIVATE(QEXTMvvmInsertNewItemCommand)
};


#endif // _QEXTMVVMINSERTNEWITEMCOMMAND_H
