#ifndef _QEXTMVVMITEMMAPPER_H
#define _QEXTMVVMITEMMAPPER_H

#include <memory>
#include <qextMvvmItemListenerInterface.h>
#include <qextMvvmModelListener.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Provides notifications on various changes for a specific item.
//! QEXTMvvmItemMapper listens signals coming from the model (i.e. via QEXTMvvmModelMapper) and processes only whose
//! signals which are related to the given item. Notifies all interested subscribers about things
//! going with the item and its relatives.

class QEXT_MVVM_API QEXTMvvmItemMapper : public QEXTMvvmItemListenerInterface,
        private QEXTMvvmModelListener<QEXTMvvmSessionModel>
{
public:
    QEXTMvvmItemMapper(QEXTMvvmSessionItem* item);
    ~QEXTMvvmItemMapper();

    void setOnItemDestroy(Callbacks::item_t f, Callbacks::slot_t owner) override;
    void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner) override;
    void setOnPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner) override;
    void setOnChildPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner) override;
    void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) override;
    void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) override;
    void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) override;

    void unsubscribe(Callbacks::slot_t client) override;

    void setActive(bool value);

private:
    friend class QEXTMvvmSessionItem;
    void callOnItemDestroy();

    struct ItemMapperImpl;
    std::unique_ptr<ItemMapperImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMITEMMAPPER_H
