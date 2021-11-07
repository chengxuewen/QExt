#include <qextMvvmItemManager.h>
#include <qextMvvmItemManager_p.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmFactory.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmItem.h>

namespace
{
QEXTMvvmItemFactory *qextMvvmDefaultItemFactory()
{
    return new QEXTMvvmItemFactory(QEXTMvvmFactory::createStandardItemCatalogue());
}
} // namespace


QEXTMvvmItemManagerPrivate::QEXTMvvmItemManagerPrivate(QEXTMvvmItemManager *q)
    : q_ptr(q)
    , m_itemFactory(qextMvvmDefaultItemFactory())
{

}

QEXTMvvmItemManagerPrivate::~QEXTMvvmItemManagerPrivate()
{

}



QEXTMvvmItemManager::QEXTMvvmItemManager()
    : d_ptr(new QEXTMvvmItemManagerPrivate(this))
{

}

QEXTMvvmItemManager::~QEXTMvvmItemManager()
{

}

void QEXTMvvmItemManager::setItemFactory(QEXTMvvmItemFactoryInterface *factory)
{
    QEXT_DECL_D(QEXTMvvmItemManager);
    d->m_itemFactory.reset(factory);
}

void QEXTMvvmItemManager::setItemPool(const QSharedPointer<QEXTMvvmItemPool> &pool)
{
    QEXT_DECL_D(QEXTMvvmItemManager);
    d->m_itemPool = pool;
}

QEXTMvvmItem *QEXTMvvmItemManager::createItem(const QString &modelType) const
{
    QEXT_DECL_DC(QEXTMvvmItemManager);
    return d->m_itemFactory->createItem(modelType);
}

QEXTMvvmItem *QEXTMvvmItemManager::createRootItem() const
{
    QEXT_DECL_DC(QEXTMvvmItemManager);
    return d->m_itemFactory->createEmptyItem();
}

QEXTMvvmItem *QEXTMvvmItemManager::findItem(const QString &id) const
{
    QEXT_DECL_DC(QEXTMvvmItemManager);
    return d->m_itemPool ? d->m_itemPool->itemForKey(id) : QEXT_DECL_NULLPTR;
}

QString QEXTMvvmItemManager::findIdentifier(QEXTMvvmItem *item) const
{
    QEXT_DECL_DC(QEXTMvvmItemManager);
    return d->m_itemPool ? d->m_itemPool->keyForItem(item) : QString();
}

const QEXTMvvmItemPool *QEXTMvvmItemManager::itemPool() const
{
    QEXT_DECL_DC(QEXTMvvmItemManager);
    return d->m_itemPool.data();
}

QEXTMvvmItemPool *QEXTMvvmItemManager::itemPool()
{
    QEXT_DECL_DC(QEXTMvvmItemManager);
    return d->m_itemPool.data();
}

void QEXTMvvmItemManager::registerItem(QEXTMvvmItem *item)
{
    QEXT_DECL_D(QEXTMvvmItemManager);
    if (d->m_itemPool)
    {
        d->m_itemPool->registerItem(item, item->identifier());
    }
}

void QEXTMvvmItemManager::unregisterItem(QEXTMvvmItem *item)
{
    QEXT_DECL_D(QEXTMvvmItemManager);
    if (d->m_itemPool)
    {
        d->m_itemPool->unregisterItem(item);
    }
}

const QEXTMvvmItemFactoryInterface *QEXTMvvmItemManager::factory() const
{
    QEXT_DECL_DC(QEXTMvvmItemManager);
    return d->m_itemFactory.data();
}
