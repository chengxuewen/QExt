// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
#define MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H

#include <memory>
#include <commands/qextMvvmCommandResult.h>
#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView
{

class QEXTMvvmSessionItem;
class SessionModel;
class Path;

//! Abstract command interface to manipulate QEXTMvvmSessionItem in model context.

class QEXT_MVVM_API QEXTMvvmItemCommand
{
public:
    explicit QEXTMvvmItemCommand(QEXTMvvmSessionItem* receiver);
    virtual ~QEXTMvvmItemCommand();

    QEXTMvvmItemCommand(const QEXTMvvmItemCommand& other) = delete;
    QEXTMvvmItemCommand& operator=(const QEXTMvvmItemCommand& other) = delete;

    void execute();

    void undo();

    bool isObsolete() const;

    std::string description() const;

    CommandResult result() const;

protected:
    void setObsolete(bool flag);
    void setDescription(const std::string& text);
    Path pathFromItem(QEXTMvvmSessionItem* item) const;
    QEXTMvvmSessionItem* itemFromPath(const Path& path) const;
    SessionModel* model() const;
    void setResult(const CommandResult& command_result);

private:
    virtual void execute_command() = 0;
    virtual void undo_command() = 0;

    struct AbstractItemCommandImpl;
    std::unique_ptr<AbstractItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
