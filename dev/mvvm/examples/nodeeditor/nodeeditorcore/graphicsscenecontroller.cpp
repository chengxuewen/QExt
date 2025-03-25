// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscenecontroller.h"
#include "graphicsscene.h"
#include <qextMvvmSessionItem.h>
#include "sampleitems.h"
#include "samplemodel.h"

using namespace ModelView;

namespace NodeEditor {

GraphicsSceneController::GraphicsSceneController(SampleModel* model, GraphicsScene* scene)
    : ModelView::QExtMvvmModelListener<SampleModel>(model), m_scene(scene)
{
    setOnItemInserted([this](QExtMvvmSessionItem*, QExtMvvmTagRow) { m_scene->updateScene(); });

    auto on_about_to_remove = [this](QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow) {
        auto child = parent->getItem(tagrow.tag, tagrow.row);
        m_scene->removeViewForItem(dynamic_cast<ConnectableItem*>(child));
    };
    setOnAboutToRemoveItem(on_about_to_remove);
}

} // namespace NodeEditor
