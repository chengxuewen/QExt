#ifndef _QEXTMVVMCOMMANDSADAPTER_H
#define _QEXTMVVMCOMMANDSADAPTER_H

#include <qextMvvmGlobal.h>

#include <QUndoCommand>
#include <memory>

namespace ModelView
{

class QEXTMvvmItemCommand;

//! Adapter to execute our commands within Qt undo/redo framework.

class QEXT_MVVM_API QEXTMvvmCommandAdapter : public QUndoCommand
{
public:
    QEXTMvvmCommandAdapter(std::shared_ptr<QEXTMvvmItemCommand> command);
    ~QEXTMvvmCommandAdapter() override;

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<QEXTMvvmItemCommand> m_command;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDSADAPTER_H
