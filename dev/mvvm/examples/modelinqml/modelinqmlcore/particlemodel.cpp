// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "particlemodel.h"
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmVectorItem.h>

using namespace ModelView;

namespace
{

//! Constants to define toy items.
const std::string ParticleType = "Particle";
const std::string CylinderType = "Cylinder";
const std::string SphereType = "Sphere";
const std::string AnysoPyramidType = "AnysoPyramid";
const std::string ShapeGroupType = "ShapeGroup";

QExtUniquePointer<ModelView::QExtMvvmItemCatalogue> CreateItemCatalogue()
{
    auto result = qextMakeUnique<QExtMvvmItemCatalogue>();
    result->registerItem<ParticleItem>();
    result->registerItem<SphereItem>();
    result->registerItem<CylinderItem>();
    result->registerItem<AnysoPyramidItem>();
    result->registerItem<ShapeGroupItem>();
    return result;
}

} // namespace

ParticleItem::ParticleItem() : QExtMvvmCompoundItem(ParticleType)
{
//    addProperty<QExtMvvmVectorItem>(P_POSITION);
//    addProperty<ShapeGroupItem>(P_SHAPES);
    addProperty("Radius", 42.0);
    addProperty("Height", 10.0);
    addProperty("Alpha", 11.0);
}

CylinderItem::CylinderItem() : QExtMvvmCompoundItem(CylinderType)
{
    addProperty(P_RADIUS, 8.0);
    addProperty(P_HEIGHT, 10.0);
}

SphereItem::SphereItem() : QExtMvvmCompoundItem(SphereType)
{
    addProperty(P_RADIUS, 8.0);
}

AnysoPyramidItem::AnysoPyramidItem() : QExtMvvmCompoundItem(AnysoPyramidType)
{
    addProperty(P_LENGTH, 8.0);
    addProperty(P_WIDTH, 9.0);
    addProperty(P_HEIGHT, 10.0);
    addProperty(P_ALPHA, 11.0);
}

ShapeGroupItem::ShapeGroupItem() : QExtMvvmGroupItem(ShapeGroupType)
{
    addToGroup<CylinderItem>("Cylinder");
    addToGroup<SphereItem>("Full sphere", /*make_selected*/ true);
    addToGroup<AnysoPyramidItem>("Anysotropical pyramid");
}

//! ---------------------------------------------------------------------------

ParticleModel::ParticleModel() : QExtMvvmSessionModel("ParticleModel")
{
    setItemCatalogue(CreateItemCatalogue());
    insertItem<ParticleItem>();
}
