#ifndef _QEXTMVVMUNDDOSTACKINTERFACE_H
#define _QEXTMVVMUNDDOSTACKINTERFACE_H

#include <QSharedPointer>
#include <QString>

class QUndoCommand;

class QEXTMvvmAbstractItemCommand;

//! Interface class for undo/redo stack.
class QEXTMvvmUndoStackInterface
{
public:
    virtual ~QEXTMvvmUndoStackInterface() { }

    //! Executes the command, then pushes it in the stack for possible undo.
    //! Current design relies on shared pointer. This is done
    //! a) to retrieve result of the command from another place
    //! b) to adapt the command for QUndoStack
    //! c) to bypass QUndoStack behavior which wants to have an ownership
    virtual void execute(const QSharedPointer<QEXTMvvmAbstractItemCommand> &command) = 0;

    virtual bool isActive() const = 0;
    virtual bool canUndo() const = 0;
    virtual bool canRedo() const = 0;
    virtual int index() const = 0;
    virtual int count() const = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void clear() = 0;
    virtual void setUndoLimit(int limit) = 0;

    virtual void beginMacro(const QString &name) = 0;
    virtual void endMacro() = 0;
};


#endif // _QEXTMVVMUNDDOSTACKINTERFACE_H
