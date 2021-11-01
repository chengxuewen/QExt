#include <QUndoStack>
#include <qextMvvmCommandAdapter.h>
#include <qextMvvmUndoStack.h>

using namespace ModelView;

struct QEXTUndoStack::UndoStackImpl {
    std::unique_ptr<QUndoStack> m_undoStack;
    UndoStackImpl() : m_undoStack(std::make_unique<QUndoStack>()) {}
    QUndoStack* undoStack() { return m_undoStack.get(); }
};

QEXTUndoStack::QEXTUndoStack() : p_impl(std::make_unique<UndoStackImpl>()) {}

void QEXTUndoStack::execute(std::shared_ptr<QEXTAbstractItemCommand> command)
{
    // Wrapping command for Qt. It will be executed by Qt after push.
    auto adapter = new QEXTCommandAdapter(std::move(command));
    p_impl->undoStack()->push(adapter);
}

QEXTUndoStack::~QEXTUndoStack() = default;

bool QEXTUndoStack::isActive() const
{
    return p_impl->undoStack()->isActive();
}

bool QEXTUndoStack::canUndo() const
{
    return p_impl->undoStack()->canUndo();
}

bool QEXTUndoStack::canRedo() const
{
    return p_impl->undoStack()->canRedo();
}

int QEXTUndoStack::index() const
{
    return p_impl->undoStack()->index();
}

int QEXTUndoStack::count() const
{
    return p_impl->undoStack()->count();
}

void QEXTUndoStack::undo()
{
    return p_impl->undoStack()->undo();
}

void QEXTUndoStack::redo()
{
    return p_impl->undoStack()->redo();
}

void QEXTUndoStack::clear()
{
    return p_impl->undoStack()->clear();
}

void QEXTUndoStack::setUndoLimit(int limit)
{
    return p_impl->undoStack()->setUndoLimit(limit);
}

//! Returns underlying QUndoStack if given object can be casted to QEXTUndoStack instance.
//! This method is used to "convert" current instance to Qt implementation, and use it with other
//! Qt widgets, if necessary.

QUndoStack* QEXTUndoStack::qtUndoStack(QEXTMvvmUndoStackInterface* stack_interface)
{
    if (auto stack = dynamic_cast<QEXTUndoStack*>(stack_interface); stack)
        return stack->p_impl->undoStack();
    return nullptr;
}

void QEXTUndoStack::beginMacro(const std::string& name)
{
    p_impl->undoStack()->beginMacro(QString::fromStdString(name));
}

void QEXTUndoStack::endMacro()
{
    p_impl->undoStack()->endMacro();
}
