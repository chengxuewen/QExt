// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mousemodel.h"
#include <QColor>
#include <algorithm>
#include <cmath>

#include <qextMvvmModelDocumentInterface.h>
#include <qextMvvmUndoStackInterface.h>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmRealLimits.h>
#include <qextMvvmFactory.h>
#include <qextMvvmWidgetUtils.h>

namespace
{
static const int MouseCount = 7;

QEXTMvvmItemCatalogue *qextMvvmCreateItemCatalogue()
{
    QEXTMvvmItemCatalogue *result = new QEXTMvvmItemCatalogue;
    result->registerItem<MouseItem>();
    return result;
}

} // namespace

MouseItem::MouseItem() : QEXTMvvmCompoundItem("MouseItem")
{
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(P_XPOS, 0.0)->setLimits(QEXTMvvmRealLimits::limitless())->setDisplayName("X");
    addProperty(P_YPOS, 0.0)->setLimits(QEXTMvvmRealLimits::limitless())->setDisplayName("Y");
    addProperty(P_ANGLE, 0.0)
        ->setLimits(QEXTMvvmRealLimits::limitless())
        ->setDisplayName("Angle of yaw");
    addProperty(P_SPEED, 0.0)
        ->setLimits(QEXTMvvmRealLimits::limitless())
        ->setDisplayName("Speed");
}

// ----------------------------------------------------------------------------

MouseModel::MouseModel() : QEXTMvvmModel("MouseModel")
{
    setItemCatalogue(qextMvvmCreateItemCatalogue());
    populate_model();

    setUndoRedoEnabled(true);
    const int max_commands_to_keep = 1000;
    undoStack()->setUndoLimit(max_commands_to_keep);
}

void MouseModel::readFromFile(const QString &name)
{
    auto document = QEXTMvvmFactory::createModelDocument({this});
    document->load(name);
}

void MouseModel::writeToFile(const QString &name)
{
    auto document = QEXTMvvmFactory::createModelDocument({this});
    document->save(name);
}

void MouseModel::setUndoPosition(int value)
{
    int desired_command_id = undoStack()->count() * qextClamp(value, 0, 100) / 100;

    if (undoStack()->index() < desired_command_id) {
        while (undoStack()->index() != desired_command_id)
            undoStack()->redo(); // going forward
    } else {
        while (undoStack()->index() != desired_command_id)
            undoStack()->undo(); // going back in time
    }
}

void MouseModel::populate_model()
{
    for (int i = 0; i < MouseCount; ++i) {
        auto item = insertItem<MouseItem>();
        item->setProperty(MouseItem::P_XPOS, std::sin((i * 6.28) / MouseCount) * 200);
        item->setProperty(MouseItem::P_YPOS, std::cos((i * 6.28) / MouseCount) * 200);
        item->setProperty(MouseItem::P_COLOR, QEXTMvvmWidgetUtils::RandomColor());
    }
}
