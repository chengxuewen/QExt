// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmSessionItem.h>

using namespace ModelView;

ItemFactory::ItemFactory(std::unique_ptr<ItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{
}

ItemFactory::~ItemFactory() = default;

std::unique_ptr<QEXTMvvmSessionItem> ItemFactory::createItem(const model_type& modelType) const
{
    return m_catalogue->create(modelType);
}

std::unique_ptr<QEXTMvvmSessionItem> ItemFactory::createEmptyItem() const
{
    return std::make_unique<QEXTMvvmSessionItem>();
}
