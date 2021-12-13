// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDSERVICE_H
#define MVVM_COMMANDS_COMMANDSERVICE_H

#include <memory>
#include <commands/qextMvvmCommandResult.h>
#include <commands/qextMvvmUndoStack.h>
#include <qextMvvmVariant.h>
#include <qextMvvmFunctionTypes.h>
#include <qextMvvmGlobal.h>

class QUndoCommand;

namespace ModelView
{

class SessionModel;
class QEXTMvvmSessionItem;
class TagRow;

//! Provides undo/redo for all commands of SessionModel.

class QEXT_MVVM_API QEXTMvvmCommandService
{
public:
    QEXTMvvmCommandService(SessionModel* model);

    void setUndoRedoEnabled(bool value);

    QEXTMvvmSessionItem* insertNewItem(const item_factory_func_t& func, QEXTMvvmSessionItem* parent,
                               const TagRow& tagrow);

    QEXTMvvmSessionItem* copyItem(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, const TagRow& tagrow);

    bool setData(QEXTMvvmSessionItem* item, const Variant& value, int role);

    void removeItem(QEXTMvvmSessionItem* parent, const TagRow& tagrow);

    void moveItem(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, const TagRow& tagrow);

    QEXTMvvmUndoStackInterface* undoStack() const;

    void setCommandRecordPause(bool value);

private:
    template <typename C, typename... Args> CommandResult process_command(Args&&... args);

    bool provideUndo() const;

    SessionModel* m_model;
    std::unique_ptr<QEXTMvvmUndoStackInterface> m_commands;
    bool m_pause_record;
};

//! Creates and processes command of given type using given argument list.

template <typename C, typename... Args>
CommandResult QEXTMvvmCommandService::process_command(Args&&... args)
{
    if (provideUndo()) {
        // making shared because underlying QUndoStack requires ownership
        auto command = std::make_shared<C>(std::forward<Args>(args)...);
        m_commands->execute(command);
        return command->result();
    } else {
        C command(std::forward<Args>(args)...);
        command.execute();
        return command.result();
    }
}

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDSERVICE_H
