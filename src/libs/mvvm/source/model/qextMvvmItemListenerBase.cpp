#include <qextMvvmItemListenerBase.h>
#include <qextMvvmItemMapper.h>
#include <qextMvvmItem.h>

QEXTMvvmItemListenerBase::QEXTMvvmItemListenerBase(QEXTMvvmItem *item)
    : m_item(QEXT_DECL_NULLPTR)
{
    this->setItem(item);
}

QEXTMvvmItemListenerBase::~QEXTMvvmItemListenerBase()
{
    this->removeListener();
}

QEXTConnection QEXTMvvmItemListenerBase::addItemAboutToBeInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemAboutToBeInsertedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemInsertedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemAboutToBeRemovedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemRemovedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemDataAboutToBeChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemDataAboutToBeChangedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemDataChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemDataChangedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemAboutToBeDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemAboutToBeDestroyedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemDestroyedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemPropertyAboutToBeChangedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemPropertyChangedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemChildPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemChildPropertyAboutToBeChangedListener(function, this);
}

QEXTConnection QEXTMvvmItemListenerBase::addItemChildPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_item->mapper()->addItemChildPropertyChangedListener(function, this);
}

void QEXTMvvmItemListenerBase::removeListener(void *listener)
{
    Q_UNUSED(listener);
    m_item->mapper()->removeListener(this);
}

void QEXTMvvmItemListenerBase::setItem(QEXTMvvmItem *item)
{
    if (m_item != item)
    {
        this->unsubscribeFromCurrent();
        m_item = item;
        if (m_item)
        {
            m_item->mapper()->addItemDestroyedListener(QEXTMvvmItemFunction(this, &QEXTMvvmItemListenerBase::onItemDestroy), this);
            this->subscribe();
        }
    }
}

//! Sets callback to be notified when row is about to be removed.
//! Callback will be called with (compound_item, tagrow). For MultiLayer containing the T_LAYERS
//! tag, the signal will be triggered on layer deletion with
//! (multilayer*, {T_LAYER, row}) as callback parameters.

QEXTMvvmItem *QEXTMvvmItemListenerBase::item() const
{
    return m_item;
}

void QEXTMvvmItemListenerBase::unsubscribeFromCurrent()
{
    if (m_item)
    {
        this->unsubscribe();
        m_item->mapper()->removeListener(this);
    }
}

void QEXTMvvmItemListenerBase::onItemDestroy(QEXTMvvmItem *)
{
    m_item = QEXT_DECL_NULLPTR;
    this->unsubscribe();
}
