#include <qextMvvmItemPool.h>
#include <qextMvvmItemPool_p.h>
#include <qextMvvmUniqueIdGenerator.h>

#include <stdexcept>

QEXTMvvmItemPoolPrivate::QEXTMvvmItemPoolPrivate(QEXTMvvmItemPool *q)
    : q_ptr(q)
{

}

QEXTMvvmItemPoolPrivate::~QEXTMvvmItemPoolPrivate()
{

}



QEXTMvvmItemPool::QEXTMvvmItemPool()
    : d_ptr(new QEXTMvvmItemPoolPrivate(this))
{

}

QEXTMvvmItemPool::~QEXTMvvmItemPool()
{

}

int QEXTMvvmItemPool::size() const
{
    QEXT_DECL_DC(QEXTMvvmItemPool);
    if (d->m_keyToItem.size() != d->m_itemToKey.size())
    {
        throw std::runtime_error("Error in QEXTMvvmItemPool: array size mismatch");
    }
    return d->m_keyToItem.size();
}

QString QEXTMvvmItemPool::registerItem(QEXTMvvmItem *item, QString key)
{
    QEXT_DECL_D(QEXTMvvmItemPool);
    if (d->m_itemToKey.contains(item))
    {
        throw std::runtime_error("QEXTMvvmItemPool::register_item() -> Attempt to register already registered item.");
    }

    if (key.isEmpty())
    {
        key = QEXTMvvmUniqueIdGenerator::generate();
        while (d->m_keyToItem.contains(key))
        {
            key = QEXTMvvmUniqueIdGenerator::generate(); // preventing improbable duplicates
        }
    }
    else
    {
        if (d->m_keyToItem.contains(key))
        {
            throw std::runtime_error(" QEXTMvvmItemPool::register_item() -> Attempt to reuse existing key");
        }
    }

    d->m_keyToItem.insert(key, item);
    d->m_itemToKey.insert(item, key);
    return key;
}

void QEXTMvvmItemPool::unregisterItem(QEXTMvvmItem *item)
{
    QEXT_DECL_D(QEXTMvvmItemPool);
    if (!d->m_itemToKey.contains(item))
    {
        throw std::runtime_error("QEXTMvvmItemPool::deregister_item() -> Attempt to deregister non existing item.");
    }
    QString key = d->m_itemToKey.value(item);
    d->m_itemToKey.remove(item);
    d->m_keyToItem.remove(key);
}

QString QEXTMvvmItemPool::keyForItem(QEXTMvvmItem *item) const
{
    QEXT_DECL_DC(QEXTMvvmItemPool);
    if (d->m_itemToKey.contains(item))
    {
        return d->m_itemToKey.value(item);
    }
    return QString();
}

QEXTMvvmItem* QEXTMvvmItemPool::itemForKey(const QString &key) const
{
    QEXT_DECL_DC(QEXTMvvmItemPool);
    if (d->m_keyToItem.contains(key))
    {
        return d->m_keyToItem.value(key);
    }
    return QEXT_DECL_NULLPTR;
}
