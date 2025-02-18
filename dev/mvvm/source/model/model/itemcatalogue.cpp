// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/itemcatalogue.h"
#include "model/model/sessionitem.h"
#include "model/utils/ifactory.h"
#include <stdexcept>

using namespace ModelView;

struct ItemCatalogue::ItemCatalogueImpl {
    IFactory<std::string, SessionItem> factory;
    struct TypeAndLabel {
        std::string item_type;
        std::string item_label;
    };

    std::vector<TypeAndLabel> m_info;
};

ItemCatalogue::ItemCatalogue() : p_impl(qextMakeUnique<ItemCatalogueImpl>()) {}

ItemCatalogue::~ItemCatalogue() = default;

ItemCatalogue::ItemCatalogue(const ItemCatalogue& other)
{
    p_impl = qextMakeUnique<ItemCatalogueImpl>(*other.p_impl);
}

ItemCatalogue& ItemCatalogue::operator=(const ItemCatalogue& other)
{
    if (this != &other) {
        ItemCatalogue tmp(other);
        std::swap(this->p_impl, tmp.p_impl);
    }
    return *this;
}

void ItemCatalogue::registerItem(const std::string& modelType, item_factory_func_t func,
                                 const std::string& label)
{
    p_impl->factory.add(modelType, func);
    p_impl->m_info.push_back({modelType, label});
}

bool ItemCatalogue::contains(const std::string& modelType) const
{
    return p_impl->factory.contains(modelType);
}

QExtUniquePointer<SessionItem> ItemCatalogue::create(const std::string& modelType) const
{
    return p_impl->factory.create(modelType);
}

std::vector<std::string> ItemCatalogue::modelTypes() const
{
    std::vector<std::string> result;
    for (const auto& x : p_impl->m_info)
        result.push_back(x.item_type);
    return result;
}

std::vector<std::string> ItemCatalogue::labels() const
{
    std::vector<std::string> result;
    for (const auto& x : p_impl->m_info)
        result.push_back(x.item_label);
    return result;
}

int ItemCatalogue::itemCount() const
{
    return static_cast<int>(p_impl->factory.size());
}

//! Adds content of other catalogue to this.

void ItemCatalogue::merge(const ItemCatalogue& other)
{
    size_t index(0);
    for (auto it : other.p_impl->factory) {
        if (contains(it.first))
            throw std::runtime_error(
                "ItemCatalogue::add() -> Catalogue contains duplicated records");

        registerItem(it.first, it.second, other.p_impl->m_info[index].item_label);
        ++index;
    }
}
