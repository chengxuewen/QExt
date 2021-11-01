// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"
#include <QColor>
#include <qextMvvmItemCatalogue.h>
#include <utils/qextMvvmNumericUtils.h>
#include <widgets/widgetutils.h>

namespace DragAndView
{

namespace
{
std::unique_ptr<ModelView::QEXTMvvmItemCatalogue> CreateToyItemCatalogue()
{
    auto result = std::make_unique<ModelView::QEXTMvvmItemCatalogue>();
    result->registerItem<DemoItem>();
    result->registerItem<DemoContainerItem>();
    return result;
}

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
} // namespace

SampleModel::SampleModel() : QEXTMvvmSessionModel("SampleModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
    init_model_content();
    setUndoRedoEnabled(true);
}

void SampleModel::append_random_item(ModelView::QEXTMvvmSessionItem* container)
{
    auto item = insertItem<DemoItem>(container);
    item->setProperty(DemoItem::P_COLOR_PROPERTY, ModelView::Utils::RandomColor());
    item->setProperty(DemoItem::P_STRING_PROPERTY, random_name());
    item->setProperty(DemoItem::P_INTEGER_PROPERTY, ModelView::Utils::RandInt(0, 10));
}

//! Generates initial model content.

void SampleModel::init_model_content()
{
    auto container = insertItem<DemoContainerItem>();
    append_random_item(container);
    append_random_item(container);
    append_random_item(container);

    container = insertItem<DemoContainerItem>();
    append_random_item(container);
    append_random_item(container);
}

} // namespace DragAndView
