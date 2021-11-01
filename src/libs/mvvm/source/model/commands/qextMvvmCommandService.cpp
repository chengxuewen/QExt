#include <qextMvvmCommandService.h>
#include <qextMvvmCopyItemCommand.h>
#include <qextMvvmInsertNewItemCommand.h>
#include <qextMvvmMoveItemCommand.h>
#include <qextMvvmRemoveItemCommand.h>
#include <qextMvvmSetValueCommand.h>

#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <stdexcept>

using namespace ModelView;

QEXTCommandService::QEXTCommandService(QEXTMvvmSessionModel* model) : m_model(model), m_pause_record(false) {}

void QEXTCommandService::setUndoRedoEnabled(bool value)
{
    if (value)
        m_commands = std::make_unique<QEXTUndoStack>();
    else
        m_commands.reset();
}

QEXTMvvmSessionItem* QEXTCommandService::insertNewItem(const item_factory_func_t& func, QEXTMvvmSessionItem* parent,
                                           const QEXTMvvmTagRow& tagrow)
{
    if (!parent)
        parent = m_model->rootItem();

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    return std::get<QEXTMvvmSessionItem*>(
        process_command<QEXTInsertNewItemCommand>(func, parent, QEXTMvvmTagRow{tagrow.tag, actual_row}));
}

QEXTMvvmSessionItem* QEXTCommandService::copyItem(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent,
                                      const QEXTMvvmTagRow& tagrow)
{
    if (!item)
        return nullptr;

    if (parent->model() != m_model)
        throw std::runtime_error(
            "QEXTCommandService::copyItem() -> Item doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    return std::get<QEXTMvvmSessionItem*>(
        process_command<QEXTCopyItemCommand>(item, parent, QEXTMvvmTagRow{tagrow.tag, actual_row}));
}

bool QEXTCommandService::setData(QEXTMvvmSessionItem* item, const QEXTMvvmVariant& value, int role)
{
    if (!item)
        return false;

    return std::get<bool>(process_command<QEXTSetValueCommand>(item, value, role));
}

void QEXTCommandService::removeItem(QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow)
{
    if (parent->model() != m_model)
        throw std::runtime_error(
            "QEXTCommandService::removeRow() -> Item doesn't belong to given model");

    process_command<QEXTRemoveItemCommand>(parent, tagrow);
}

void QEXTCommandService::moveItem(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, const QEXTMvvmTagRow& tagrow)
{
    if (item->model() != m_model)
        throw std::runtime_error(
            "QEXTCommandService::removeRow() -> Item doesn't belong to given model");

    if (new_parent->model() != m_model)
        throw std::runtime_error(
            "QEXTCommandService::removeRow() -> Parent doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? new_parent->itemCount(tagrow.tag) : tagrow.row;

    process_command<QEXTMoveItemCommand>(item, new_parent, QEXTMvvmTagRow{tagrow.tag, actual_row});
}

QEXTMvvmUndoStackInterface* QEXTCommandService::undoStack() const
{
    return m_commands.get();
}

void QEXTCommandService::setCommandRecordPause(bool value)
{
    m_pause_record = value;
}

bool QEXTCommandService::provideUndo() const
{
    return m_commands && !m_pause_record;
}
