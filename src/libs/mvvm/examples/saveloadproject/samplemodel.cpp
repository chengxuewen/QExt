// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include <QColor>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemContainer.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmUtils.h>
#include <qextMvvmWidgetUtils.h>

namespace
{
QEXTMvvmItemCatalogue *qextMvvmCreateItemCatalogue()
{
    QEXTMvvmItemCatalogue *result = new QEXTMvvmItemCatalogue;
    result->registerItem<DemoItem>();
    return result;
}

QString random_name()
{
    static const QString alphabet = "abcdefgh";
    const size_t len(3);

    QString result;
    for (size_t i = 0; i < len; ++i)
    {
        int randomIndex = QEXTMvvmUtils::RandInt(0, static_cast<int>(alphabet.size() - 1));
        result.append(alphabet[randomIndex]);
    }

    return result;
}

const QString DemoItemType = "DemoItem";

} // namespace



DemoItem::DemoItem() : QEXTMvvmCompoundItem(DemoItemType)
{
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
}

SampleModel::SampleModel() : QEXTMvvmModel("SampleModel")
{
    setItemCatalogue(qextMvvmCreateItemCatalogue());
    initModelContent();
    setUndoRedoEnabled(true);
}

void SampleModel::appendNewItem(QEXTMvvmItem* container)
{
    auto item = insertItem<DemoItem>(container);
    item->setProperty(DemoItem::P_COLOR_PROPERTY, QEXTMvvmWidgetUtils::RandomColor());
    item->setProperty(DemoItem::P_STRING_PROPERTY, random_name());
    item->setProperty(DemoItem::P_INTEGER_PROPERTY, QEXTMvvmUtils::RandInt(0, 10));
}

//! Generates initial model content.

void SampleModel::initModelContent()
{
    auto container = insertItem<QEXTMvvmContainerItem>();
    appendNewItem(container);
    appendNewItem(container);
    appendNewItem(container);
}
