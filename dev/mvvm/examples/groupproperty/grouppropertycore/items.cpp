// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "items.h"
#include "model/standarditems/vectoritem.h"
#include <QColor>

namespace GroupProperty {

UndefinedShapeItem::UndefinedShapeItem() : ModelView::QExtMvvmCompoundItem("Undefined")
{
    // no properties
}

SphereItem::SphereItem() : ModelView::QExtMvvmCompoundItem("Sphere")
{
    addProperty("Radius", 5.0);
}

CylinderItem::CylinderItem() : ModelView::QExtMvvmCompoundItem("Cylinder")
{
    addProperty("Radius", 8.0);
    addProperty("Height", 10.0);
}

BoxItem::BoxItem() : ModelView::QExtMvvmCompoundItem("Box")
{
    addProperty("Length", 12.0);
    addProperty("Width", 6.0);
    addProperty("Height", 3.0);
}

ShapeGroupItem::ShapeGroupItem() : ModelView::QExtMvvmGroupItem("Shape")
{
    addToGroup<UndefinedShapeItem>();
    addToGroup<SphereItem>();
    addToGroup<CylinderItem>();
    addToGroup<BoxItem>();
}

ParticleItem::ParticleItem() : ModelView::QExtMvvmCompoundItem("Particle")
{
    addProperty("Color", QColor(Qt::green));
    addProperty<ShapeGroupItem>("Shape");
    addProperty<ModelView::QExtMvvmVectorItem>("Position");
}

Model::Model()
{
    // register custom item to use with the model
    registerItem<ParticleItem>();
}

} // namespace GroupProperty
