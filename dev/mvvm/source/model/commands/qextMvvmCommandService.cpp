// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCommandService.h>
#include <qextMvvmCommands.h>
// #include "model/commands/commandservice.h"
// #include "model/commands/copyitemcommand.h"
// #include "model/commands/insertnewitemcommand.h"
// #include "model/commands/moveitemcommand.h"
// #include "model/commands/removeitemcommand.h"
// #include "model/commands/setvaluecommand.h"
#include <qextMvvmUndoStack.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <stdexcept>

using namespace ModelView;

QExtMvvmCommandService::QExtMvvmCommandService(QExtMvvmSessionModel* model) : m_model(model), m_pause_record(false) {}

void QExtMvvmCommandService::setUndoRedoEnabled(bool value)
{
    if (value)
        m_commands = qextMakeUnique<QExtMvvmUndoStack>();
    else
        m_commands.reset();
}

QExtMvvmSessionItem* QExtMvvmCommandService::insertNewItem(const QExtMvvmItemFactoryFunc& func, QExtMvvmSessionItem* parent,
                                           const QExtMvvmTagRow& tagrow)
{
    if (!parent)
        parent = m_model->rootItem();

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    return qextVariantGet<QExtMvvmSessionItem*>(process_command<QExtMvvmInsertNewItemCommand>(func, parent, QExtMvvmTagRow{tagrow.tag, actual_row}));
}

QExtMvvmSessionItem* QExtMvvmCommandService::copyItem(const QExtMvvmSessionItem* item, QExtMvvmSessionItem* parent,
                                      const QExtMvvmTagRow& tagrow)
{
    if (!item)
        return nullptr;

    if (parent->model() != m_model)
        throw std::runtime_error(
            "QExtMvvmCommandService::copyItem() -> Item doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? parent->itemCount(tagrow.tag) : tagrow.row;

    return qextVariantGet<QExtMvvmSessionItem*>(
        process_command<QExtMvvmCopyItemCommand>(item, parent, QExtMvvmTagRow{tagrow.tag, actual_row}));
}

bool QExtMvvmCommandService::setData(QExtMvvmSessionItem* item, const QVariant& value, int role)
{
    if (!item)
        return false;

    return qextVariantGet<bool>(process_command<QExtMvvmSetValueCommand>(item, value, role));
}

void QExtMvvmCommandService::removeItem(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow)
{
    if (parent->model() != m_model)
        throw std::runtime_error(
            "QExtMvvmCommandService::removeRow() -> Item doesn't belong to given model");

    process_command<RemoveItemCommand>(parent, tagrow);
}

void QExtMvvmCommandService::moveItem(QExtMvvmSessionItem* item, QExtMvvmSessionItem* new_parent, const QExtMvvmTagRow& tagrow)
{
    if (item->model() != m_model)
        throw std::runtime_error(
            "QExtMvvmCommandService::removeRow() -> Item doesn't belong to given model");

    if (new_parent->model() != m_model)
        throw std::runtime_error(
            "QExtMvvmCommandService::removeRow() -> Parent doesn't belong to given model");

    int actual_row = tagrow.row < 0 ? new_parent->itemCount(tagrow.tag) : tagrow.row;

    process_command<QExtMvvmMoveItemCommand>(item, new_parent, QExtMvvmTagRow{tagrow.tag, actual_row});
}

QExtMvvmUndoStackInterface* QExtMvvmCommandService::undoStack() const
{
    return m_commands.get();
}

void QExtMvvmCommandService::setCommandRecordPause(bool value)
{
    m_pause_record = value;
}

bool QExtMvvmCommandService::provideUndo() const
{
    return m_commands && !m_pause_record;
}
