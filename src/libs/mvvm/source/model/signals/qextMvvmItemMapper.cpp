// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmCallbackContainer.h>
#include <qextMvvmItemMapper.h>
#include <qextMvvmModelMapper.h>
#include <stdexcept>

using namespace ModelView;

struct QEXTMvvmItemMapper::ItemMapperImpl {
    QEXTMvvmItemMapper* m_itemMapper{nullptr};
    Signal<QEXTMvvmCallbacks::item_t> m_on_item_destroy;
    Signal<QEXTMvvmCallbacks::item_int_t> m_on_data_change;
    Signal<QEXTMvvmCallbacks::item_str_t> m_on_property_change;
    Signal<QEXTMvvmCallbacks::item_str_t> m_on_child_property_change;
    Signal<QEXTMvvmCallbacks::item_tagrow_t> m_on_item_inserted;
    Signal<QEXTMvvmCallbacks::item_tagrow_t> m_on_item_removed;
    Signal<QEXTMvvmCallbacks::item_tagrow_t> m_on_about_to_remove_item;

    bool m_active{true};
    QEXTMvvmSessionItem* m_item{nullptr};

    ItemMapperImpl(QEXTMvvmItemMapper* item_mapper) : m_itemMapper(item_mapper) {}

    void unsubscribe(QEXTMvvmCallbacks::slot_t client)
    {
        m_on_item_destroy.remove_client(client);
        m_on_data_change.remove_client(client);
        m_on_property_change.remove_client(client);
        m_on_child_property_change.remove_client(client);
        m_on_item_inserted.remove_client(client);
        m_on_item_removed.remove_client(client);
        m_on_about_to_remove_item.remove_client(client);
    }

    int nestlingDepth(QEXTMvvmSessionItem* item, int level = 0)
    {
        if (item == nullptr || item == m_itemMapper->model()->rootItem())
            return -1;
        if (item == m_item)
            return level;
        return nestlingDepth(item->parent(), level + 1);
    }

    //! Processes signals from the model when item data changed.

    void processDataChange(QEXTMvvmSessionItem* item, int role)
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

    void processItemInserted(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    {
        if (parent == m_item)
            callOnItemInserted(m_item, tagrow);
    }

    void processItemRemoved(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    {
        if (parent == m_item)
            callOnItemRemoved(m_item, tagrow);
    }

    void processAboutToRemoveItem(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    {
        if (parent == m_item)
            callOnAboutToRemoveItem(m_item, tagrow);
    }

    //! Notifies all callbacks subscribed to "item data is changed" event.

    void callOnDataChange(QEXTMvvmSessionItem* item, int role)
    {
        if (m_active)
            m_on_data_change(item, role);
    }

    //! Notifies all callbacks subscribed to "item property is changed" event.

    void callOnPropertyChange(QEXTMvvmSessionItem* item, std::string property_name)
    {
        if (m_active)
            m_on_property_change(item, property_name);
    }

    //! Notifies all callbacks subscribed to "child property changed" event.

    void callOnChildPropertyChange(QEXTMvvmSessionItem* item, std::string property_name)
    {
        if (m_active)
            m_on_child_property_change(item, property_name);
    }

    //! Notifies all callbacks subscribed to "on row inserted" event.

    void callOnItemInserted(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    {
        if (m_active)
            m_on_item_inserted(parent, tagrow);
    }

    //! Notifies all callbacks subscribed to "on row removed" event.

    void callOnItemRemoved(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    {
        if (m_active)
            m_on_item_removed(parent, tagrow);
    }

    //! Notifies all callbacks subscribed to "on row about to be removed".

    void callOnAboutToRemoveItem(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    {
        if (m_active)
            m_on_about_to_remove_item(parent, tagrow);
    }
};

QEXTMvvmItemMapper::QEXTMvvmItemMapper(QEXTMvvmSessionItem* item)
    : QEXTMvvmModelListener(item->model()), p_impl(make_unique<ItemMapperImpl>(this))
{
    if (!item)
        throw std::runtime_error("ItemMapper::ItemMapper() -> Not initialized item");

    if (!item->model())
        throw std::runtime_error("ItemMapper::ItemMapper() -> Item doesn't have model");

    p_impl->m_item = item;

    auto on_data_change = [this](QEXTMvvmSessionItem* item, int role) { p_impl->processDataChange(item, role); };
    QEXTMvvmModelListener::setOnDataChange(on_data_change);

    auto on_item_inserted = [this](QEXTMvvmSessionItem* item, QEXTMvvmTagRow tagrow) {
        p_impl->processItemInserted(item, tagrow);
    };
    QEXTMvvmModelListener::setOnItemInserted(on_item_inserted, this);

    auto on_item_removed = [this](QEXTMvvmSessionItem* item, QEXTMvvmTagRow tagrow) {
        p_impl->processItemRemoved(item, tagrow);
    };
    QEXTMvvmModelListener::setOnItemRemoved(on_item_removed, this);

    auto on_about_to_remove_item = [this](QEXTMvvmSessionItem* item, QEXTMvvmTagRow tagrow) {
        p_impl->processAboutToRemoveItem(item, tagrow);
    };
    QEXTMvvmModelListener::setOnAboutToRemoveItem(on_about_to_remove_item, this);
}

QEXTMvvmItemMapper::~QEXTMvvmItemMapper() = default;

void QEXTMvvmItemMapper::setOnItemDestroy(QEXTMvvmCallbacks::item_t f, QEXTMvvmCallbacks::slot_t owner)
{
    p_impl->m_on_item_destroy.connect(std::move(f), owner);
}

void QEXTMvvmItemMapper::setOnDataChange(QEXTMvvmCallbacks::item_int_t f, QEXTMvvmCallbacks::slot_t owner)
{
    p_impl->m_on_data_change.connect(std::move(f), owner);
}

void QEXTMvvmItemMapper::setOnPropertyChange(QEXTMvvmCallbacks::item_str_t f, QEXTMvvmCallbacks::slot_t owner)
{
    p_impl->m_on_property_change.connect(std::move(f), owner);
}

void QEXTMvvmItemMapper::setOnChildPropertyChange(QEXTMvvmCallbacks::item_str_t f, QEXTMvvmCallbacks::slot_t owner)
{
    p_impl->m_on_child_property_change.connect(std::move(f), owner);
}

void QEXTMvvmItemMapper::setOnItemInserted(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner)
{
    p_impl->m_on_item_inserted.connect(std::move(f), owner);
}

void QEXTMvvmItemMapper::setOnItemRemoved(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner)
{
    p_impl->m_on_item_removed.connect(std::move(f), owner);
}

void QEXTMvvmItemMapper::setOnAboutToRemoveItem(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner)
{
    p_impl->m_on_about_to_remove_item.connect(std::move(f), owner);
}

void QEXTMvvmItemMapper::unsubscribe(QEXTMvvmCallbacks::slot_t client)
{
    p_impl->unsubscribe(client);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void QEXTMvvmItemMapper::setActive(bool value)
{
    p_impl->m_active = value;
}

//! Calls all callbacks subscribed to "item is destroyed" event.

void QEXTMvvmItemMapper::callOnItemDestroy()
{
    if (p_impl->m_active)
        p_impl->m_on_item_destroy(p_impl->m_item);
}
