// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCallbackContainer.h>
#include <qextMvvmModelMapper.h>

using namespace ModelView;

struct QEXTMvvmModelMapper::ModelMapperImpl {
    Signal<QEXTMvvmCallbacks::item_int_t> m_on_data_change;
    Signal<QEXTMvvmCallbacks::item_tagrow_t> m_on_item_inserted;
    Signal<QEXTMvvmCallbacks::item_tagrow_t> m_on_item_removed;
    Signal<QEXTMvvmCallbacks::item_tagrow_t> m_on_item_about_removed;
    Signal<QEXTMvvmCallbacks::model_t> m_on_model_destroyed;
    Signal<QEXTMvvmCallbacks::model_t> m_on_model_about_reset;
    Signal<QEXTMvvmCallbacks::model_t> m_on_model_reset;

    bool m_active{true};
    QEXTMvvmSessionModel* m_model{nullptr};

    ModelMapperImpl(QEXTMvvmSessionModel* model) : m_model(model){};

    void unsubscribe(QEXTMvvmCallbacks::slot_t client)
    {
        m_on_data_change.remove_client(client);
        m_on_item_inserted.remove_client(client);
        m_on_item_removed.remove_client(client);
        m_on_item_about_removed.remove_client(client);
        m_on_model_destroyed.remove_client(client);
        m_on_model_about_reset.remove_client(client);
        m_on_model_reset.remove_client(client);
    }
};

QEXTMvvmModelMapper::QEXTMvvmModelMapper(QEXTMvvmSessionModel* model) : p_impl(make_unique<ModelMapperImpl>(model)) {}

QEXTMvvmModelMapper::~QEXTMvvmModelMapper() = default;

//! Sets callback to be notified on item's data change. The callback will be called
//! with (QEXTMvvmSessionItem*, data_role).

void QEXTMvvmModelMapper::setOnDataChange(QEXTMvvmCallbacks::item_int_t f, QEXTMvvmCallbacks::slot_t client)
{
    p_impl->m_on_data_change.connect(std::move(f), client);
}

//! Sets callback to be notified on item insert. The callback will be called with
//! (QEXTMvvmSessionItem* parent, tagrow), where 'tagrow' denotes inserted child position.

void QEXTMvvmModelMapper::setOnItemInserted(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t client)
{
    p_impl->m_on_item_inserted.connect(std::move(f), client);
}

//! Sets callback to be notified on item remove. The callback will be called with
//! (QEXTMvvmSessionItem* parent, tagrow), where 'tagrow' denotes child position before the removal.

void QEXTMvvmModelMapper::setOnItemRemoved(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t client)
{
    p_impl->m_on_item_removed.connect(std::move(f), client);
}

//! Sets callback to be notified when the item is about to be removed. The callback will be called
//! with (QEXTMvvmSessionItem* parent, tagrow), where 'tagrow' denotes child position being removed.

void QEXTMvvmModelMapper::setOnAboutToRemoveItem(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t client)
{
    p_impl->m_on_item_about_removed.connect(std::move(f), client);
}

//! Sets the callback for notifications on model destruction.

void QEXTMvvmModelMapper::setOnModelDestroyed(QEXTMvvmCallbacks::model_t f, QEXTMvvmCallbacks::slot_t client)
{
    p_impl->m_on_model_destroyed.connect(std::move(f), client);
}

//! Sets the callback to be notified just before the reset of the root item.

void QEXTMvvmModelMapper::setOnModelAboutToBeReset(QEXTMvvmCallbacks::model_t f, QEXTMvvmCallbacks::slot_t client)
{
    p_impl->m_on_model_about_reset.connect(std::move(f), client);
}

//! Sets the callback to be notified right after the root item recreation.

void QEXTMvvmModelMapper::setOnModelReset(QEXTMvvmCallbacks::model_t f, QEXTMvvmCallbacks::slot_t client)
{
    p_impl->m_on_model_reset.connect(std::move(f), client);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void QEXTMvvmModelMapper::setActive(bool value)
{
    p_impl->m_active = value;
}

//! Removes given client from all subscriptions.

void QEXTMvvmModelMapper::unsubscribe(QEXTMvvmCallbacks::slot_t client)
{
    p_impl->unsubscribe(client);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void QEXTMvvmModelMapper::callOnDataChange(QEXTMvvmSessionItem* item, int role)
{
    if (p_impl->m_active)
        p_impl->m_on_data_change(item, role);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void QEXTMvvmModelMapper::callOnItemInserted(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
{
    if (p_impl->m_active)
        p_impl->m_on_item_inserted(parent, tagrow);
}

void QEXTMvvmModelMapper::callOnItemRemoved(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
{
    if (p_impl->m_active)
        p_impl->m_on_item_removed(parent, tagrow);
}

void QEXTMvvmModelMapper::callOnItemAboutToBeRemoved(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
{
    if (p_impl->m_active)
        p_impl->m_on_item_about_removed(parent, tagrow);
}

void QEXTMvvmModelMapper::callOnModelDestroyed()
{
    p_impl->m_on_model_destroyed(p_impl->m_model);
}

void QEXTMvvmModelMapper::callOnModelAboutToBeReset()
{
    p_impl->m_on_model_about_reset(p_impl->m_model);
}

void QEXTMvvmModelMapper::callOnModelReset()
{
    p_impl->m_on_model_reset(p_impl->m_model);
}
