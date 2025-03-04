// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmUndoStack.h>
#include <qextMvvmCommandAdapter.h>

using namespace ModelView;

struct QExtMvvmUndoStack::UndoStackImpl {
    QExtUniquePointer<QUndoStack> m_undoStack;
    UndoStackImpl() : m_undoStack(qextMakeUnique<QUndoStack>()) {}
    QUndoStack* undoStack() { return m_undoStack.get(); }
};

QExtMvvmUndoStack::QExtMvvmUndoStack() : p_impl(qextMakeUnique<UndoStackImpl>()) {}

void QExtMvvmUndoStack::execute(std::shared_ptr<QExtMvvmAbstractItemCommand> command)
{
    // Wrapping command for Qt. It will be executed by Qt after push.
    auto adapter = new QExtMvvmCommandAdapter(std::move(command));
    p_impl->undoStack()->push(adapter);
}

QExtMvvmUndoStack::~QExtMvvmUndoStack() = default;

bool QExtMvvmUndoStack::isActive() const
{
    return p_impl->undoStack()->isActive();
}

bool QExtMvvmUndoStack::canUndo() const
{
    return p_impl->undoStack()->canUndo();
}

bool QExtMvvmUndoStack::canRedo() const
{
    return p_impl->undoStack()->canRedo();
}

int QExtMvvmUndoStack::index() const
{
    return p_impl->undoStack()->index();
}

int QExtMvvmUndoStack::count() const
{
    return p_impl->undoStack()->count();
}

void QExtMvvmUndoStack::undo()
{
    return p_impl->undoStack()->undo();
}

void QExtMvvmUndoStack::redo()
{
    return p_impl->undoStack()->redo();
}

void QExtMvvmUndoStack::clear()
{
    return p_impl->undoStack()->clear();
}

void QExtMvvmUndoStack::setUndoLimit(int limit)
{
    return p_impl->undoStack()->setUndoLimit(limit);
}

//! Returns underlying QUndoStack if given object can be casted to QExtMvvmUndoStack instance.
//! This method is used to "convert" current instance to Qt implementation, and use it with other
//! Qt widgets, if necessary.

QUndoStack* QExtMvvmUndoStack::qtUndoStack(QExtMvvmUndoStackInterface* stack_interface)
{
    if (auto stack = dynamic_cast<QExtMvvmUndoStack*>(stack_interface); stack)
        return stack->p_impl->undoStack();
    return nullptr;
}

void QExtMvvmUndoStack::beginMacro(const std::string& name)
{
    p_impl->undoStack()->beginMacro(QString::fromStdString(name));
}

void QExtMvvmUndoStack::endMacro()
{
    p_impl->undoStack()->endMacro();
}
