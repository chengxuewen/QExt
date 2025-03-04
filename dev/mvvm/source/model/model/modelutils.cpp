// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/modelutils.h"
#include "model/interfaces/undostackinterface.h"
#include "model/model/path.h"
#include <QJsonObject>

using namespace ModelView;

QExtMvvmPath Utils::PathFromItem(const QExtMvvmSessionItem* item)
{
    if (!item || !item->model())
        return {};

    QExtMvvmPath result;
    const QExtMvvmSessionItem* current(item);
    while (current && current->parent()) {
        result.prepend(Utils::IndexOfChild(current->parent(), current));
        current = current->parent();
    }
    return result;
}

QExtMvvmSessionItem* Utils::ItemFromPath(const QExtMvvmSessionModel& model, const QExtMvvmPath& path)
{
    QExtMvvmSessionItem* result(model.rootItem());
    for (const auto& x : path) {
        result = Utils::ChildAt(result, x);
        if (!result)
            break;
    }
    return result;
}

void Utils::PopulateEmptyModel(const QExtMvvmJsonModelConverterInterface* converter,
                               const QExtMvvmSessionModel& source, QExtMvvmSessionModel& target)
{
    QJsonObject object = converter->to_json(source);
    converter->from_json(object, target);
}

void Utils::DeleteItemFromModel(QExtMvvmSessionItem* item)
{
    auto model = item->model();
    if (!model)
        return;

    model->removeItem(item->parent(), item->tagRow());
}

void Utils::MoveUp(QExtMvvmSessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == 0)
        return; // item already at the top
    item->model()->moveItem(item, item->parent(), tagrow.prev());
}

void Utils::MoveDown(QExtMvvmSessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == item->parent()->itemCount(tagrow.tag) - 1)
        return; // item already at the buttom
    item->model()->moveItem(item, item->parent(), tagrow.next());
}

void Utils::Undo(QExtMvvmSessionModel& model)
{
    if (auto stack = model.undoStack(); stack)
        stack->undo();
}

void Utils::Redo(QExtMvvmSessionModel& model)
{
    if (auto stack = model.undoStack(); stack)
        stack->redo();
}

void Utils::BeginMacros(const QExtMvvmSessionItem* item, const std::string& macro_name)
{
    if (!item)
        return;
    BeginMacros(item->model(), macro_name);
}

void Utils::EndMacros(const QExtMvvmSessionItem* item)
{
    if (!item)
        return;
    EndMacros(item->model());
}

void Utils::BeginMacros(const QExtMvvmSessionModel* model, const std::string& macro_name)
{
    if (!model)
        return;
    if (auto stack = model->undoStack(); stack)
        stack->beginMacro(macro_name);
}

void Utils::EndMacros(const QExtMvvmSessionModel* model)
{
    if (!model)
        return;
    if (auto stack = model->undoStack(); stack)
        stack->endMacro();
}
