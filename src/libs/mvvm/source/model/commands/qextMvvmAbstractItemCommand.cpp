#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <stdexcept>

using namespace ModelView;

struct QEXTAbstractItemCommand::AbstractItemCommandImpl {
    enum EStatus { INITIAL, AFTER_EXECUTE, AFTER_UNDO };
    bool is_obsolete{false};
    std::string text;
    EStatus status{INITIAL};
    QEXTMvvmSessionModel* model{nullptr};
    QEXTAbstractItemCommand* parent_impl{nullptr};
    QEXTCommandResult m_result;
    AbstractItemCommandImpl(QEXTAbstractItemCommand* parent) : parent_impl(parent) {}

    void set_after_execute() { status = AFTER_EXECUTE; }
    void set_after_undo() { status = AFTER_UNDO; }
    bool can_execute() const { return status != AFTER_EXECUTE; }
    bool can_undo() const { return status == AFTER_EXECUTE && !parent_impl->isObsolete(); }
};

QEXTAbstractItemCommand::QEXTAbstractItemCommand(QEXTMvvmSessionItem* receiver)
    : p_impl(std::make_unique<QEXTAbstractItemCommand::AbstractItemCommandImpl>(this))
{
    if (!receiver)
        throw std::runtime_error("Invalid item.");

    if (!receiver->model())
        throw std::runtime_error("Item doesn't have a model");

    p_impl->model = receiver->model();
}

QEXTAbstractItemCommand::~QEXTAbstractItemCommand() = default;

//! Execute command.

void QEXTAbstractItemCommand::execute()
{
    if (!p_impl->can_execute())
        throw std::runtime_error("Can't execute the command. Wrong order.");

    execute_command();

    p_impl->set_after_execute();
}

//! Undo command as it was before execution.

void QEXTAbstractItemCommand::undo()
{
    if (!p_impl->can_undo())
        throw std::runtime_error("Can't undo the command. Wrong order.");

    undo_command();

    p_impl->set_after_undo();
}

//! Returns whether the command is obsolete (which means that it shouldn't be kept in the stack).

bool QEXTAbstractItemCommand::isObsolete() const
{
    return p_impl->is_obsolete;
}

//! Returns command description.

std::string QEXTAbstractItemCommand::description() const
{
    return p_impl->text;
}

QEXTCommandResult QEXTAbstractItemCommand::result() const
{
    return p_impl->m_result;
}

//! Sets command obsolete flag.

void QEXTAbstractItemCommand::setObsolete(bool flag)
{
    p_impl->is_obsolete = flag;
}

//! Sets command description.

void QEXTAbstractItemCommand::setDescription(const std::string& text)
{
    p_impl->text = text;
}

QEXTMvvmPath QEXTAbstractItemCommand::pathFromItem(QEXTMvvmSessionItem* item) const
{
    return p_impl->model->pathFromItem(item);
}

QEXTMvvmSessionItem* QEXTAbstractItemCommand::itemFromPath(const QEXTMvvmPath& path) const
{
    return p_impl->model->itemFromPath(path);
}

QEXTMvvmSessionModel* QEXTAbstractItemCommand::model() const
{
    return p_impl->model;
}

void QEXTAbstractItemCommand::setResult(const QEXTCommandResult& command_result)
{
    p_impl->m_result = command_result;
}
