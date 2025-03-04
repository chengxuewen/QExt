// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

// #include "model/commands/abstractitemcommand.h"
#include <qextMvvmAbstractItemCommand.h>
#include "model/model/modelutils.h"
#include "model/model/path.h"
#include "model/model/sessionitem.h"
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmAbstractItemCommand::AbstractItemCommandImpl {
    enum class Status { initial, after_execute, after_undo };
    bool m_isObsolete{false};
    std::string m_text;
    Status m_status{Status::initial};
    QExtMvvmSessionModel* m_model{nullptr};
    QExtMvvmAbstractItemCommand* m_self{nullptr};
    QExtMvvmCommandResult m_result;
    AbstractItemCommandImpl(QExtMvvmAbstractItemCommand* parent) : m_self(parent) {}

    void set_after_execute() { m_status = Status::after_execute; }
    void set_after_undo() { m_status = Status::after_undo; }
    bool can_execute() const { return m_status != Status::after_execute; }
    bool can_undo() const { return m_status == Status::after_execute && !m_self->isObsolete(); }
};

QExtMvvmAbstractItemCommand::QExtMvvmAbstractItemCommand(QExtMvvmSessionItem* receiver)
    : p_impl(qextMakeUnique<QExtMvvmAbstractItemCommand::AbstractItemCommandImpl>(this))
{
    if (!receiver)
        throw std::runtime_error("Invalid item.");

    if (!receiver->model())
        throw std::runtime_error("Item doesn't have a model");

    p_impl->m_model = receiver->model();
}

QExtMvvmAbstractItemCommand::~QExtMvvmAbstractItemCommand() = default;

//! Execute command.

void QExtMvvmAbstractItemCommand::execute()
{
    if (!p_impl->can_execute())
        throw std::runtime_error("Can't execute the command. Wrong order.");

    execute_command();

    p_impl->set_after_execute();
}

//! Undo command as it was before execution.

void QExtMvvmAbstractItemCommand::undo()
{
    if (!p_impl->can_undo())
        throw std::runtime_error("Can't undo the command. Wrong order.");

    undo_command();

    p_impl->set_after_undo();
}

//! Returns whether the command is obsolete (which means that it shouldn't be kept in the stack).

bool QExtMvvmAbstractItemCommand::isObsolete() const
{
    return p_impl->m_isObsolete;
}

//! Returns command description.

std::string QExtMvvmAbstractItemCommand::description() const
{
    return p_impl->m_text;
}

QExtMvvmCommandResult QExtMvvmAbstractItemCommand::result() const
{
    return p_impl->m_result;
}

//! Sets command obsolete flag.

void QExtMvvmAbstractItemCommand::setObsolete(bool flag)
{
    p_impl->m_isObsolete = flag;
}

//! Sets command description.

void QExtMvvmAbstractItemCommand::setDescription(const std::string& text)
{
    p_impl->m_text = text;
}

QExtMvvmPath QExtMvvmAbstractItemCommand::pathFromItem(QExtMvvmSessionItem* item) const
{
    return Utils::PathFromItem(item);
}

QExtMvvmSessionItem* QExtMvvmAbstractItemCommand::itemFromPath(const QExtMvvmPath& path) const
{
    return Utils::ItemFromPath(*p_impl->m_model, path);
}

QExtMvvmSessionModel* QExtMvvmAbstractItemCommand::model() const
{
    return p_impl->m_model;
}

void QExtMvvmAbstractItemCommand::setResult(const QExtMvvmCommandResult& command_result)
{
    p_impl->m_result = command_result;
}
