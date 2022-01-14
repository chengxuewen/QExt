// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sampleitems.h"
#include "item_constants.h"
#include <QColor>
#include <qextMvvmComboProperty.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmItemMapper.h>
#include <qextMvvmVectorItem.h>

using namespace ModelView;

namespace TreeViews
{

MultiLayer::MultiLayer() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::MultiLayerItemType)
{
    registerTag(QEXTMvvmTagInfo::universalTag(T_LAYERS, {::QEXTMvvmConstants::LayerItemType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

LayerItem::LayerItem() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::LayerItemType)
{
    addProperty(P_THICKNESS, 42.0);
    addProperty(P_COLOR, QColor(Qt::green));
    registerTag(QEXTMvvmTagInfo::universalTag(T_PARTICLES, {::QEXTMvvmConstants::ParticleItemType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

ParticleItem::ParticleItem() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::ParticleItemType)
{
    addProperty<QEXTMvvmVectorItem>(P_POSITION);
    addProperty<ShapeGroupItem>(P_SHAPES);
}

// ----------------------------------------------------------------------------

LatticeItem::LatticeItem() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::LatticeItemType)
{
    addProperty(P_ROTATION_ANLE, 90.0);
    addProperty(P_INTEGRATION, true);

    auto combo = QEXTMvvmComboProperty::createFrom({"Default", "Square", "Hexagonal"});
    addProperty(P_LATTICE_TYPE, combo);

    update_appearance();
}

void LatticeItem::activate()
{
    auto onIntegrationFlagChange = [this](QEXTMvvmSessionItem*, std::string property) {
        if (property == P_INTEGRATION)
            update_appearance();
    };

    mapper()->setOnPropertyChange(onIntegrationFlagChange, this);
}

void LatticeItem::update_appearance()
{
    auto angle_item = getItem(P_ROTATION_ANLE);
    angle_item->setEnabled(!property<bool>(P_INTEGRATION));
}

// ----------------------------------------------------------------------------

CylinderItem::CylinderItem() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::CylinderItemType)
{
    addProperty(P_RADIUS, 8.0);
    addProperty(P_HEIGHT, 10.0);
}

// ----------------------------------------------------------------------------

SphereItem::SphereItem() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::SphereItemType)
{
    addProperty(P_RADIUS, 8.0);
}

// ----------------------------------------------------------------------------

AnysoPyramidItem::AnysoPyramidItem() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::AnysoPyramidItemType)
{
    addProperty(P_LENGTH, 8.0);
    addProperty(P_WIDTH, 9.0);
    addProperty(P_HEIGHT, 10.0);
    addProperty(P_ALPHA, 11.0);
}

// ----------------------------------------------------------------------------

ShapeGroupItem::ShapeGroupItem() : QEXTMvvmGroupItem(::QEXTMvvmConstants::ShapeGroupItemType)
{
    registerItem<CylinderItem>("Cylinder");
    registerItem<SphereItem>("Full sphere", /*make_selected*/ true);
    registerItem<AnysoPyramidItem>("Anysotropical pyramid");
    init_group();
}

} // namespace TreeViews
