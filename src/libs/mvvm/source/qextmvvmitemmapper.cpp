#include <qextmvvmitemmapper.h>
#include <qextmvvmitemmapper_p.h>
#include <qextmvvmitem.h>
#include <qextmvvmmodel.h>

#include <QDebug>

QEXT_USE_NAMESPACE

QEXTMvvmItemMapperPrivate::QEXTMvvmItemMapperPrivate(QEXTMvvmItemMapper *qq)
    : QEXTObjectPrivate(qq)
{
    m_active = true;
    m_item = QEXT_NULLPTR;
}

QEXTMvvmItemMapperPrivate::~QEXTMvvmItemMapperPrivate()
{

}

void QEXTMvvmItemMapperPrivate::unsubscribe(QEXTMvvmSlot_t client)
{
    m_on_item_destroy.remove_client(client);
    m_on_data_change.remove_client(client);
    m_on_property_change.remove_client(client);
    m_on_child_property_change.remove_client(client);
    m_on_item_inserted.remove_client(client);
    m_on_item_removed.remove_client(client);
    m_on_about_to_remove_item.remove_client(client);
}

int QEXTMvvmItemMapperPrivate::nestlingDepth(QEXTMvvmItem *item, int level)
{
    QEXT_Q(QEXTMvvmItemMapper);
    if (!item || item == q->model()->rootItem()) {
        return -1;
    }
    if (item == m_item) {
        return level;
    }
    return this->nestlingDepth(item->parent(), level + 1);
}

void QEXTMvvmItemMapperPrivate::processDataChange(QEXTMvvmItem *item, int role)
{
    int nestling = this->nestlingDepth(item);

    // own item data changed
    if (nestling == 0) {
        this->callOnDataChange(item, role);
    }

    // data of item's property changed
    if (nestling == 1) {
        this->callOnPropertyChange(m_item, m_item->tagOfItem(item));
    }

    // child property changed
    if (nestling == 2) {
        QEXTMvvmItem *parent = item->parent();
        if (parent) {
            this->callOnChildPropertyChange(parent, parent->tagOfItem(item));
        }
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
        m_on_data_change(item, role);
}

void QEXTMvvmItemMapperPrivate::callOnPropertyChange(QEXTMvvmItem *item, std::string property_name)
{
    if (m_active)
        m_on_property_change(item, property_name);
}

void QEXTMvvmItemMapperPrivate::callOnChildPropertyChange(QEXTMvvmItem *item, std::string property_name)
{
    if (m_active)
        m_on_child_property_change(item, property_name);
}

void QEXTMvvmItemMapperPrivate::callOnItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (m_active)
        m_on_item_inserted(parent, tagrow);
}

void QEXTMvvmItemMapperPrivate::callOnItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (m_active)
        m_on_item_removed(parent, tagrow);
}

void QEXTMvvmItemMapperPrivate::callOnAboutToRemoveItem(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    if (m_active)
        m_on_about_to_remove_item(parent, tagrow);
}



QEXTMvvmItemMapper::QEXTMvvmItemMapper(QEXTMvvmItem *item)
    : QEXTMvvmModelListener(item->model()), QEXTObject(*(new QEXTMvvmItemMapperPrivate(this)))
{
    QEXT_D(QEXTMvvmItemMapper);
    if (!item) {
        qFatal("QEXTMvvmItemMapper::QEXTMvvmItemMapper() -> Not initialized item");
    }
    if (!item->model()) {
        qFatal("QEXTMvvmItemMapper::QEXTMvvmItemMapper() -> Item doesn't have model");
    }
    d->m_item = item;
    //    QEXTMvvmModelListener::setOnDataChange();
}

QEXTMvvmItemMapper::~QEXTMvvmItemMapper()
{

}

void QEXTMvvmItemMapper::setOnItemDestroy(QEXTMvvmItem_t f, QEXTMvvmSlot_t owner)
{

}

void QEXTMvvmItemMapper::setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t owner)
{

}

void QEXTMvvmItemMapper::setOnPropertyChange(QEXTMvvmItem_str_t f, QEXTMvvmSlot_t owner)
{

}

void QEXTMvvmItemMapper::setOnChildPropertyChange(QEXTMvvmItem_str_t f, QEXTMvvmSlot_t owner)
{

}

void QEXTMvvmItemMapper::setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner)
{

}

void QEXTMvvmItemMapper::setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner)
{

}

void QEXTMvvmItemMapper::setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner)
{

}

void QEXTMvvmItemMapper::unsubscribe(QEXTMvvmSlot_t client)
{

}

void QEXTMvvmItemMapper::setActive(bool value)
{

}
