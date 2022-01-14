// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmCommandService.h>
#include <commands/qextMvvmCopyItemCommand.h>
#include <commands/qextMvvmInsertNewItemCommand.h>
#include <commands/qextMvvmMoveItemCommand.h>
#include <commands/qextMvvmRemoveItemCommand.h>
#include <commands/qextMvvmSetValueCommand.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <stdexcept>

using namespace ModelView;

QEXTMvvmCommandService::QEXTMvvmCommandService(QEXTMvvmSessionModel* model) : m_model(model), m_pause_record(false) {}

void QEXTMvvmCommandService::setUndoRedoEnabled(bool value)
{
    if (value)
        m_commands = make_unique<QEXTMvvmUndoStack>();
    else
        m_commands.reset();
}

QEXTMvvmSessionItem* QEXTMvvmCommandService::insertNewItem(const item_factory_func_t& func, QEXTMvvmSessionItem* parent,
                                           const QEXTMvvmTagRow& tagrow)
{
    if (!parent)
        parent = m_model->rootItem();

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

//    return std::get<QEXTMvvmSessionItem*>(
//        process_command<QEXTMvvmInsertNewItemCommand>(func, parent, QEXTMvvmTagRow{tagrow.tag, actual_row}));
    return process_command<QEXTMvvmInsertNewItemCommand>(func, parent, QEXTMvvmTagRow{tagrow.tag, actual_row}).item();
}

QEXTMvvmSessionItem* QEXTMvvmCommandService::copyItem(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent,
                                      const QEXTMvvmTagRow& tagrow)
{
    if (!item)
        return nullptr;

    if (parent->model() != m_model)
        throw std::runtime_error(
            "QEXTMvvmCommandService::copyItem() -> Item doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    return process_command<QEXTMvvmCopyItemCommand>(item, parent, QEXTMvvmTagRow{tagrow.tag, actual_row}).item();
}

bool QEXTMvvmCommandService::setData(QEXTMvvmSessionItem* item, const QVariant& value, int role)
{
    if (!item)
        return false;

    return process_command<QEXTMvvmSetValueCommand>(item, value, role).success();
}

void QEXTMvvmCommandService::removeItem(QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow)
{
    if (parent->model() != m_model)
        throw std::runtime_error(
            "QEXTMvvmCommandService::removeRow() -> Item doesn't belong to given model");

    process_command<QEXTMvvmRemoveItemCommand>(parent, tagrow);
}

void QEXTMvvmCommandService::moveItem(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, const QEXTMvvmTagRow& tagrow)
{
    if (item->model() != m_model)
        throw std::runtime_error(
            "QEXTMvvmCommandService::removeRow() -> Item doesn't belong to given model");

    if (new_parent->model() != m_model)
        throw std::runtime_error(
            "QEXTMvvmCommandService::removeRow() -> Parent doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? new_parent->itemCount(tagrow.tag) : tagrow.row;

    process_command<QEXTMvvmMoveItemCommand>(item, new_parent, QEXTMvvmTagRow{tagrow.tag, actual_row});
}

QEXTMvvmUndoStackInterface* QEXTMvvmCommandService::undoStack() const
{
    return m_commands.get();
}

void QEXTMvvmCommandService::setCommandRecordPause(bool value)
{
    m_pause_record = value;
}

bool QEXTMvvmCommandService::provideUndo() const
{
    return m_commands && !m_pause_record;
}
