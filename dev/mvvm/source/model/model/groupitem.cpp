// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/groupitem.h"
#include "model/model/comboproperty.h"
#include "model/model/taginfo.h"
#include "model/utils/containerutils.h"
#include <stdexcept>

using namespace ModelView;

namespace {

//! Returns vector of model types for given vector of items.
std::vector<std::string> modelTypes(const std::vector<QExtMvvmSessionItem*>& items)
{
    std::vector<std::string> result;
    std::transform(items.begin(), items.end(), std::back_inserter(result),
                   [](QExtMvvmSessionItem *item) { return item->modelType(); });
    return result;
}
} // namespace

QExtMvvmGroupItem::~QExtMvvmGroupItem() = default;

QExtMvvmGroupItem::QExtMvvmGroupItem(QExtMvvmModelType modelType) : QExtMvvmSessionItem(std::move(modelType)), m_index_to_select(0)
{
    registerTag(QExtMvvmTagInfo::universalTag(T_GROUP_ITEMS), /*set_as_default*/ true);
    setData(QExtMvvmComboProperty());
}

int QExtMvvmGroupItem::currentIndex() const
{
    return data<QExtMvvmComboProperty>().currentIndex();
}

//! Returns currently selected item.

const QExtMvvmSessionItem* QExtMvvmGroupItem::currentItem() const
{
    return currentIndex() != -1 ? getItem("", currentIndex()) : nullptr;
}

QExtMvvmSessionItem* QExtMvvmGroupItem::currentItem()
{
    return const_cast<QExtMvvmSessionItem*>(static_cast<const QExtMvvmGroupItem*>(this)->currentItem());
}

std::string QExtMvvmGroupItem::currentType() const
{
    return currentItem() ? currentItem()->modelType() : std::string();
}

//! Sets item corresponding to given model type.

void QExtMvvmGroupItem::setCurrentType(const std::string& QExtMvvmModelType)
{
    int index = Utils::IndexOfItem(modelTypes(children()), QExtMvvmModelType);
    if (index == -1)
        throw std::runtime_error("QExtMvvmGroupItem::setCurrentType() -> Model type '" + QExtMvvmModelType
                                 + "' doesn't belong to the group");
    setCurrentIndex(index);
}

void QExtMvvmGroupItem::setCurrentIndex(int index)
{
    auto combo = data<QExtMvvmComboProperty>();
    combo.setCurrentIndex(index);
    setData(combo, ItemDataRole::DATA);
}

//! Updates internal data representing selection of items, and current selection.
//! To be called during QExtMvvmGroupItem's construction.

void QExtMvvmGroupItem::updateCombo()
{
    QExtMvvmComboProperty combo;
    combo.setValues(m_item_text);
    combo.setCurrentIndex(m_index_to_select);
    setData(combo, ItemDataRole::DATA);
}
