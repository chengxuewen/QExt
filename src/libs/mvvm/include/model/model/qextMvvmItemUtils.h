#ifndef _QEXTMVVMITEMUTILS_H
#define _QEXTMVVMITEMUTILS_H

#include <functional>
#include <qextMvvmGlobal.h>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItem;

namespace Utils
{

//! Iterates through item and all its children.
QEXT_MVVM_API void iterate(QEXTMvvmSessionItem* item, const std::function<void(QEXTMvvmSessionItem*)>& fun);

//! Iterates through all model indices and calls user function.
//! If function returns false for given index, iteration will not go down to children.
QEXT_MVVM_API void iterate_if(const QEXTMvvmSessionItem* item,
                                  const std::function<bool(const QEXTMvvmSessionItem*)>& fun);

//! Returns copy number of given item in it's parent hierarchy. Takes into account only items with
//! same modelType.
QEXT_MVVM_API int CopyNumber(const QEXTMvvmSessionItem* item);

//! Returns child at given index of parent. No tags are involved, index is considered
//! as global index in the combined array of all children.
QEXT_MVVM_API QEXTMvvmSessionItem* ChildAt(const QEXTMvvmSessionItem* parent, int index);

//! Returns index in children array corresponding to given child. No tags are involved,
//! index is considered as global index in the combined array of all children.
QEXT_MVVM_API int IndexOfChild(const QEXTMvvmSessionItem* parent, const QEXTMvvmSessionItem* child);

//! Returns vector of children representing top level items.

QEXT_MVVM_API std::vector<QEXTMvvmSessionItem*> TopLevelItems(const QEXTMvvmSessionItem& item);

//! Returns vector of children representing property items.

QEXT_MVVM_API std::vector<QEXTMvvmSessionItem*> SinglePropertyItems(const QEXTMvvmSessionItem& item);

//! Returns next sibling with same tag.

QEXT_MVVM_API QEXTMvvmSessionItem* FindNextSibling(QEXTMvvmSessionItem* item);

//! Returns previous sibling with same tag.

QEXT_MVVM_API QEXTMvvmSessionItem* FindPreviousSibling(QEXTMvvmSessionItem* item);

//! Finds next item to select
//! Method is used in the context of next item selection after given item was deleted.

QEXT_MVVM_API QEXTMvvmSessionItem* FindNextItemToSelect(QEXTMvvmSessionItem* item);

//! Returns true if 'candidate' is one of ancestor of given item.
QEXT_MVVM_API bool IsItemAncestor(const QEXTMvvmSessionItem* item, const QEXTMvvmSessionItem* candidate);

//! Returns vector with duplicates and 'nullptr' filtered out.
QEXT_MVVM_API std::vector<QEXTMvvmSessionItem*> UniqueItems(const std::vector<QEXTMvvmSessionItem*>& items);

//! Returns vector of items casted to given type.
template <typename T> std::vector<T*> CastedItems(const std::vector<QEXTMvvmSessionItem*>& items)
{
    std::vector<T*> result;
    for (auto item : items)
        if (auto casted_item = dynamic_cast<T*>(item); casted_item)
            result.push_back(casted_item);

    return result;
}

} // namespace Utils

} // namespace ModelView

#endif // _QEXTMVVMITEMUTILS_H
