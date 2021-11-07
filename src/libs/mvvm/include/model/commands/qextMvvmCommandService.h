#ifndef _QEXTMVVMCOMMANDSERVICE_H
#define _QEXTMVVMCOMMANDSERVICE_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCommandResult.h>
#include <qextMvvmUndoStack.h>
#include <qextMvvmTypes.h>

#include <memory>

class QUndoCommand;


class QEXTMvvmModel;
class QEXTMvvmItem;
class QEXTMvvmTagRow;

//! Provides undo/redo for all commands of QEXTMvvmModel.

class QEXTMvvmCommandServicePrivate;
class QEXT_MVVM_API QEXTMvvmCommandService
{
public:
    QEXTMvvmCommandService(QEXTMvvmModel *model);
    virtual ~QEXTMvvmCommandService();

    QEXTMvvmUndoStackInterface *undoStack() const;
    void setUndoRedoEnabled(bool value);
    void setCommandRecordPause(bool value);

    QEXTMvvmItem *insertNewItem(const QEXTMvvmItemFactoryFunction &func, QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow);
    void removeItem(QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow);
    void moveItem(QEXTMvvmItem *item, QEXTMvvmItem *newParent, const QEXTMvvmTagRow &tagrow);
    QEXTMvvmItem *copyItem(QEXTMvvmItem *item, QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow);

    bool setData(QEXTMvvmItem *item, const QVariant &value, int role);

protected:
    template <typename T_command, typename T_arg1>
    QEXTMvvmCommandResult processCommand(T_arg1 arg1);

    template <typename T_command, typename T_arg1, typename T_arg2>
    QEXTMvvmCommandResult processCommand(T_arg1 arg1, T_arg2 arg2);

    template <typename T_command, typename T_arg1, typename T_arg2, typename T_arg3>
    QEXTMvvmCommandResult processCommand(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3);

    bool provideUndo() const;
    void execute(const QSharedPointer<QEXTMvvmAbstractItemCommand> &command);

    QScopedPointer<QEXTMvvmCommandServicePrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmCommandService)
    QEXT_DECL_PRIVATE(QEXTMvvmCommandService)
};



template<typename T_command, typename T_arg1>
QEXTMvvmCommandResult QEXTMvvmCommandService::processCommand(T_arg1 arg1)
{
    if (this->provideUndo())
    {
        // making shared because underlying QUndoStack requires ownership
        QSharedPointer<T_command> command(new T_command(arg1));
        this->execute(command);
        return command->result();
    }
    else
    {
        T_command command(arg1);
        command.execute();
        return command.result();
    }
}

template<typename T_command, typename T_arg1, typename T_arg2>
QEXTMvvmCommandResult QEXTMvvmCommandService::processCommand(T_arg1 arg1, T_arg2 arg2)
{
    if (this->provideUndo())
    {
        // making shared because underlying QUndoStack requires ownership
        QSharedPointer<T_command> command(new T_command(arg1, arg2));
        this->execute(command);
        return command->result();
    }
    else
    {
        T_command command(arg1, arg2);
        command.execute();
        return command.result();
    }
}

template<typename T_command, typename T_arg1, typename T_arg2, typename T_arg3>
QEXTMvvmCommandResult QEXTMvvmCommandService::processCommand(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
{
    if (this->provideUndo())
    {
        // making shared because underlying QUndoStack requires ownership
        QSharedPointer<T_command> command(new T_command(arg1, arg2, arg3));
        this->execute(command);
        return command->result();
    }
    else
    {
        T_command command(arg1, arg2, arg3);
        command.execute();
        return command.result();
    }
}


#endif // _QEXTMVVMCOMMANDSERVICE_H
