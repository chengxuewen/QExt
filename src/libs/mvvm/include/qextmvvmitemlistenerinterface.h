#ifndef QEXTMVVMITEMLISTENERINTERFACE_H
#define QEXTMVVMITEMLISTENERINTERFACE_H

#include <qextmvvmglobal.h>
#include <qextmvvmcallback.h>



class QEXT_MVVM_API QEXTMvvmItemListenerInterface
{
public:
    virtual ~QEXTMvvmItemListenerInterface() QEXT_EQ_DEFAULT;

    virtual void setOnItemDestroy(QEXTMvvmItem_t f, QEXTMvvmSlot_t owner) = 0;

    //! Sets callback to be notified on item's data change.
    //! Callback will be called with (SessionItem*, data_role).
    virtual void setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t owner) = 0;

    //! Sets callback to be notified on item's property change.
    //! Callback will be called with (compound_item, property_name).
    virtual void setOnPropertyChange(QEXTMvvmItem_str_t f, QEXTMvvmSlot_t owner) = 0;

    //! Sets callback to be notified on item's children property change.
    //! Callback will be called with (compound_item, property_name). For MultiLayer containing the
    //! layer with "thickness" property, the signal will be triggered on thickness change using
    //! (layeritem*, "thickness") as callback parameters.
    virtual void setOnChildPropertyChange(QEXTMvvmItem_str_t f, QEXTMvvmSlot_t owner) = 0;

    //! Sets callback to be notified on child insertion.
    //! Callback will be called with (compound_item, tag, row). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer insertion with
    //! (multilayer*, {T_LAYER, row}) as callback parameters.
    virtual void setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner) = 0;

    //! Sets callback to be notified on child removal.
    //! Callback will be called with (compound_item, tag, row). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer removal with
    //! (multilayer*, {T_LAYER, oldrow}) as callback parameters.
    virtual void setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner) = 0;

    //! Sets callback to be notified when row is about to be removed.
    //! Callback will be called with (compound_item, tagrow). For MultiLayer containing the
    //! T_LAYERS tag, the signal will be triggered on layer deletion with
    //! (multilayer*, {T_LAYER, row}) as callback parameters.
    virtual void setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner) = 0;

    //! Removes given client from all subscriptions.
    virtual void unsubscribe(QEXTMvvmSlot_t client) = 0;
};



#endif // QEXTMVVMITEMLISTENERINTERFACE_H
