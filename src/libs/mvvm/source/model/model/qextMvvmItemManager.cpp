#include <qextMvvmItemCatalogueFactory.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmItemManager.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmSessionItem.h>

namespace
{
std::unique_ptr<ModelView::QEXTMvvmItemFactory> DefaultItemFactory()
{
    return std::make_unique<ModelView::QEXTMvvmItemFactory>(ModelView::CreateStandardItemCatalogue());
}
} // namespace

using namespace ModelView;

QEXTMvvmItemManager::QEXTMvvmItemManager() : m_item_factory(DefaultItemFactory()) {}

void QEXTMvvmItemManager::setItemFactory(std::unique_ptr<QEXTMvvmItemFactoryInterface> factory)
{
    m_item_factory = std::move(factory);
}

void QEXTMvvmItemManager::setItemPool(std::shared_ptr<QEXTMvvmItemPool> pool)
{
    m_item_pool = std::move(pool);
}

QEXTMvvmItemManager::~QEXTMvvmItemManager() = default;

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmItemManager::createItem(const QEXTMvvmModelType& modelType) const
{
    return m_item_factory->createItem(modelType);
}

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmItemManager::createRootItem() const
{
    return m_item_factory->createEmptyItem();
}

QEXTMvvmSessionItem* QEXTMvvmItemManager::findItem(const QEXTMvvmIdentifierType& id) const
{
    return m_item_pool ? m_item_pool->item_for_key(id) : nullptr;
}

QEXTMvvmIdentifierType QEXTMvvmItemManager::findIdentifier(QEXTMvvmSessionItem* item) const
{
    return m_item_pool ? m_item_pool->key_for_item(item) : QEXTMvvmIdentifierType();
}

const QEXTMvvmItemPool* QEXTMvvmItemManager::itemPool() const
{
    return m_item_pool.get();
}

QEXTMvvmItemPool* QEXTMvvmItemManager::itemPool()
{
    return m_item_pool.get();
}

void QEXTMvvmItemManager::register_item(QEXTMvvmSessionItem* item)
{
    if (m_item_pool)
        m_item_pool->register_item(item, item->identifier());
}

void QEXTMvvmItemManager::unregister_item(QEXTMvvmSessionItem* item)
{
    if (m_item_pool)
        m_item_pool->unregister_item(item);
}

const QEXTMvvmItemFactoryInterface* QEXTMvvmItemManager::factory() const
{
    return m_item_factory.get();
}
