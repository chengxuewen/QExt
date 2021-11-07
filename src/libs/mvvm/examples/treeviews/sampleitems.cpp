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
#include <qextMvvmUtils.h>



namespace TreeViews
{

    MultiLayer::MultiLayer() : QEXTMvvmCompoundItem(::Constants::MultiLayerItemType)
    {
        registerTag(QEXTMvvmTagInfo::universalTag(T_LAYERS, {::Constants::LayerItemType}),
                    /*set_as_default*/ true);
    }

// ----------------------------------------------------------------------------

    LayerItem::LayerItem() : QEXTMvvmCompoundItem(::Constants::LayerItemType)
    {
        addProperty(P_THICKNESS, 42.0);
        addProperty(P_COLOR, QColor(Qt::green));
        registerTag(QEXTMvvmTagInfo::universalTag(T_PARTICLES, {::Constants::ParticleItemType}),
                    /*set_as_default*/ true);
    }

// ----------------------------------------------------------------------------

    ParticleItem::ParticleItem() : QEXTMvvmCompoundItem(::Constants::ParticleItemType)
    {
        addProperty<QEXTMvvmVectorItem>(P_POSITION);
        addProperty<ShapeGroupItem>(P_SHAPES);
    }

// ----------------------------------------------------------------------------

    LatticeItem::LatticeItem() : QEXTMvvmCompoundItem(::Constants::LatticeItemType)
    {
        addProperty(P_ROTATION_ANLE, 90.0);
        addProperty(P_INTEGRATION, true);

        auto combo = QEXTMvvmComboProperty::createFrom({"Default", "Square", "Hexagonal"});
        addProperty(P_LATTICE_TYPE, combo);

        update_appearance();
    }

    void LatticeItem::activate()
    {
        auto onIntegrationFlagChange = [this](QEXTMvvmItem *, QString property)
        {
            if (property == P_INTEGRATION)
            {
                update_appearance();
            }
        };

        mapper()->addItemPropertyChangedListener(onIntegrationFlagChange, this);
    }

    void LatticeItem::update_appearance()
    {
        auto angle_item = this->item(P_ROTATION_ANLE);
        angle_item->setEnabled(!property<bool>(P_INTEGRATION));
    }

// ----------------------------------------------------------------------------

    CylinderItem::CylinderItem() : QEXTMvvmCompoundItem(::Constants::CylinderItemType)
    {
        addProperty(P_RADIUS, 8.0);
        addProperty(P_HEIGHT, 10.0);
    }

// ----------------------------------------------------------------------------

    SphereItem::SphereItem() : QEXTMvvmCompoundItem(::Constants::SphereItemType)
    {
        addProperty(P_RADIUS, 8.0);
    }

// ----------------------------------------------------------------------------

    AnysoPyramidItem::AnysoPyramidItem() : QEXTMvvmCompoundItem(::Constants::AnysoPyramidItemType)
    {
        addProperty(P_LENGTH, 8.0);
        addProperty(P_WIDTH, 9.0);
        addProperty(P_HEIGHT, 10.0);
        addProperty(P_ALPHA, 11.0);
    }

// ----------------------------------------------------------------------------

    ShapeGroupItem::ShapeGroupItem() : QEXTMvvmGroupItem(::Constants::ShapeGroupItemType)
    {
        registerItem<CylinderItem>("Cylinder");
        registerItem<SphereItem>("Full sphere", /*make_selected*/ true);
        registerItem<AnysoPyramidItem>("Anysotropical pyramid");
        initGroup();
    }

} // namespace TreeViews
