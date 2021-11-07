#include <qextMvvmUndoStack.h>
#include <qextMvvmUndoStack_p.h>
#include <qextMvvmCommandAdapter.h>

#include <QUndoStack>


QEXTMvvmUndoStackPrivate::QEXTMvvmUndoStackPrivate(QEXTMvvmUndoStack *q)
    : q_ptr(q)
{

}

QEXTMvvmUndoStackPrivate::~QEXTMvvmUndoStackPrivate()
{

}



QEXTMvvmUndoStack::QEXTMvvmUndoStack()
    : d_ptr(new QEXTMvvmUndoStackPrivate(this))
{

}

QEXTMvvmUndoStack::~QEXTMvvmUndoStack()
{

}

void QEXTMvvmUndoStack::execute(const QSharedPointer<QEXTMvvmAbstractItemCommand> &command)
{
    QEXT_DECL_D(QEXTMvvmUndoStack);
    // Wrapping command for Qt. It will be executed by Qt after push.
    QEXTCommandAdapter *adapter = new QEXTCommandAdapter(command);
    d->m_undoStack->push(adapter);
}

bool QEXTMvvmUndoStack::isActive() const
{
    QEXT_DECL_DC(QEXTMvvmUndoStack);
    return d->m_undoStack->isActive();
}

bool QEXTMvvmUndoStack::canUndo() const
{
    QEXT_DECL_DC(QEXTMvvmUndoStack);
    return d->m_undoStack->canUndo();
}

bool QEXTMvvmUndoStack::canRedo() const
{
    QEXT_DECL_DC(QEXTMvvmUndoStack);
    return d->m_undoStack->canRedo();
}

int QEXTMvvmUndoStack::index() const
{
    QEXT_DECL_DC(QEXTMvvmUndoStack);
    return d->m_undoStack->index();
}

int QEXTMvvmUndoStack::count() const
{
    QEXT_DECL_DC(QEXTMvvmUndoStack);
    return d->m_undoStack->count();
}

void QEXTMvvmUndoStack::undo()
{
    QEXT_DECL_D(QEXTMvvmUndoStack);
    return d->m_undoStack->undo();
}

void QEXTMvvmUndoStack::redo()
{
    QEXT_DECL_D(QEXTMvvmUndoStack);
    return d->m_undoStack->redo();
}

void QEXTMvvmUndoStack::clear()
{
    QEXT_DECL_D(QEXTMvvmUndoStack);
    return d->m_undoStack->clear();
}

void QEXTMvvmUndoStack::setUndoLimit(int limit)
{
    QEXT_DECL_D(QEXTMvvmUndoStack);
    return d->m_undoStack->setUndoLimit(limit);
}

//! Returns underlying QUndoStack if given object can be casted to QEXTMvvmUndoStack instance.
//! This method is used to "convert" current instance to Qt implementation, and use it with other
//! Qt widgets, if necessary.

QUndoStack *QEXTMvvmUndoStack::qtUndoStack(QEXTMvvmUndoStackInterface *stackInterface)
{
    QEXTMvvmUndoStack *undoStack = dynamic_cast<QEXTMvvmUndoStack *>(stackInterface);
    if (undoStack)
    {
        return undoStack->d_func()->m_undoStack.data();
    }
    return QEXT_DECL_NULLPTR;
}

void QEXTMvvmUndoStack::beginMacro(const QString &name)
{
    QEXT_DECL_D(QEXTMvvmUndoStack);
    d->m_undoStack->beginMacro(name);
}

void QEXTMvvmUndoStack::endMacro()
{
    QEXT_DECL_D(QEXTMvvmUndoStack);
    d->m_undoStack->endMacro();
}
