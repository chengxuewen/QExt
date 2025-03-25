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

#include <qextMvvmCommandResult.h>
// #include "model/commands/commandresult.h"

#include <qextMvvmUndoStackInterface.h>
#include <qextMvvmFunctionTypes.h>
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmSessionItem;
class QExtMvvmTagRow;

//! Provides undo/redo for all commands of QExtMvvmSessionModel.

class QEXT_MVVM_API QExtMvvmCommandService {
public:
    QExtMvvmCommandService(QExtMvvmSessionModel* model);

    void setUndoRedoEnabled(bool value);

    QExtMvvmSessionItem* insertNewItem(const QExtMvvmItemFactoryFunc& func, QExtMvvmSessionItem* parent,
                               const QExtMvvmTagRow& tagrow);

    QExtMvvmSessionItem* copyItem(const QExtMvvmSessionItem* item, QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);

    bool setData(QExtMvvmSessionItem* item, const QVariant& value, int role);

    void removeItem(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);

    void moveItem(QExtMvvmSessionItem* item, QExtMvvmSessionItem* new_parent, const QExtMvvmTagRow& tagrow);

    QExtMvvmUndoStackInterface* undoStack() const;

    void setCommandRecordPause(bool value);

private:
    template <typename C, typename... Args> QExtMvvmCommandResult process_command(Args&&... args);

    bool provideUndo() const;

    QExtMvvmSessionModel* m_model;
    QExtUniquePointer<QExtMvvmUndoStackInterface> m_commands;
    bool m_pause_record;
};

//! Creates and processes command of given type using given argument list.

template <typename C, typename... Args>
QExtMvvmCommandResult QExtMvvmCommandService::process_command(Args&&... args)
{
    if (provideUndo()) {
        // making shared because underlying QUndoStack requires ownership
        auto command = std::make_shared<C>(std::forward<Args>(args)...);
        m_commands->execute(command);
        return command->result();
    }
    else {
        C command(std::forward<Args>(args)...);
        command.execute();
        return command.result();
    }
}

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDSERVICE_H
