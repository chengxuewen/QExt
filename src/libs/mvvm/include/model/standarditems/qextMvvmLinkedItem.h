#ifndef _QEXTMVVMLINKEDITEM_H
#define _QEXTMVVMLINKEDITEM_H

#include <qextMvvmItem.h>
#include <qextMvvmModel.h>


//! Item to store a persistent link to other arbitrary items.

//! The identifier of the item intended for linking is stored as QEXTMvvmDataRole on board of QEXTMvvmLinkedItem
//! and can be used to find the corresponding item via QEXTMvvmModel::findItem machinery.
//! Provided mechanism is persistent and outlive serialization. Can be used to find items in
//! different models. For that being the case, models should use same QEXTMvvmItemPool.

class QEXT_MVVM_API QEXTMvvmLinkedItem : public QEXTMvvmItem
{
public:
    QEXTMvvmLinkedItem();

    void setLink(const QEXTMvvmItem* item);

    template <typename T = QEXTMvvmItem> T* get() const;
};

//! Returns item linked to given item. Works only in model context.

template <typename T> T* QEXTMvvmLinkedItem::get() const
{
    return model() ? dynamic_cast<T*>(model()->findItem(data<QString>())) : nullptr;
}

#endif // _QEXTMVVMLINKEDITEM_H
