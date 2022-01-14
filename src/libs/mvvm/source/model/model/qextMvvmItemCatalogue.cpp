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

struct QEXTMvvmItemCatalogue::ItemCatalogueImpl {
    QEXTMvvmIFactory<std::string, QEXTMvvmSessionItem> factory;
    struct TypeAndLabel {
        std::string item_type;
        std::string item_label;
    };

    std::vector<TypeAndLabel> m_info;
};

QEXTMvvmItemCatalogue::QEXTMvvmItemCatalogue() : p_impl(make_unique<ItemCatalogueImpl>()) {}

QEXTMvvmItemCatalogue::~QEXTMvvmItemCatalogue()
{

}

QEXTMvvmItemCatalogue::QEXTMvvmItemCatalogue(const QEXTMvvmItemCatalogue& other)
{
    p_impl = make_unique<ItemCatalogueImpl>(*other.p_impl);
}

QEXTMvvmItemCatalogue& QEXTMvvmItemCatalogue::operator=(const QEXTMvvmItemCatalogue& other)
{
    if (this != &other) {
        QEXTMvvmItemCatalogue tmp(other);
        std::swap(this->p_impl, tmp.p_impl);
    }
    return *this;
}

void QEXTMvvmItemCatalogue::add(const std::string& model_type, item_factory_func_t func,
                        const std::string& label)
{
    p_impl->factory.add(model_type, func);
    p_impl->m_info.push_back({model_type, label});
}

bool QEXTMvvmItemCatalogue::contains(const std::string& model_type) const
{
    return p_impl->factory.contains(model_type);
}

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmItemCatalogue::create(const std::string& model_type) const
{
    return p_impl->factory.create(model_type);
}

std::vector<std::string> QEXTMvvmItemCatalogue::modelTypes() const
{
    std::vector<std::string> result;
    for (const auto& x : p_impl->m_info)
        result.push_back(x.item_type);
    return result;
}

std::vector<std::string> QEXTMvvmItemCatalogue::labels() const
{
    std::vector<std::string> result;
    for (const auto& x : p_impl->m_info)
        result.push_back(x.item_label);
    return result;
}

int QEXTMvvmItemCatalogue::itemCount() const
{
    return static_cast<int>(p_impl->factory.size());
}

//! Adds content of other catalogue to this.

void QEXTMvvmItemCatalogue::merge(const QEXTMvvmItemCatalogue& other)
{
    size_t index(0);
    for (auto it : other.p_impl->factory) {
        if (contains(it.first))
            throw std::runtime_error(
                "ItemCatalogue::add() -> Catalogue contains duplicated records");

        add(it.first, it.second, other.p_impl->m_info[index].item_label);
        ++index;
    }
}
