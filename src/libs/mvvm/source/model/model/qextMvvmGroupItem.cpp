#include <qextMvvmComboProperty.h>
#include <qextMvvmGroupItem.h>
#include <qextMvvmTagInfo.h>
#include <utils/qextMvvmContainerUtils.h>
#include <stdexcept>

using namespace ModelView;

QEXTMvvmGroupItem::~QEXTMvvmGroupItem() = default;

QEXTMvvmGroupItem::QEXTMvvmGroupItem(QEXTMvvmModelType modelType)
    : QEXTMvvmSessionItem(std::move(modelType))
    , m_catalogue(std::make_unique<QEXTMvvmItemCatalogue>())
    , m_default_selected_index(0)
{
    registerTag(QEXTMvvmTagInfo::universalTag(T_GROUP_ITEMS), /*set_as_default*/ true);
    setData(QEXTMvvmComboProperty());
}

int QEXTMvvmGroupItem::currentIndex() const
{
    return data<QEXTMvvmComboProperty>().currentIndex();
}

//! Returns currently selected item.

const QEXTMvvmSessionItem* QEXTMvvmGroupItem::currentItem() const
{
    return is_valid_index() ? getItem("", currentIndex()) : nullptr;
}

QEXTMvvmSessionItem* QEXTMvvmGroupItem::currentItem()
{
    return const_cast<QEXTMvvmSessionItem*>(static_cast<const QEXTMvvmGroupItem*>(this)->currentItem());
}

std::string QEXTMvvmGroupItem::currentType() const
{
    return is_valid_index() ? m_catalogue->modelTypes()[static_cast<size_t>(currentIndex())] : "";
}

//! Sets item corresponding to given model type.

void QEXTMvvmGroupItem::setCurrentType(const std::string& QEXTMvvmModelType)
{
    auto model_types = m_catalogue->modelTypes();
    int index = Utils::IndexOfItem(model_types, QEXTMvvmModelType);
    if (index == -1)
        throw std::runtime_error("QEXTMvvmGroupItem::setCurrentType() -> Model type '" + QEXTMvvmModelType
                                 + "' doesn't belong to the group");

    setCurrentIndex(index);
}

void QEXTMvvmGroupItem::setCurrentIndex(int index)
{
    auto combo = data<QEXTMvvmComboProperty>();
    combo.setCurrentIndex(index);
    setData(combo, ItemDataRole::DATA);
}

bool QEXTMvvmGroupItem::is_valid_index() const
{
    return currentIndex() != -1;
}

//! Inits group item by creating all registered items and constructing combo property
//! for switching between items.

void QEXTMvvmGroupItem::init_group()
{
    QEXTMvvmComboProperty combo;
    combo.setValues(m_catalogue->labels());
    combo.setCurrentIndex(m_default_selected_index);
    setData(combo, ItemDataRole::DATA);
    for (const auto& x : m_catalogue->modelTypes())
        insertItem(m_catalogue->create(x).release(), QEXTMvvmTagRow::append(T_GROUP_ITEMS));
}
