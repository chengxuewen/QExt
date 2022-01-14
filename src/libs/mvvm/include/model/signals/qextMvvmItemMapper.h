#ifndef _QEXTMVVMSIGNALSITEMMAPPER_H
#define _QEXTMVVMSIGNALSITEMMAPPER_H

#include <qextMvvmItemListenerInterface.h>
#include <qextMvvmModelListener.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Provides notifications on various changes for a specific item.
//! ItemMapper listens signals coming from the model (i.e. via ModelMapper) and processes only whose
//! signals which are related to the given item. Notifies all interested subscribers about things
//! going with the item and its relatives.

class QEXT_MVVM_API QEXTMvvmItemMapper : public QEXTMvvmItemListenerInterface,
        private QEXTMvvmModelListener<QEXTMvvmSessionModel>
{
public:
    QEXTMvvmItemMapper(QEXTMvvmSessionItem* item);
    ~QEXTMvvmItemMapper();

    void setOnItemDestroy(QEXTMvvmCallbacks::item_t f, QEXTMvvmCallbacks::slot_t owner) override;
    void setOnDataChange(QEXTMvvmCallbacks::item_int_t f, QEXTMvvmCallbacks::slot_t owner) override;
    void setOnPropertyChange(QEXTMvvmCallbacks::item_str_t f, QEXTMvvmCallbacks::slot_t owner) override;
    void setOnChildPropertyChange(QEXTMvvmCallbacks::item_str_t f, QEXTMvvmCallbacks::slot_t owner) override;
    void setOnItemInserted(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner) override;
    void setOnItemRemoved(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner) override;
    void setOnAboutToRemoveItem(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t owner) override;

    void unsubscribe(QEXTMvvmCallbacks::slot_t client) override;

    void setActive(bool value);

private:
    friend class QEXTMvvmSessionItem;
    void callOnItemDestroy();

    struct ItemMapperImpl;
    std::unique_ptr<ItemMapperImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMSIGNALSITEMMAPPER_H
