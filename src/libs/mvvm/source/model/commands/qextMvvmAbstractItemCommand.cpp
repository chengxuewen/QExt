#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmAbstractItemCommand_p.h>
#include <qextMvvmPath.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <stdexcept>


QEXTMvvmAbstractItemCommandPrivate::QEXTMvvmAbstractItemCommandPrivate(QEXTMvvmAbstractItemCommand *q)
    : q_ptr(q)
    , m_isObsolete(false)
    , m_status(Status_Initial)
    , m_model(QEXT_DECL_NULLPTR)
{

}

QEXTMvvmAbstractItemCommandPrivate::~QEXTMvvmAbstractItemCommandPrivate()
{

}

void QEXTMvvmAbstractItemCommandPrivate::setAfterExecute()
{
    m_status = Status_AfterExecute;
}

void QEXTMvvmAbstractItemCommandPrivate::setAfterUndo()
{
    m_status = Status_AfterUndo;
}

bool QEXTMvvmAbstractItemCommandPrivate::canExecute() const
{
    return m_status != Status_AfterExecute;
}

bool QEXTMvvmAbstractItemCommandPrivate::canUndo() const
{
    return m_status == Status_AfterExecute && !m_isObsolete;
}




QEXTMvvmAbstractItemCommand::QEXTMvvmAbstractItemCommand(QEXTMvvmItem *receiver)
    : d_ptr(new QEXTMvvmAbstractItemCommandPrivate(this))
{
    if (!receiver)
    {
        throw std::runtime_error("Invalid item.");
    }

    if (!receiver->model())
    {
        throw std::runtime_error("Item doesn't have a model");
    }

    d_ptr->m_model = receiver->model();
}

QEXTMvvmAbstractItemCommand::~QEXTMvvmAbstractItemCommand()
{

}

//! Execute command.

void QEXTMvvmAbstractItemCommand::execute()
{
    if (!d_ptr->canExecute())
    {
        throw std::runtime_error("Can't execute the command. Wrong order.");
    }

    this->executeCommand();
    d_ptr->setAfterExecute();
}

//! Undo command as it was before execution.

void QEXTMvvmAbstractItemCommand::undo()
{
    if (!d_ptr->canUndo())
    {
        throw std::runtime_error("Can't undo the command. Wrong order.");
    }

    this->undoCommand();
    d_ptr->setAfterUndo();
}

//! Returns whether the command is obsolete (which means that it shouldn't be kept in the stack).

bool QEXTMvvmAbstractItemCommand::isObsolete() const
{
    return d_ptr->m_isObsolete;
}

//! Returns command description.

QString QEXTMvvmAbstractItemCommand::description() const
{
    return d_ptr->m_text;
}

QEXTMvvmCommandResult QEXTMvvmAbstractItemCommand::result() const
{
    return d_ptr->m_result;
}

QEXTMvvmAbstractItemCommand::QEXTMvvmAbstractItemCommand(QEXTMvvmAbstractItemCommandPrivate *d,
                                                         QEXTMvvmItem *receiver)
    : d_ptr(d)
{
    if (!receiver)
    {
        throw std::runtime_error("Invalid item.");
    }

    if (!receiver->model())
    {
        throw std::runtime_error("Item doesn't have a model");
    }

    d_ptr->m_model = receiver->model();
}

//! Sets command obsolete flag.

void QEXTMvvmAbstractItemCommand::setObsolete(bool flag)
{
    d_ptr->m_isObsolete = flag;
}

//! Sets command description.

void QEXTMvvmAbstractItemCommand::setDescription(const QString &text)
{
    d_ptr->m_text = text;
}

QEXTMvvmPath QEXTMvvmAbstractItemCommand::pathFromItem(QEXTMvvmItem *item) const
{
    return d_ptr->m_model->pathFromItem(item);
}

QEXTMvvmItem *QEXTMvvmAbstractItemCommand::itemFromPath(const QEXTMvvmPath &path) const
{
    return d_ptr->m_model->itemFromPath(path);
}

QEXTMvvmModel *QEXTMvvmAbstractItemCommand::model() const
{
    return d_ptr->m_model;
}

void QEXTMvvmAbstractItemCommand::setResult(const QEXTMvvmCommandResult &result)
{
    d_ptr->m_result = result;
}
