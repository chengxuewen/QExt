// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemListenerBase.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmItemMapper.h>

ModelView::QEXTMvvmItemListenerBase::QEXTMvvmItemListenerBase(ModelView::QEXTMvvmSessionItem* item)
{
    setItem(item);
}

ModelView::QEXTMvvmItemListenerBase::~QEXTMvvmItemListenerBase()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

void ModelView::QEXTMvvmItemListenerBase::setItem(ModelView::QEXTMvvmSessionItem* item)
{
    if (m_item == item)
        return;

    unsubscribe_from_current();

    m_item = item;

    if (!m_item)
        return;

    auto on_item_destroy = [this](auto) {
        m_item = nullptr;
        unsubscribe();
    };
    m_item->mapper()->setOnItemDestroy(on_item_destroy, this);

    subscribe();
}

void ModelView::QEXTMvvmItemListenerBase::setOnItemDestroy(ModelView::Callbacks::item_t f)
{
    item()->mapper()->setOnItemDestroy(f, this);
}

//! Sets callback to be notified on item's data change.
//! Callback will be called with (QEXTMvvmSessionItem*, data_role).

void ModelView::QEXTMvvmItemListenerBase::setOnDataChange(ModelView::Callbacks::item_int_t f)
{
    item()->mapper()->setOnDataChange(f, this);
}

//! Sets callback to be notified on item's property change.
//! Callback will be called with (compound_item, property_name).

void ModelView::QEXTMvvmItemListenerBase::setOnPropertyChange(ModelView::Callbacks::item_str_t f)
{
    item()->mapper()->setOnPropertyChange(f, this);
}

//! Sets callback to be notified on item's children property change.
//! Callback will be called with (compound_item, property_name). For MultiLayer containing the
//! layer with "thickness" property, the signal will be triggered on thickness change using
//! (layeritem*, "thickness") as callback parameters.

void ModelView::QEXTMvvmItemListenerBase::setOnChildPropertyChange(ModelView::Callbacks::item_str_t f)
{
    item()->mapper()->setOnChildPropertyChange(f, this);
}

//! Sets callback to be notified on child insertion.
//! Callback will be called with (compound_item, tag, row). For MultiLayer containing the T_LAYERS
//! tag, the signal will be triggered on layer insertion with
//! (multilayer*, {T_LAYER, row}) as callback parameters.

void ModelView::QEXTMvvmItemListenerBase::setOnItemInserted(ModelView::Callbacks::item_tagrow_t f)
{
    item()->mapper()->setOnItemInserted(f, this);
}

//! Sets callback to be notified on child removal.
//! Callback will be called with (compound_item, tag, row). For MultiLayer containing the T_LAYERS
//! tag, the signal will be triggered on layer removal with
//! (multilayer*, {T_LAYER, oldrow}) as callback parameters.

void ModelView::QEXTMvvmItemListenerBase::setOnItemRemoved(ModelView::Callbacks::item_tagrow_t f)
{
    item()->mapper()->setOnItemRemoved(f, this);
}

void ModelView::QEXTMvvmItemListenerBase::setOnAboutToRemoveItem(ModelView::Callbacks::item_tagrow_t f)
{
    item()->mapper()->setOnAboutToRemoveItem(f, this);
}

//! Sets callback to be notified when row is about to be removed.
//! Callback will be called with (compound_item, tagrow). For MultiLayer containing the T_LAYERS
//! tag, the signal will be triggered on layer deletion with
//! (multilayer*, {T_LAYER, row}) as callback parameters.

ModelView::QEXTMvvmSessionItem* ModelView::QEXTMvvmItemListenerBase::item() const
{
    return m_item;
}

void ModelView::QEXTMvvmItemListenerBase::unsubscribe_from_current()
{
    if (!m_item)
        return;

    unsubscribe();

    m_item->mapper()->unsubscribe(this);
}
