// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_LINKEDITEM_H
#define MVVM_STANDARDITEMS_LINKEDITEM_H

#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>

namespace ModelView {

//! Item to store a persistent link to other arbitrary items.

//! The identifier of the item intended for linking is stored as QExtMvvmDataRole on board of QExtMvvmLinkedItem
//! and can be used to find the corresponding item via QExtMvvmSessionModel::findItem machinery.
//! Provided mechanism is persistent and outlive serialization. Can be used to find items in
//! different models. For that being the case, models should use same QExtMvvmItemPool.

class QEXT_MVVM_API QExtMvvmLinkedItem : public QExtMvvmSessionItem {
public:
    QExtMvvmLinkedItem();

    void setLink(const QExtMvvmSessionItem* item);

    template <typename T = QExtMvvmSessionItem> T* get() const;
};

//! Returns item linked to given item. Works only in model context.

template <typename T> T* QExtMvvmLinkedItem::get() const
{
    return model() ? dynamic_cast<T*>(model()->findItem(data<std::string>())) : nullptr;
}

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_LINKEDITEM_H
