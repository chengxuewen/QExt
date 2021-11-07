#include <qextMvvmItemMapper.h>
#include <qextMvvmItemMapper_p.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmModelMapper.h>
#include <qextMvvmModelListener.h>
#include <qextMvvmModel.h>

#include <qextSignal.h>

#include <stdexcept>


QEXTMvvmItemMapperPrivate::QEXTMvvmItemMapperPrivate(QEXTMvvmItemMapper *q)
    : q_ptr(q)
    , m_active(true)
    , m_item(QEXT_DECL_NULLPTR)
{

}

QEXTMvvmItemMapperPrivate::~QEXTMvvmItemMapperPrivate()
{

}

int QEXTMvvmItemMapperPrivate::nestlingDepth(QEXTMvvmItem *item, int level)
{
    if (item == nullptr || item == m_modelListener->model()->rootItem())
        return -1;
    if (item == m_item)
        return level;
    return nestlingDepth(item->parent(), level + 1);
}

void QEXTMvvmItemMapperPrivate::processDataChange(QEXTMvvmItem *item, int role)
{
    int nestling = nestlingDepth(item);

    // own item data changed
    if (nestling == 0)
        callOnDataChange(item, role);

    // data of item's property changed
    if (nestling == 1)
        callOnPropertyChange(m_item, m_item->tagOfItem(item));

    // child property changed
    if (nestling == 2) {
        if (auto parent = item->parent())
            callOnChildPropertyChange(parent, parent->tagOfItem(item));
    }
}

void QEXTMvvmItemMapperPrivate::processItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (parent == m_item)
        callOnItemInserted(m_item, tagrow);
}

void QEXTMvvmItemMapperPrivate::processItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (parent == m_item)
        callOnItemRemoved(m_item, tagrow);
}

void QEXTMvvmItemMapperPrivate::processAboutToRemoveItem(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (parent == m_item)
        callOnAboutToRemoveItem(m_item, tagrow);
}

void QEXTMvvmItemMapperPrivate::callOnDataChange(QEXTMvvmItem *item, int role)
{
    if (m_active)
        m_itemDataChangedSignal(item, role);
}

void QEXTMvvmItemMapperPrivate::callOnPropertyChange(QEXTMvvmItem *item, QString property_name)
{
    if (m_active)
        m_itemPropertyChangedSignal(item, property_name);
}

void QEXTMvvmItemMapperPrivate::callOnChildPropertyChange(QEXTMvvmItem *item, QString property_name)
{
        if (m_active)
            m_itemChildPropertyChangedSignal(item, property_name);
}

void QEXTMvvmItemMapperPrivate::callOnItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (m_active)
        m_itemInsertedSignal(parent, tagrow);
}

void QEXTMvvmItemMapperPrivate::callOnItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (m_active)
        m_itemRemovedSignal(parent, tagrow);
}

void QEXTMvvmItemMapperPrivate::callOnAboutToRemoveItem(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (m_active)
    {
        m_itemAboutToBeRemovedSignal(parent, tagrow);
    }
}



QEXTMvvmItemMapper::QEXTMvvmItemMapper(QEXTMvvmItem *item)
    : d_ptr(new QEXTMvvmItemMapperPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    if (!item)
    {
        throw std::runtime_error("QEXTMvvmItemMapper::QEXTMvvmItemMapper() -> Not initialized item");
    }

    if (!item->model())
    {
        throw std::runtime_error("QEXTMvvmItemMapper::QEXTMvvmItemMapper() -> Item doesn't have model");
    }

    d->m_item = item;
    d->m_modelListener.reset(new QEXTMvvmModelListener<QEXTMvvmModel>(item->model()));

    d->m_modelListener->addItemDataChangedListener(QEXTMvvmItemRoleFunction(d, &QEXTMvvmItemMapperPrivate::processDataChange));
    d->m_modelListener->addItemInsertedListener(QEXTMvvmItemTagRowFunction(d, &QEXTMvvmItemMapperPrivate::processItemInserted));
    d->m_modelListener->addItemRemovedListener(QEXTMvvmItemTagRowFunction(d, &QEXTMvvmItemMapperPrivate::processItemRemoved));
    d->m_modelListener->addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction(d, &QEXTMvvmItemMapperPrivate::processAboutToRemoveItem));

//    auto on_data_change = [this](auto item, auto role) { d->processDataChange(item, role); };
//    QEXTMvvmModelListener::addItemDataChangedListener(on_data_change);

//    auto on_item_inserted = [this](auto item, auto tagrow) {
//        d->processItemInserted(item, tagrow);
//    };
//    QEXTMvvmModelListener::addItemInsertedListener(on_item_inserted, this);

//    auto on_item_removed = [this](auto item, auto tagrow) {
//        d->processItemRemoved(item, tagrow);
//    };
//    QEXTMvvmModelListener::addItemRemovedListener(on_item_removed, this);

//    auto on_about_to_remove_item = [this](auto item, auto tagrow) {
//        d->processAboutToRemoveItem(item, tagrow);
//    };
//    QEXTMvvmModelListener::addItemAboutToBeRemovedListener(on_about_to_remove_item, this);
}

QEXTMvvmItemMapper::~QEXTMvvmItemMapper()
{

}

QEXTConnection QEXTMvvmItemMapper::addItemAboutToBeInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemAboutToBeInsertedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemInsertedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemAboutToBeRemovedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemRemovedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemDataAboutToBeChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemDataAboutToBeChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemDataChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemDataChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemAboutToBeDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemAboutToBeDestroyedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemDestroyedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemPropertyAboutToBeChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemPropertyChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemChildPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemChildPropertyAboutToBeChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmItemMapper::addItemChildPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QEXTConnection connection = d->m_itemChildPropertyChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

void QEXTMvvmItemMapper::removeListener(void *listener)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    QList<QEXTConnection> connections = d->m_lisenterConnectionMap.values(listener);
    for (int i = 0; i < connections.size(); ++i)
    {
        QEXTConnection connection = connections.at(i);
        connection.disconnect();
    }
    d->m_lisenterConnectionMap.remove(listener);
}


//! Sets activity flag to given value. Will disable all callbacks if false.

void QEXTMvvmItemMapper::setActive(bool value)
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    d->m_active = value;
}

//! Calls all callbacks subscribed to "item is destroyed" event.

void QEXTMvvmItemMapper::callOnItemDestroy()
{
    QEXT_DECL_D(QEXTMvvmItemMapper);
    if (d->m_active)
    {
        d->m_itemDestroyedSignal(d->m_item);
    }
}
