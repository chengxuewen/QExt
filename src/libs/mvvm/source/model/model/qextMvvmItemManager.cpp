// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemCatalogueFactory.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmItemManager.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmSessionItem.h>

namespace
{
std::unique_ptr<ModelView::ItemFactory> DefaultItemFactory()
{
    return std::make_unique<ModelView::ItemFactory>(ModelView::CreateStandardItemCatalogue());
}
} // namespace

using namespace ModelView;

ItemManager::ItemManager() : m_item_factory(DefaultItemFactory()) {}

void ItemManager::setItemFactory(std::unique_ptr<QEXTMvvmItemFactoryInterface> factory)
{
    m_item_factory = std::move(factory);
}

void ItemManager::setItemPool(std::shared_ptr<ItemPool> pool)
{
    m_item_pool = std::move(pool);
}

ItemManager::~ItemManager() = default;

std::unique_ptr<QEXTMvvmSessionItem> ItemManager::createItem(const model_type& modelType) const
{
    return m_item_factory->createItem(modelType);
}

std::unique_ptr<QEXTMvvmSessionItem> ItemManager::createRootItem() const
{
    return m_item_factory->createEmptyItem();
}

QEXTMvvmSessionItem* ItemManager::findItem(const identifier_type& id) const
{
    return m_item_pool ? m_item_pool->item_for_key(id) : nullptr;
}

identifier_type ItemManager::findIdentifier(QEXTMvvmSessionItem* item) const
{
    return m_item_pool ? m_item_pool->key_for_item(item) : identifier_type();
}

const ItemPool* ItemManager::itemPool() const
{
    return m_item_pool.get();
}

ItemPool* ItemManager::itemPool()
{
    return m_item_pool.get();
}

void ItemManager::register_item(QEXTMvvmSessionItem* item)
{
    if (m_item_pool)
        m_item_pool->register_item(item, item->identifier());
}

void ItemManager::unregister_item(QEXTMvvmSessionItem* item)
{
    if (m_item_pool)
        m_item_pool->unregister_item(item);
}

const QEXTMvvmItemFactoryInterface* ItemManager::factory() const
{
    return m_item_factory.get();
}
