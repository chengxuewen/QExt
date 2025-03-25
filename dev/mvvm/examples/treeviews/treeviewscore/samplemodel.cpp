// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"
#include <qextMvvmItemCatalogue.h>

using namespace ModelView;

namespace {
QExtUniquePointer<ModelView::QExtMvvmItemCatalogue> CreateItemCatalogue()
{
    auto result = qextMakeUnique<QExtMvvmItemCatalogue>();
    result->registerItem<TreeViews::MultiLayer>();
    result->registerItem<TreeViews::LayerItem>();
    result->registerItem<TreeViews::ParticleItem>();
    result->registerItem<TreeViews::LatticeItem>();
    result->registerItem<TreeViews::SphereItem>();
    result->registerItem<TreeViews::CylinderItem>();
    result->registerItem<TreeViews::AnysoPyramidItem>();
    result->registerItem<TreeViews::ShapeGroupItem>();
    return result;
}
} // namespace

namespace TreeViews {

SampleModel::SampleModel() : QExtMvvmSessionModel("SampleModel")
{
    setItemCatalogue(CreateItemCatalogue());
    populateModel();
}

//! Provides initial model content.

void SampleModel::populateModel()
{
    auto multi_layer = insertItem<MultiLayer>();
    auto layer = insertItem<LayerItem>(multi_layer);
    insertItem<ParticleItem>(layer);

    insertItem<LayerItem>(multi_layer);

    insertItem<LatticeItem>();
}

} // namespace TreeViews
