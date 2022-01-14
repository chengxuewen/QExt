#ifndef _QEXTMVVMVIEWMODELVIEWMODELUTILS_H
#define _QEXTMVVMVIEWMODELVIEWMODELUTILS_H

#include <qextMvvmGlobal.h>

#include <QModelIndex>
#include <QModelIndexList>
#include <QVector>

#include <functional>
#include <vector>

class QStandardItemModel;
class QStandardItem;
class QVariant;

namespace ModelView
{

class QEXTMvvmViewItem;
class QEXTMvvmSessionItem;

namespace QEXTMvvmUtils
{

//! Iterates through QAbstractItem model
QEXT_MVVM_API void iterate_model(const QAbstractItemModel* model, const QModelIndex& parent,
                                         const std::function<void(const QModelIndex& child)>& fun);

//! Returns vector of Qt roles corresponding to given ItemDataRole.
QEXT_MVVM_API QVector<int> ItemRoleToQtRole(int role);

//! Returns text color for given item.
QEXT_MVVM_API QVariant TextColorRole(const QEXTMvvmSessionItem& item);

//! Returns check state role of given item.
QEXT_MVVM_API QVariant CheckStateRole(const QEXTMvvmSessionItem& item);

//! Returns decoration role for given item.
QEXT_MVVM_API QVariant DecorationRole(const QEXTMvvmSessionItem& item);

//! Returns tooltip role for given item.
QEXT_MVVM_API QVariant ToolTipRole(const QEXTMvvmSessionItem& item);

//! Returns vector of underlying QEXTMvvmSessionItem's for given index list.
QEXT_MVVM_API std::vector<QEXTMvvmSessionItem*> ItemsFromIndex(const QModelIndexList& index_list);

//! Returns vector of underlying QEXTMvvmSessionItem's for given index list. Removes repetitions
QEXT_MVVM_API std::vector<QEXTMvvmSessionItem*>
UniqueItemsFromIndex(const QModelIndexList& index_list);

//! Returns vector of parent items from given index list.
//! Finds all SessionItems corresponding to given index list and collect their parents.
//! Function is usefull in the context of table-like views when we want to find compound items
//! (i.e. Layers) from table cells containing LayerItem's properties (i.e. thickness).
QEXT_MVVM_API std::vector<QEXTMvvmSessionItem*>
ParentItemsFromIndex(const QModelIndexList& index_list);

} // namespace Utils

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELVIEWMODELUTILS_H
