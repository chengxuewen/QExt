#ifndef _QEXTMVVMUNDOSTACK_H
#define _QEXTMVVMUNDOSTACK_H

#include <qextMvvmUndoStackInterface.h>
#include <qextMvvmGlobal.h>

#include <QSharedPointer>

class QUndoStack;

//! Default undo stack implementation. Internally relies on QUndoStack.
//! It serves two goals: a) hides Qt usage b) simplifies future refactoring toward Qt-independent
//! libmvvm_model library.

class QEXTMvvmUndoStackPrivate;
class QEXT_MVVM_API QEXTMvvmUndoStack : public QEXTMvvmUndoStackInterface
{
public:
    QEXTMvvmUndoStack();
    ~QEXTMvvmUndoStack() QEXT_DECL_OVERRIDE;

    //! Executes the command, then pushes it in the stack for possible undo.
    void execute(const QSharedPointer<QEXTMvvmAbstractItemCommand> &command) QEXT_DECL_OVERRIDE;

    bool isActive() const QEXT_DECL_OVERRIDE;
    bool canUndo() const QEXT_DECL_OVERRIDE;
    bool canRedo() const QEXT_DECL_OVERRIDE;
    int index() const QEXT_DECL_OVERRIDE;
    int count() const QEXT_DECL_OVERRIDE;
    void undo() QEXT_DECL_OVERRIDE;
    void redo() QEXT_DECL_OVERRIDE;
    void clear() QEXT_DECL_OVERRIDE;
    void setUndoLimit(int limit) QEXT_DECL_OVERRIDE;

    void beginMacro(const QString &name) QEXT_DECL_OVERRIDE;
    void endMacro() QEXT_DECL_OVERRIDE;

    static QUndoStack *qtUndoStack(QEXTMvvmUndoStackInterface *stackInterface);

protected:
    QScopedPointer<QEXTMvvmUndoStackPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmUndoStack)
    QEXT_DECL_PRIVATE(QEXTMvvmUndoStack)
};

#endif // _QEXTMVVMUNDOSTACK_H
