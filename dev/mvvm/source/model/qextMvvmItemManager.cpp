// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemManager.h>
#include <qextMvvmItemCatalogueFactory.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmSessionItem.h>

namespace {
QExtUniquePointer<ModelView::QExtMvvmItemFactory> DefaultItemFactory()
{
    return qextMakeUnique<ModelView::QExtMvvmItemFactory>(ModelView::qextMvvmCreateStandardItemCatalogue());
}
} // namespace

using namespace ModelView;

QExtMvvmItemManager::QExtMvvmItemManager() : m_item_factory(DefaultItemFactory()) {}

void QExtMvvmItemManager::setItemFactory(QExtUniquePointer<QExtMvvmItemFactoryInterface> factory)
{
    m_item_factory = std::move(factory);
}

void QExtMvvmItemManager::setItemPool(std::shared_ptr<QExtMvvmItemPool> pool)
{
    m_item_pool = std::move(pool);
}

QExtMvvmItemManager::~QExtMvvmItemManager() = default;

QExtUniquePointer<QExtMvvmSessionItem> QExtMvvmItemManager::createItem(const QExtMvvmModelType& modelType) const
{
    return m_item_factory->createItem(modelType);
}

QExtUniquePointer<QExtMvvmSessionItem> QExtMvvmItemManager::createRootItem() const
{
    return qextMakeUnique<QExtMvvmSessionItem>();
}

QExtMvvmSessionItem* QExtMvvmItemManager::findItem(const QExtMvvmIdentifierType& id) const
{
    return m_item_pool ? m_item_pool->item_for_key(id) : nullptr;
}

QExtMvvmIdentifierType QExtMvvmItemManager::findIdentifier(const QExtMvvmSessionItem* item) const
{
    return m_item_pool ? m_item_pool->key_for_item(item) : QExtMvvmIdentifierType();
}

const QExtMvvmItemPool* QExtMvvmItemManager::itemPool() const
{
    return m_item_pool.get();
}

QExtMvvmItemPool* QExtMvvmItemManager::itemPool()
{
    return m_item_pool.get();
}

void QExtMvvmItemManager::registerInPool(QExtMvvmSessionItem* item)
{
    if (m_item_pool)
        m_item_pool->register_item(item, item->identifier());
}

void QExtMvvmItemManager::unregisterFromPool(QExtMvvmSessionItem* item)
{
    if (m_item_pool)
        m_item_pool->unregister_item(item);
}

const QExtMvvmItemFactoryInterface* QExtMvvmItemManager::factory() const
{
    return m_item_factory.get();
}

QExtMvvmItemFactoryInterface* QExtMvvmItemManager::factory()
{
    return const_cast<QExtMvvmItemFactoryInterface*>(static_cast<const QExtMvvmItemManager*>(this)->factory());
}
