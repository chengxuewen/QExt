#ifndef _QEXTMVVMSTANDARDITEMSLINKEDITEM_H
#define _QEXTMVVMSTANDARDITEMSLINKEDITEM_H

#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>

namespace ModelView
{

//! Item to store a persistent link to other arbitrary items.

//! The identifier of the item intended for linking is stored as DataRole on board of LinkedItem
//! and can be used to find the corresponding item via SessionModel::findItem machinery.
//! Provided mechanism is persistent and outlive serialization. Can be used to find items in
//! different models. For that being the case, models should use same ItemPool.

class QEXT_MVVM_API QEXTMvvmLinkedItem : public QEXTMvvmSessionItem
{
public:
    QEXTMvvmLinkedItem();

    void setLink(const QEXTMvvmSessionItem* item);

    template <typename T = QEXTMvvmSessionItem> T* get() const;
};

//! Returns item linked to given item. Works only in model context.

template <typename T> T* QEXTMvvmLinkedItem::get() const
{
    return model() ? dynamic_cast<T*>(model()->findItem(data<std::string>())) : nullptr;
}

} // namespace ModelView

#endif // _QEXTMVVMSTANDARDITEMSLINKEDITEM_H
