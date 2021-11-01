#include <QJsonObject>
#include <qextMvvmUndoStackInterface.h>
#include <qextMvvmModelUtils.h>

using namespace ModelView;

void Utils::PopulateEmptyModel(const QEXTMvvmJsonModelConverterInterface* converter, const QEXTMvvmSessionModel& source, QEXTMvvmSessionModel& target)
{
    QJsonObject object = converter->to_json(source);
    converter->from_json(object, target);
}

void Utils::DeleteItemFromModel(QEXTMvvmSessionItem* item)
{
    auto model = item->model();
    if (!model)
        return;

    model->removeItem(item->parent(), item->tagRow());
}

void Utils::MoveUp(QEXTMvvmSessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == 0)
        return; // item already at the top
    item->model()->moveItem(item, item->parent(), tagrow.prev());
}

void Utils::MoveDown(QEXTMvvmSessionItem* item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == item->parent()->itemCount(tagrow.tag) - 1)
        return; // item already at the buttom
    item->model()->moveItem(item, item->parent(), tagrow.next());
}

void Utils::Undo(QEXTMvvmSessionModel& model)
{
    if (auto stack = model.undoStack(); stack)
        stack->undo();
}

void Utils::Redo(QEXTMvvmSessionModel& model)
{
    if (auto stack = model.undoStack(); stack)
        stack->redo();
}

void Utils::BeginMacros(const QEXTMvvmSessionItem* item, const std::string& macro_name)
{
    if (!item->model())
        return;

    if (auto stack = item->model()->undoStack(); stack)
        stack->beginMacro(macro_name);
}

void Utils::EndMacros(const QEXTMvvmSessionItem* item)
{
    if (!item->model())
        return;

    if (auto stack = item->model()->undoStack(); stack)
        stack->endMacro();
}
