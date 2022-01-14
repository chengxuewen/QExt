// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "item_constants.h"
#include <QColor>

#include <qextMvvmEditorConstants.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmRealLimits.h>

using namespace ModelView;

namespace CellEditors
{

DemoPropertiesItem::DemoPropertiesItem() : QEXTMvvmCompoundItem(::QEXTMvvmConstants::DemoPropertiesType)
{
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool")->setToolTip("tooltip");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1234)
        ->setDisplayName("Double")
        ->setLimits(QEXTMvvmRealLimits::limitless());
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");

    auto combo = QEXTMvvmComboProperty::createFrom({"option 1", "option 2", "option 3"});
    addProperty(P_COMBO_PROPERTY, combo)->setDisplayName("Combo");

    addProperty(P_SELECTABLE_COMBO_PROPERTY, combo)
        ->setDisplayName("Selectable")
        ->setEditorType(ModelView::QEXTMvvmConstants::SelectableComboPropertyEditorType);

    QEXTMvvmExternalProperty ext_prop("Gold", QColor(Qt::darkYellow), "some id");
    addProperty(P_EXTERNAL_PROPERTY, ext_prop)->setDisplayName("External");
}

SampleModel::SampleModel() : QEXTMvvmSessionModel("SampleModel")
{
    auto catalogue = make_unique<ModelView::QEXTMvvmItemCatalogue>();
    catalogue->registerItem<DemoPropertiesItem>();

    setItemCatalogue(std::move(catalogue));
}

} // namespace CellEditors
