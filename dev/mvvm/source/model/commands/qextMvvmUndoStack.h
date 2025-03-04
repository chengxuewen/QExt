// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_UNDOSTACK_H
#define MVVM_COMMANDS_UNDOSTACK_H

#include "model/interfaces/undostackinterface.h"
#include <qextMvvmGlobal.h>
#include <memory>

class QUndoStack;

namespace ModelView
{

//! Default undo stack implementation. Internally relies on QUndoStack.
//! It serves two goals: a) hides Qt usage b) simplifies future refactoring toward Qt-independent
//! libmvvm_model library.

class QEXT_MVVM_API QExtMvvmUndoStack : public QExtMvvmUndoStackInterface
{
public:
    QExtMvvmUndoStack();
    ~QExtMvvmUndoStack() override;

    //! Executes the command, then pushes it in the stack for possible undo.
    void execute(std::shared_ptr<QExtMvvmAbstractItemCommand> command) override;

    bool isActive() const override;
    bool canUndo() const override;
    bool canRedo() const override;
    int index() const override;
    int count() const override;
    void undo() override;
    void redo() override;
    void clear() override;
    void setUndoLimit(int limit) override;

    static QUndoStack* qtUndoStack(QExtMvvmUndoStackInterface* stack_interface);

    void beginMacro(const std::string &name) override;
    void endMacro() override;

private:
    struct UndoStackImpl;
    QExtUniquePointer<UndoStackImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_UNDOSTACK_H
