// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemCatalogue.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmIFactory.h>
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmItemCatalogue::ItemCatalogueImpl {
    QExtMvvmIFactory<std::string, QExtMvvmSessionItem> factory;
    struct TypeAndLabel {
        std::string item_type;
        std::string item_label;
    };

    std::vector<TypeAndLabel> m_info;
};

QExtMvvmItemCatalogue::QExtMvvmItemCatalogue() : p_impl(qextMakeUnique<ItemCatalogueImpl>()) {}

QExtMvvmItemCatalogue::~QExtMvvmItemCatalogue() = default;

QExtMvvmItemCatalogue::QExtMvvmItemCatalogue(const QExtMvvmItemCatalogue& other)
{
    p_impl = qextMakeUnique<ItemCatalogueImpl>(*other.p_impl);
}

QExtMvvmItemCatalogue& QExtMvvmItemCatalogue::operator=(const QExtMvvmItemCatalogue& other)
{
    if (this != &other) {
        QExtMvvmItemCatalogue tmp(other);
        std::swap(this->p_impl, tmp.p_impl);
    }
    return *this;
}

void QExtMvvmItemCatalogue::registerItem(const std::string& modelType, QExtMvvmItemFactoryFunc func,
                                 const std::string& label)
{
    p_impl->factory.add(modelType, func);
    p_impl->m_info.push_back({modelType, label});
}

bool QExtMvvmItemCatalogue::contains(const std::string& modelType) const
{
    return p_impl->factory.contains(modelType);
}

QExtUniquePointer<QExtMvvmSessionItem> QExtMvvmItemCatalogue::create(const std::string& modelType) const
{
    return p_impl->factory.create(modelType);
}

std::vector<std::string> QExtMvvmItemCatalogue::modelTypes() const
{
    std::vector<std::string> result;
    for (const auto& x : p_impl->m_info)
        result.push_back(x.item_type);
    return result;
}

std::vector<std::string> QExtMvvmItemCatalogue::labels() const
{
    std::vector<std::string> result;
    for (const auto& x : p_impl->m_info)
        result.push_back(x.item_label);
    return result;
}

int QExtMvvmItemCatalogue::itemCount() const
{
    return static_cast<int>(p_impl->factory.size());
}

//! Adds content of other catalogue to this.

void QExtMvvmItemCatalogue::merge(const QExtMvvmItemCatalogue& other)
{
    size_t index(0);
    for (auto it : other.p_impl->factory) {
        if (contains(it.first))
            throw std::runtime_error(
                "QExtMvvmItemCatalogue::add() -> Catalogue contains duplicated records");

        registerItem(it.first, it.second, other.p_impl->m_info[index].item_label);
        ++index;
    }
}
