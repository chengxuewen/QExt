// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <layereditorcore/materialmodel.h>
#include <layereditorcore/materialpropertycontroller.h>
#include <layereditorcore/samplemodel.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmModelUtils.h>
#include <qextMvvmModelMapper.h>

using namespace ModelView;

MaterialPropertyController::MaterialPropertyController(MaterialModel* material_model,
                                                       SampleModel* sample_model)
    : QEXTMvvmModelListener(material_model), m_sample_model(sample_model)
{
    setOnDataChange([this](QEXTMvvmSessionItem*, int) { update_all(); });
    setOnItemInserted([this](QEXTMvvmSessionItem*, QEXTMvvmTagRow) { update_all(); });
    setOnItemRemoved([this](QEXTMvvmSessionItem*, QEXTMvvmTagRow) { update_all(); });
    setOnModelReset([this](QEXTMvvmSessionModel*) { update_all(); });
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
