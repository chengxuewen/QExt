#ifndef _QEXTMVVMVIEWMODELUTILS_H
#define _QEXTMVVMVIEWMODELUTILS_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

#include <QModelIndexList>
#include <QModelIndex>
#include <QVector>

class QStandardItemModel;
class QStandardItem;
class QVariant;

class QEXTMvvmViewItem;
class QEXTMvvmItem;

struct QEXT_MVVM_API QEXTMvvmViewModelUtils
{

//! Iterates through QAbstractItem model
    static void iterate_model(const QAbstractItemModel *model, const QModelIndex &parent,
                                     const QEXTFunction<void, const QModelIndex &> &fun);

//! Returns vector of Qt roles corresponding to given QEXTMvvmItem.
    static QVector<int> ItemRoleToQtRole(int role);

//! Returns text color for given item.
    static QVariant TextColorRole(const QEXTMvvmItem &item);

//! Returns check state role of given item.
    static QVariant CheckStateRole(const QEXTMvvmItem &item);

//! Returns decoration role for given item.
    static QVariant DecorationRole(const QEXTMvvmItem &item);

//! Returns tooltip role for given item.
    static QVariant ToolTipRole(const QEXTMvvmItem &item);

//! Returns vector of underlying QEXTMvvmItem's for given index list.
    static QVector<QEXTMvvmItem *> ItemsFromIndex(const QModelIndexList &index_list);

////! Returns vector of underlying QEXTMvvmItem's for given index list. Removes repetitions
//    static QVector<QEXTMvvmItem *>
//    UniqueItemsFromIndex(const QModelIndexList &index_list);

//! Returns vector of parent items from given index list.
//! Finds all SessionItems corresponding to given index list and collect their parents.
//! Function is usefull in the context of table-like views when we want to find compound items
//! (i.e. Layers) from table cells containing LayerItem's properties (i.e. thickness).
    static QVector<QEXTMvvmItem *>
    ParentItemsFromIndex(const QModelIndexList &index_list);

};


#endif // _QEXTMVVMVIEWMODELUTILS_H
