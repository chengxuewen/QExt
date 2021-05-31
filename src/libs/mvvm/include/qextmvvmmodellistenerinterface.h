#ifndef QEXTMVVMMODELLISTENERINTERFACE_H
#define QEXTMVVMMODELLISTENERINTERFACE_H

#include <qextmvvmglobal.h>
#include <qextmvvmcallback.h>



class QEXT_MVVM_API QEXTMvvmModelListenerInterface
{
public:
    virtual ~QEXTMvvmModelListenerInterface() QEXT_EQ_DEFAULT;


    //! Sets callback to be notified on item's data change. The callback will be called
    //! with (SessionItem*, data_role).
    virtual void setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t client) = 0;

    //! Sets callback to be notified on item insert. The callback will be called with
    //! (SessionItem* parent, tagrow), where 'tagrow' denotes inserted child position.
    virtual void setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client) = 0;

    //! Sets callback to be notified on item remove. The callback will be called with
    //! (SessionItem* parent, tagrow), where 'tagrow' denotes child position before the removal.
    virtual void setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client) = 0;

    //! Sets callback to be notified when the item is about to be removed. The callback will be
    //! called with (SessionItem* parent, tagrow), where 'tagrow' denotes child position being
    //! removed.
    virtual void setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client) = 0;

    //! Sets the callback for notifications on model destruction.
    virtual void setOnModelDestroyed(QEXTMvvmModel_t f, QEXTMvvmSlot_t client) = 0;

    //! Sets the callback to be notified just before the reset of the root item.
    virtual void setOnModelAboutToBeReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client) = 0;

    //! Sets the callback to be notified right after the root item recreation.
    virtual void setOnModelReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client) = 0;

    //! Removes given client from all subscriptions.
    virtual void unsubscribe(QEXTMvvmSlot_t client) = 0;
};



#endif // QEXTMVVMMODELLISTENERINTERFACE_H
