// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QUndoStack>

#include <qextMvvmCommandAdapter.h>
#include <qextMvvmUndoStack.h>
#include <qextMvvmTypes.h>

using namespace ModelView;

struct QEXTMvvmUndoStack::UndoStackImpl {
    std::unique_ptr<QUndoStack> m_undoStack;
    UndoStackImpl() : m_undoStack(make_unique<QUndoStack>()) {}
    QUndoStack* undoStack() { return m_undoStack.get(); }
};

QEXTMvvmUndoStack::QEXTMvvmUndoStack() : p_impl(make_unique<UndoStackImpl>()) {}

void QEXTMvvmUndoStack::execute(std::shared_ptr<QEXTMvvmItemCommand> command)
{
    // Wrapping command for Qt. It will be executed by Qt after push.
    auto adapter = new QEXTMvvmCommandAdapter(std::move(command));
    p_impl->undoStack()->push(adapter);
}

QEXTMvvmUndoStack::~QEXTMvvmUndoStack() = default;

bool QEXTMvvmUndoStack::isActive() const
{
    return p_impl->undoStack()->isActive();
}

bool QEXTMvvmUndoStack::canUndo() const
{
    return p_impl->undoStack()->canUndo();
}

bool QEXTMvvmUndoStack::canRedo() const
{
    return p_impl->undoStack()->canRedo();
}

int QEXTMvvmUndoStack::index() const
{
    return p_impl->undoStack()->index();
}

int QEXTMvvmUndoStack::count() const
{
    return p_impl->undoStack()->count();
}

void QEXTMvvmUndoStack::undo()
{
    return p_impl->undoStack()->undo();
}

void QEXTMvvmUndoStack::redo()
{
    return p_impl->undoStack()->redo();
}

void QEXTMvvmUndoStack::clear()
{
    return p_impl->undoStack()->clear();
}

void QEXTMvvmUndoStack::setUndoLimit(int limit)
{
    return p_impl->undoStack()->setUndoLimit(limit);
}

//! Returns underlying QUndoStack if given object can be casted to QEXTMvvmUndoStack instance.
//! This method is used to "convert" current instance to Qt implementation, and use it with other
//! Qt widgets, if necessary.

QUndoStack* QEXTMvvmUndoStack::qtUndoStack(QEXTMvvmUndoStackInterface* stack_interface)
{
    if (auto stack = dynamic_cast<QEXTMvvmUndoStack*>(stack_interface); stack)
        return stack->p_impl->undoStack();
    return nullptr;
}

void QEXTMvvmUndoStack::beginMacro(const std::string& name)
{
    p_impl->undoStack()->beginMacro(QString::fromStdString(name));
}

void QEXTMvvmUndoStack::endMacro()
{
    p_impl->undoStack()->endMacro();
}
