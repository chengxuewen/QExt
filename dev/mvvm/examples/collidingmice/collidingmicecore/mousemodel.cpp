// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mousemodel.h"
#include <qextMvvmModelDocumentFactory.h>
#include <qextMvvmUndoStackInterface.h>
#include <qextMvvmWidgetUtils.h>
#include <QColor>
#include <qextMath.h>
#include <cmath>

namespace {
const int MouseCount = 7;
} // namespace

MouseItem::MouseItem() : ModelView::QExtMvvmCompoundItem("MouseItem")
{
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(P_XPOS, 0.0)->setDisplayName("X");
    addProperty(P_YPOS, 0.0)->setDisplayName("Y");
    addProperty(P_ANGLE, 0.0)->setDisplayName("Angle of yaw");
    addProperty(P_SPEED, 0.0)->setDisplayName("Speed");
}

// ----------------------------------------------------------------------------

MouseModel::MouseModel() : ModelView::QExtMvvmSessionModel("MouseModel")
{
    registerItem<MouseItem>();
    populateModel();
    setUndoRedoEnabled(true);
    const int max_commands_to_keep = 1000;
    undoStack()->setUndoLimit(max_commands_to_keep);
}

void MouseModel::loadFromFile(const QString& name)
{
    auto document = ModelView::qextMvvmCreateJsonDocument({this});
    document->load(name.toStdString());
}

void MouseModel::saveToFile(const QString& name)
{
    auto document = ModelView::qextMvvmCreateJsonDocument({this});
    document->save(name.toStdString());
}

void MouseModel::setUndoPosition(int value)
{
    int desired_command_id = undoStack()->count() * qextClamp(value, 0, 100) / 100;

    if (undoStack()->index() < desired_command_id) {
        while (undoStack()->index() != desired_command_id)
            undoStack()->redo(); // going forward
    }
    else {
        while (undoStack()->index() != desired_command_id)
            undoStack()->undo(); // going back in time
    }
}

void MouseModel::populateModel()
{
    for (int i = 0; i < MouseCount; ++i) {
        auto item = insertItem<MouseItem>();
        item->setProperty(MouseItem::P_XPOS, std::sin((i * 6.28) / MouseCount) * 200);
        item->setProperty(MouseItem::P_YPOS, std::cos((i * 6.28) / MouseCount) * 200);
        item->setProperty(MouseItem::P_COLOR, ModelView::Utils::RandomColor());
    }
}
