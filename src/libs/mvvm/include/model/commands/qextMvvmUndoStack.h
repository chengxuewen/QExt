#ifndef _QEXTMVVMUNDOSTACK_H
#define _QEXTMVVMUNDOSTACK_H

#include <memory>
#include <qextMvvmUndoStackInterface.h>
#include <qextMvvmGlobal.h>

class QUndoStack;

namespace ModelView
{

//! Default undo stack implementation. Internally relies on QUndoStack.
//! It serves two goals: a) hides Qt usage b) simplifies future refactoring toward Qt-independent
//! libmvvm_model library.

class QEXT_MVVM_API QEXTUndoStack : public QEXTMvvmUndoStackInterface
{
public:
    QEXTUndoStack();
    ~QEXTUndoStack() override;

    //! Executes the command, then pushes it in the stack for possible undo.
    void execute(std::shared_ptr<QEXTAbstractItemCommand> command) override;

    bool isActive() const override;
    bool canUndo() const override;
    bool canRedo() const override;
    int index() const override;
    int count() const override;
    void undo() override;
    void redo() override;
    void clear() override;
    void setUndoLimit(int limit) override;

    static QUndoStack* qtUndoStack(QEXTMvvmUndoStackInterface* stack_interface);

    void beginMacro(const std::string& name) override;
    void endMacro() override;

private:
    struct UndoStackImpl;
    std::unique_ptr<UndoStackImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMUNDOSTACK_H
