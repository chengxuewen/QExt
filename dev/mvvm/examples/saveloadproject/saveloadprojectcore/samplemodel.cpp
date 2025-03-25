// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include <qextMvvmContainerItem.h>
#include <qextMvvmNumericUtils.h>
#include <qextMvvmWidgetUtils.h>
#include <QColor>

namespace {
std::string random_name()
{
    static const std::string alphabet = "abcdefgh";
    const size_t len(3);

    std::string result;
    for (size_t i = 0; i < len; ++i) {
        size_t random_index = static_cast<size_t>(
            ModelView::Utils::RandInt(0, static_cast<int>(alphabet.size() - 1)));
        result.push_back(alphabet[random_index]);
    }

    return result;
}

const std::string DemoItemType = "DemoItem";

} // namespace

using namespace ModelView;

DemoItem::DemoItem() : QExtMvvmCompoundItem(DemoItemType)
{
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
}

SampleModel::SampleModel() : QExtMvvmSessionModel("SampleModel")
{
    registerItem<DemoItem>();
    populateModel();
    setUndoRedoEnabled(true);
}

void SampleModel::appendNewItem(ModelView::QExtMvvmSessionItem* container)
{
    auto item = insertItem<DemoItem>(container);
    item->setProperty(DemoItem::P_COLOR_PROPERTY, ModelView::Utils::RandomColor());
    item->setProperty(DemoItem::P_STRING_PROPERTY, random_name());
    item->setProperty(DemoItem::P_INTEGER_PROPERTY, ModelView::Utils::RandInt(0, 10));
}

//! Generates initial model content.

void SampleModel::populateModel()
{
    auto container = insertItem<ModelView::QExtMvvmContainerItem>();
    appendNewItem(container);
    appendNewItem(container);
    appendNewItem(container);
}
