// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmItemCommand.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <stdexcept>

using namespace ModelView;

struct QEXTMvvmItemCommand::AbstractItemCommandImpl {
    enum EStatus { INITIAL, AFTER_EXECUTE, AFTER_UNDO };
    bool is_obsolete{false};
    std::string text;
    EStatus status{INITIAL};
    SessionModel* model{nullptr};
    QEXTMvvmItemCommand* parent_impl{nullptr};
    CommandResult m_result;
    AbstractItemCommandImpl(QEXTMvvmItemCommand* parent) : parent_impl(parent) {}

    void set_after_execute() { status = AFTER_EXECUTE; }
    void set_after_undo() { status = AFTER_UNDO; }
    bool can_execute() const { return status != AFTER_EXECUTE; }
    bool can_undo() const { return status == AFTER_EXECUTE && !parent_impl->isObsolete(); }
};

QEXTMvvmItemCommand::QEXTMvvmItemCommand(QEXTMvvmSessionItem* receiver)
    : p_impl(std::make_unique<QEXTMvvmItemCommand::AbstractItemCommandImpl>(this))
{
    if (!receiver)
        throw std::runtime_error("Invalid item.");

    if (!receiver->model())
        throw std::runtime_error("Item doesn't have a model");

    p_impl->model = receiver->model();
}

QEXTMvvmItemCommand::~QEXTMvvmItemCommand() = default;

//! Execute command.

void QEXTMvvmItemCommand::execute()
{
    if (!p_impl->can_execute())
        throw std::runtime_error("Can't execute the command. Wrong order.");

    execute_command();

    p_impl->set_after_execute();
}

//! Undo command as it was before execution.

void QEXTMvvmItemCommand::undo()
{
    if (!p_impl->can_undo())
        throw std::runtime_error("Can't undo the command. Wrong order.");

    undo_command();

    p_impl->set_after_undo();
}

//! Returns whether the command is obsolete (which means that it shouldn't be kept in the stack).

bool QEXTMvvmItemCommand::isObsolete() const
{
    return p_impl->is_obsolete;
}

//! Returns command description.

std::string QEXTMvvmItemCommand::description() const
{
    return p_impl->text;
}

CommandResult QEXTMvvmItemCommand::result() const
{
    return p_impl->m_result;
}

//! Sets command obsolete flag.

void QEXTMvvmItemCommand::setObsolete(bool flag)
{
    p_impl->is_obsolete = flag;
}

//! Sets command description.

void QEXTMvvmItemCommand::setDescription(const std::string& text)
{
    p_impl->text = text;
}

Path QEXTMvvmItemCommand::pathFromItem(QEXTMvvmSessionItem* item) const
{
    return p_impl->model->pathFromItem(item);
}

QEXTMvvmSessionItem* QEXTMvvmItemCommand::itemFromPath(const Path& path) const
{
    return p_impl->model->itemFromPath(path);
}

SessionModel* QEXTMvvmItemCommand::model() const
{
    return p_impl->model;
}

void QEXTMvvmItemCommand::setResult(const CommandResult& command_result)
{
    p_impl->m_result = command_result;
}
