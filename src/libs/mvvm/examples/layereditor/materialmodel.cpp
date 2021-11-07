// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include "materialmodel.h"
#include <qextMvvmExternalProperty.h>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmVectorItem.h>



namespace
{
QEXTMvvmItemCatalogue *qextMvvmCreateItemCatalogue()
{
    QEXTMvvmItemCatalogue *result = new QEXTMvvmItemCatalogue;
    result->registerItem<SLDMaterialItem>();
    return result;
}

const QString SLDMaterialType = "SLDMaterial";

} // namespace



SLDMaterialItem::SLDMaterialItem() : QEXTMvvmCompoundItem(SLDMaterialType)
{
    addProperty(P_NAME, "Unnamed")->setDisplayName("Name");
    addProperty(P_COLOR, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_SLD_REAL, 1e-06)->setDisplayName("SLD, real");
    addProperty(P_SLD_IMAG, 1e-08)->setDisplayName("SLD, imag");
    addProperty<QEXTMvvmVectorItem>("Magnetization");
}

void SLDMaterialItem::set_properties(const QString& name, const QColor& color, double real,
                                     double imag)
{
    setProperty(P_NAME, name);
    setProperty(P_COLOR, color);
    setProperty(P_SLD_REAL, real);
    setProperty(P_SLD_IMAG, imag);
}

MaterialModel::MaterialModel() : QEXTMvvmModel("MaterialModel")
{
    setItemCatalogue(qextMvvmCreateItemCatalogue());
    init_model();
}

//! Returns default property representing non-existent material.

QEXTMvvmExternalProperty MaterialModel::undefined_material()
{
    return QEXTMvvmExternalProperty("Undefined", QColor(Qt::red));
}

//! Returns vector of properties representing possible choice of materials.
//! Here we assume that all materials seats in top level material containers.

QVector<QEXTMvvmExternalProperty> MaterialModel::material_data()
{
    QVector<QEXTMvvmExternalProperty> result;

    result.push_back(undefined_material());
    for (auto container : rootItem()->children()) {
        for (auto item : container->children()) {
            if (auto material = dynamic_cast<SLDMaterialItem*>(item)) {
                auto text = material->property<QString>(SLDMaterialItem::P_NAME);
                auto color = material->property<QColor>(SLDMaterialItem::P_COLOR);
                auto id = material->identifier();
                result.push_back(QEXTMvvmExternalProperty(text, color, id));
            }
        }
    }
    return result;
}

//! Returns property from given material id.

QEXTMvvmExternalProperty MaterialModel::material_property(const QString& id)
{
    auto materials = material_data();
    for (const auto& prop : material_data())
        if (prop.identifier() == id)
            return prop;

    return undefined_material();
}

//! Populates the model with some default content.

void MaterialModel::init_model()
{
    auto container = insertItem<QEXTMvvmContainerItem>();
    auto material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Air", QColor(Qt::blue), 1e-06, 1e-07);

    material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Au", QColor(Qt::yellow), 2.4e-06, 5.6e-07);

    material = insertItem<SLDMaterialItem>(container);
    material->set_properties("Si2O3", QColor(Qt::darkCyan), 3.4e-06, 3.6e-07);
}
