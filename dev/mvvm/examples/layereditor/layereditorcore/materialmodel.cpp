// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialmodel.h"
#include "model/model/externalproperty.h"
#include "model/model/itemcatalogue.h"
#include "model/standarditems/containeritem.h"
#include "model/standarditems/vectoritem.h"
#include <QColor>

using namespace ModelView;

namespace {
QExtUniquePointer<QExtMvvmItemCatalogue> CreateItemCatalogue()
{
    auto result = qextMakeUnique<ModelView::QExtMvvmItemCatalogue>();
    result->registerItem<SLDMaterialItem>();
    return result;
}

const std::string SLDMaterialType = "SLDMaterial";

} // namespace

using namespace ModelView;

SLDMaterialItem::SLDMaterialItem() : ModelView::QExtMvvmCompoundItem(SLDMaterialType)
{
    addProperty(P_NAME, "Unnamed")->setDisplayName("Name");
    addProperty(P_COLOR, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_SLD_REAL, 1e-06)->setDisplayName("SLD, real");
    addProperty(P_SLD_IMAG, 1e-08)->setDisplayName("SLD, imag");
    addProperty<QExtMvvmVectorItem>("Magnetization");
}

void SLDMaterialItem::set_properties(const std::string& name, const QColor& color, double real,
                                     double imag)
{
    setProperty(P_NAME, name);
    setProperty(P_COLOR, color);
    setProperty(P_SLD_REAL, real);
    setProperty(P_SLD_IMAG, imag);
}

MaterialModel::MaterialModel() : QExtMvvmSessionModel("MaterialModel")
{
    setItemCatalogue(CreateItemCatalogue());
    populateModel();
}

//! Returns default property representing non-existent material.

QExtMvvmExternalProperty MaterialModel::undefined_material()
{
    return QExtMvvmExternalProperty("Undefined", QColor(Qt::red));
}

//! Returns vector of properties representing possible choice of materials.
//! Here we assume that all materials seats in top level material containers.

std::vector<QExtMvvmExternalProperty> MaterialModel::material_data()
{
    std::vector<QExtMvvmExternalProperty> result;

    result.push_back(undefined_material());
    for (auto container : rootItem()->children()) {
        for (auto item : container->children()) {
            if (auto material = dynamic_cast<SLDMaterialItem*>(item)) {
                auto text = material->property<std::string>(SLDMaterialItem::P_NAME);
                auto color = material->property<QColor>(SLDMaterialItem::P_COLOR);
                auto id = material->identifier();
                result.emplace_back(QExtMvvmExternalProperty(text, color, id));
            }
        }
    }
    return result;
}

//! Returns property from given material id.

QExtMvvmExternalProperty MaterialModel::material_property(const std::string& id)
{
    auto materials = material_data();
    for (const auto& prop : material_data())
        if (prop.identifier() == id)
            return prop;

    return undefined_material();
}

//! Populates the model with some default content.

void MaterialModel::populateModel()
{
    auto container = insertItem<ModelView::QExtMvvmContainerItem>();
    auto material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Air", QColor(Qt::blue), 1e-06, 1e-07);

    material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Au", QColor(Qt::yellow), 2.4e-06, 5.6e-07);

    material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Si2O3", QColor(Qt::darkCyan), 3.4e-06, 3.6e-07);
}
