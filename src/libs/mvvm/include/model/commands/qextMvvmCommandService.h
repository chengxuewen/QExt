#ifndef _QEXTMVVMCOMMANDSCOMMANDSERVICE_H
#define _QEXTMVVMCOMMANDSCOMMANDSERVICE_H

#include <qextMvvmCommandResult.h>
#include <qextMvvmUndoStack.h>
#include <qextMvvmFunctionTypes.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QUndoCommand;

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmSessionItem;
class QEXTMvvmTagRow;

//! Provides undo/redo for all commands of SessionModel.

class QEXT_MVVM_API QEXTMvvmCommandService
{
public:
    QEXTMvvmCommandService(QEXTMvvmSessionModel* model);

    void setUndoRedoEnabled(bool value);

    QEXTMvvmSessionItem* insertNewItem(const item_factory_func_t& func, QEXTMvvmSessionItem* parent,
                               const QEXTMvvmTagRow& tagrow);

    QEXTMvvmSessionItem* copyItem(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow);

    bool setData(QEXTMvvmSessionItem* item, const QVariant& value, int role);

    void removeItem(QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow);

    void moveItem(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, const QEXTMvvmTagRow& tagrow);

    QEXTMvvmUndoStackInterface* undoStack() const;

    void setCommandRecordPause(bool value);

private:
    template <typename C, typename... Args> QEXTMvvmCommandResult process_command(Args&&... args);

    bool provideUndo() const;

    QEXTMvvmSessionModel* m_model;
    std::unique_ptr<QEXTMvvmUndoStackInterface> m_commands;
    bool m_pause_record;
};

//! Creates and processes command of given type using given argument list.

template <typename C, typename... Args>
QEXTMvvmCommandResult QEXTMvvmCommandService::process_command(Args&&... args)
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

#endif // _QEXTMVVMCOMMANDSCOMMANDSERVICE_H
