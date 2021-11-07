// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialmodel.h"
#include "materialpropertycontroller.h"
#include "samplemodel.h"
#include <qextMvvmExternalProperty.h>
#include <qextMvvmUtils.h>
#include <qextMvvmModelMapper.h>



MaterialPropertyController::MaterialPropertyController(MaterialModel* material_model,
                                                       SampleModel* sample_model)
    : QEXTMvvmModelListener(material_model), m_sample_model(sample_model)
{
    addItemDataChangedListener([this](auto, auto) { update_all(); });
    addItemInsertedListener([this](auto, auto) { update_all(); });
    addItemRemovedListener([this](auto, auto) { update_all(); });
    addModelResetedListener([this](auto) { update_all(); });
    update_all();
}

//! Updates all material properties in LayerItems to get new material colors and labels.

void MaterialPropertyController::update_all()
{
    for (auto layer : QEXTMvvmUtils::FindItems<LayerItem>(m_sample_model)) {
        auto property = layer->property<QEXTMvvmExternalProperty>(LayerItem::P_MATERIAL);
        auto updated = model()->material_property(property.identifier());
        if (property != updated)
            layer->setProperty(LayerItem::P_MATERIAL, updated);
    }
}
