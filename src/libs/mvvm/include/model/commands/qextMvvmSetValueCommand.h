#ifndef _QEXTMVVMSETVALUECOMMAND_H
#define _QEXTMVVMSETVALUECOMMAND_H

#include <qextMvvmAbstractItemCommand.h>

class QEXTMvvmItem;

class QEXTMvvmSetValueCommandPrivate;
class QEXT_MVVM_API QEXTMvvmSetValueCommand : public QEXTMvvmAbstractItemCommand
{
public:
    QEXTMvvmSetValueCommand(QEXTMvvmItem *parent, QVariant value, int role);
    ~QEXTMvvmSetValueCommand() QEXT_DECL_OVERRIDE;

protected:
    void undoCommand() QEXT_DECL_OVERRIDE;
    void executeCommand() QEXT_DECL_OVERRIDE;

    void swapValues();

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmSetValueCommand)
    Q_DECLARE_PRIVATE(QEXTMvvmSetValueCommand)
};


#endif // _QEXTMVVMSETVALUECOMMAND_H
