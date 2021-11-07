// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVariant>
#include "materialmodel.h"
#include "samplemodel.h"
#include <qextMvvmExternalProperty.h>
#include <qextMvvmItemCatalogue.h>



namespace
{
QEXTMvvmItemCatalogue *qextMvvmCreateItemCatalogue()
{
    QEXTMvvmItemCatalogue *result = new QEXTMvvmItemCatalogue;
    result->registerItem<MultiLayerItem>();
    result->registerItem<LayerItem>();
    return result;
}

const QString MultiLayerType = "MultiLayer";
const QString LayerType = "Layer";

} // namespace



LayerItem::LayerItem() : QEXTMvvmCompoundItem(LayerType)
{
    addProperty(P_NAME, "Layer")->setDisplayName("Name");
    addProperty(P_MATERIAL, MaterialModel::undefined_material())->setDisplayName("Material");
    addProperty(P_THICKNESS, 42.0)->setDisplayName("Thickness");
}

MultiLayerItem::MultiLayerItem() : QEXTMvvmCompoundItem(MultiLayerType)
{
    addProperty(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    QVector<QString> allowed_child = {MultiLayerType, LayerType};
    registerTag(QEXTMvvmTagInfo::universalTag(T_LAYERS, allowed_child), /*set_default*/ true);
}

SampleModel::SampleModel() : QEXTMvvmModel("SampleModel")
{
    setItemCatalogue(qextMvvmCreateItemCatalogue());
    init_model();
}

//! Populats the model with some default content.

void SampleModel::init_model()
{
    auto multilayer = insertItem<MultiLayerItem>();
    insertItem<LayerItem>(multilayer);
    auto assembly = insertItem<MultiLayerItem>(multilayer);
    insertItem<LayerItem>(assembly);
    insertItem<LayerItem>(assembly);
    insertItem<LayerItem>(multilayer);
}
