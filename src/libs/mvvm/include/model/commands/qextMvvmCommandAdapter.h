#ifndef _QEXTMVVMCOMMANDADAPTER_H
#define _QEXTMVVMCOMMANDADAPTER_H

#include <qextMvvmGlobal.h>

#include <QUndoCommand>

#include <memory>

namespace ModelView
{

class QEXTAbstractItemCommand;

//! Adapter to execute our commands within Qt undo/redo framework.

class QEXT_MVVM_API QEXTCommandAdapter : public QUndoCommand
{
public:
    QEXTCommandAdapter(std::shared_ptr<QEXTAbstractItemCommand> command);
    ~QEXTCommandAdapter() override;

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<QEXTAbstractItemCommand> m_command;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDADAPTER_H
