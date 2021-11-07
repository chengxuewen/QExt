#include <qextMvvmCommandService.h>
#include <qextMvvmCommandService_p.h>
#include <qextMvvmCopyItemCommand.h>
#include <qextMvvmInsertNewItemCommand.h>
#include <qextMvvmMoveItemCommand.h>
#include <qextMvvmRemoveItemCommand.h>
#include <qextMvvmSetValueCommand.h>

#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <stdexcept>


QEXTMvvmCommandServicePrivate::QEXTMvvmCommandServicePrivate(QEXTMvvmCommandService *q)
    : q_ptr(q)
    , m_model(QEXT_DECL_NULLPTR)
    , m_pauseRecord(false)
{

}

QEXTMvvmCommandServicePrivate::~QEXTMvvmCommandServicePrivate()
{

}




QEXTMvvmCommandService::QEXTMvvmCommandService(QEXTMvvmModel *model)
    : d_ptr(new QEXTMvvmCommandServicePrivate(this))
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    d->m_model = model;
}

QEXTMvvmCommandService::~QEXTMvvmCommandService()
{

}

void QEXTMvvmCommandService::setUndoRedoEnabled(bool value)
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    if (value)
    {
        d->m_commands.reset(new QEXTMvvmUndoStack);
    }
    else
    {
        d->m_commands.reset();
    }
}

QEXTMvvmItem *QEXTMvvmCommandService::insertNewItem(const QEXTMvvmItemFactoryFunction &func,
                                                    QEXTMvvmItem *parent,
                                                    const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    if (!parent)
    {
        parent = d->m_model->rootItem();
    }

    int actualRow = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    QEXTMvvmCommandResult result = this->processCommand<QEXTMvvmInsertNewItemCommand>(func, parent, QEXTMvvmTagRow(tagrow.tag, actualRow));
    return result.resultItem();
}

QEXTMvvmItem *QEXTMvvmCommandService::copyItem(QEXTMvvmItem *item, QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    if (!item)
    {
        return QEXT_DECL_NULLPTR;
    }

    if (parent->model() != d->m_model)
    {
        throw std::runtime_error("QEXTMvvmCommandService::copyItem() -> Item doesn't belong to given model");
    }

    int actualRow = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    QEXTMvvmCommandResult result = this->processCommand<QEXTMvvmCopyItemCommand>(item, parent, QEXTMvvmTagRow(tagrow.tag, actualRow));
    return result.resultItem();
}

bool QEXTMvvmCommandService::setData(QEXTMvvmItem *item, const QVariant &value, int role)
{
    if (!item)
    {
        return false;
    }

    QEXTMvvmCommandResult result = this->processCommand<QEXTMvvmSetValueCommand>(item, value, role);
    return result.resultValue();
}

void QEXTMvvmCommandService::removeItem(QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    if (parent->model() != d->m_model)
    {
        throw std::runtime_error("QEXTMvvmCommandService::removeRow() -> Item doesn't belong to given model");
    }

    this->processCommand<QEXTMvvmRemoveItemCommand>(parent, tagrow);
}

void QEXTMvvmCommandService::moveItem(QEXTMvvmItem *item, QEXTMvvmItem *newParent, const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    if (item->model() != d->m_model)
    {
        throw std::runtime_error("QEXTMvvmCommandService::removeRow() -> Item doesn't belong to given model");
    }

    if (newParent->model() != d->m_model)
    {
        throw std::runtime_error("QEXTMvvmCommandService::removeRow() -> Parent doesn't belong to given model");
    }

    int actualRow = tagrow.row < 0 ? newParent->itemCount(tagrow.tag) : tagrow.row;
    this->processCommand<QEXTMvvmMoveItemCommand>(item, newParent, QEXTMvvmTagRow(tagrow.tag, actualRow));
}

QEXTMvvmUndoStackInterface *QEXTMvvmCommandService::undoStack() const
{
    QEXT_DECL_DC(QEXTMvvmCommandService);
    return d->m_commands.data();
}

void QEXTMvvmCommandService::setCommandRecordPause(bool value)
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    d->m_pauseRecord = value;
}

bool QEXTMvvmCommandService::provideUndo() const
{
    QEXT_DECL_DC(QEXTMvvmCommandService);
    return d->m_commands && !d->m_pauseRecord;
}

void QEXTMvvmCommandService::execute(const QSharedPointer<QEXTMvvmAbstractItemCommand> &command)
{
    QEXT_DECL_D(QEXTMvvmCommandService);
    d->m_commands->execute(command);
}
