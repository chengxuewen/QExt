// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDADAPTER_H
#define MVVM_COMMANDS_COMMANDADAPTER_H

#include <qextMvvmGlobal.h>

#include <QUndoCommand>
#include <memory>

namespace ModelView {

class QExtMvvmAbstractItemCommand;

//! Adapter to execute our commands within Qt undo/redo framework.

class QEXT_MVVM_API QExtMvvmCommandAdapter : public QUndoCommand
{
public:
    QExtMvvmCommandAdapter(std::shared_ptr<QExtMvvmAbstractItemCommand> command);
    ~QExtMvvmCommandAdapter() override;

    void undo() override;
    void redo() override;

private:
    std::shared_ptr<QExtMvvmAbstractItemCommand> m_command;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDADAPTER_H
