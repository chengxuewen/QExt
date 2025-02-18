// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialpropertycontroller.h"
#include "materialmodel.h"
#include "samplemodel.h"
#include "model/model/externalproperty.h"
#include "model/model/modelutils.h"

using namespace ModelView;

MaterialPropertyController::MaterialPropertyController(MaterialModel* material_model,
                                                       SampleModel* sample_model)
    : ModelListener(material_model), m_sample_model(sample_model)
{
    setOnDataChange([this](SessionItem*, int) { update_all(); });
    setOnItemInserted([this](SessionItem* item, TagRow tagrow) { update_all(); });
    setOnItemRemoved([this](SessionItem* item, TagRow tagrow) { update_all(); });
    setOnModelReset([this](SessionModel*) { update_all(); });
    update_all();
}

//! Updates all material properties in LayerItems to get new material colors and labels.

void MaterialPropertyController::update_all()
{
    for (auto layer : Utils::FindItems<LayerItem>(m_sample_model)) {
        auto property = layer->property<ExternalProperty>(LayerItem::P_MATERIAL);
        auto updated = model()->material_property(property.identifier());
        if (property != updated)
            layer->setProperty(LayerItem::P_MATERIAL, updated);
    }
}
