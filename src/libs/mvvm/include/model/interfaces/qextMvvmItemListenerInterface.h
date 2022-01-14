#ifndef _QEXTMVVMINTERFACESITEMLISTENERINTERFACE_H
#define _QEXTMVVMINTERFACESITEMLISTENERINTERFACE_H

#include <qextMvvmCallbackTypes.h>

namespace ModelView
{

//! Interface to subscribe to various events happening with specific QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmItemListenerInterface
{
public:
    virtual ~QEXTMvvmItemListenerInterface() = default;

    virtual void setOnItemDestroy(QEXTMvvmCallbacks::item_t f, QEXTMvvmCallbacks::slot_t owner) = 0;

    //! Sets callback to be notified on item's data change.
    //! Callback will be called with (QEXTMvvmSessionItem*, data_role).

    virtual void setOnDataChange(QEXTMvvmCallbacks::item_int_t f, QEXTMvvmCallbacks::slot_t owner) = 0;

    //! Sets callback to be notified on item's property change.
    //! Callback will be called with (compound_item, property_name).

    virtual void setOnPropertyChange(QEXTMvvmCallbacks::item_str_t f, QEXTMvvmCallbacks::slot_t owner) = 0;

    //! Sets callback to be notified on item's children property change.
    //! Callback will be called with (compound_item, property_name). For MultiLayer containing the
    //! layer with "thickness" property, the signal will be triggered on thickness change using
    //! (layeritem*, "thickness") as callback parameters.

    virtual void setOnChildPropertyChange(QEXTMvvmCallbacks::item_str_t f, QEXTMvvmCallbacks::slot_t owner) = 0;

    //! Sets callback to be notified on child insertion.
    //! Callback will be called with (compound_item, tag, row). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer insertion with
    //! (multilayer*, {T_LAYER, row}) as callback parameters.

    virtual void setOnItemInserted(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner) = 0;

    //! Sets callback to be notified on child removal.
    //! Callback will be called with (compound_item, tag, row). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer removal with
    //! (multilayer*, {T_LAYER, oldrow}) as callback parameters.

    virtual void setOnItemRemoved(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner) = 0;

    //! Sets callback to be notified when row is about to be removed.
    //! Callback will be called with (compound_item, tagrow). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer deletion with
    //! (multilayer*, {T_LAYER, row}) as callback parameters.

    virtual void setOnAboutToRemoveItem(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner) = 0;

    //! Removes given client from all subscriptions.
    virtual void unsubscribe(QEXTMvvmCallbacks::slot_t client) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMINTERFACESITEMLISTENERINTERFACE_H
