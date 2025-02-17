// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELUTILS_H
#define MVVM_VIEWMODEL_VIEWMODELUTILS_H

#include "qextMVVMGlobal.h"
#include <QModelIndexList>
#include <QVector>
#include <functional>
#include <vector>

class QVariant;

namespace ModelView {

class SessionItem;

namespace Utils {

//! Iterates through QAbstractItem model
QEXT_MVVM_API void iterate_model(const QAbstractItemModel* model, const QModelIndex& parent,
                                         const std::function<void(const QModelIndex& child)>& fun);

//! Returns vector of Qt roles corresponding to given ItemDataRole.
QEXT_MVVM_API QVector<int> ItemRoleToQtRole(int role);

//! Returns text color for given item.
QEXT_MVVM_API QVariant TextColorRole(const SessionItem& item);

//! Returns check state role of given item.
QEXT_MVVM_API QVariant CheckStateRole(const SessionItem& item);

//! Returns decoration role for given item.
QEXT_MVVM_API QVariant DecorationRole(const SessionItem& item);

//! Returns tooltip role for given item.
QEXT_MVVM_API QVariant ToolTipRole(const SessionItem& item);

//! Returns vector of underlying SessionItem's for given index list.
QEXT_MVVM_API std::vector<SessionItem*> ItemsFromIndex(const QModelIndexList& index_list);

//! Returns vector of underlying SessionItem's for given index list. Removes repetitions
QEXT_MVVM_API std::vector<SessionItem*>
UniqueItemsFromIndex(const QModelIndexList& index_list);

//! Returns vector of parent items from given index list.
//! Finds all SessionItems corresponding to given index list and collect their parents.
//! Function is usefull in the context of table-like views when we want to find compound items
//! (i.e. Layers) from table cells containing LayerItem's properties (i.e. thickness).
QEXT_MVVM_API std::vector<SessionItem*>
ParentItemsFromIndex(const QModelIndexList& index_list);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELUTILS_H
