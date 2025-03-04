// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/viewmodelbase.h"
#include "viewmodel/viewmodel/standardviewitems.h"
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmViewModelBase::ViewModelBaseImpl {
    QExtMvvmViewModelBase* model{nullptr};
    QExtUniquePointer<QExtMvvmViewItem> root;
    ViewModelBaseImpl(QExtMvvmViewModelBase* model) : model(model) {}

    bool item_belongs_to_model(QExtMvvmViewItem* item)
    {
        return model->indexFromItem(item).isValid() || item == model->rootItem();
    }
};

QExtMvvmViewModelBase::QExtMvvmViewModelBase(QObject* parent)
    : QAbstractItemModel(parent), p_impl(qextMakeUnique<ViewModelBaseImpl>(this))
{
    beginResetModel();
    setRootViewItem(qextMakeUnique<QExtMvvmRootViewItem>(nullptr));
    endResetModel();
}

QExtMvvmViewModelBase::~QExtMvvmViewModelBase() = default;

QModelIndex QExtMvvmViewModelBase::index(int row, int column, const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent) ? itemFromIndex(parent) : rootItem();
    const bool is_valid_row = row >= 0 && row < rowCount(parent);
    const bool is_valid_column = column >= 0 && column < columnCount(parent);
    return is_valid_row && is_valid_column
               ? createIndex(row, column, parent_item->child(row, column))
               : QModelIndex();
}

QModelIndex QExtMvvmViewModelBase::parent(const QModelIndex& child) const
{
    if (auto child_item = itemFromIndex(child); child_item) {
        auto parent_item = child_item->parent();
        return parent_item == rootItem()
                   ? QModelIndex()
                   : createIndex(parent_item->row(), parent_item->column(), parent_item);
    }

    return QModelIndex();
}

int QExtMvvmViewModelBase::rowCount(const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent);
    return parent_item ? parent_item->rowCount() : rootItem()->rowCount();
}

int QExtMvvmViewModelBase::columnCount(const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent);
    return parent_item ? parent_item->columnCount() : rootItem()->columnCount();
}

QVariant QExtMvvmViewModelBase::data(const QModelIndex& index, int role) const
{
    if (!rootItem())
        return QVariant();

    auto item = itemFromIndex(index);
    return item ? item->data(role) : QVariant();
}

bool QExtMvvmViewModelBase::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    if (auto item = itemFromIndex(index); item) {
        bool result = item->setData(value, role);
        if (result)
            dataChanged(index, index, QVector<int>() << role);
        return result;
    }

    return false;
}

//! Returns a pointer to invisible root item.

QExtMvvmViewItem* QExtMvvmViewModelBase::rootItem() const
{
    return p_impl->root.get();
}

//! Returns a pointer to the RefViewItem associated with the given index.
//! If index is invalid, returns nullptr.

QExtMvvmViewItem* QExtMvvmViewModelBase::itemFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? static_cast<QExtMvvmViewItem*>(index.internalPointer()) : nullptr;
}

//! Returns the QModelIndex associated with the given item.

QModelIndex QExtMvvmViewModelBase::indexFromItem(const QExtMvvmViewItem* item) const
{
    return item && item->parent()
               ? createIndex(item->row(), item->column(), const_cast<QExtMvvmViewItem*>(item))
               : QModelIndex();
}

void QExtMvvmViewModelBase::removeRow(QExtMvvmViewItem* parent, int row)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error(
            "Error in QExtMvvmViewModelBase: attempt to use parent from another model");

    beginRemoveRows(indexFromItem(parent), row, row);
    parent->removeRow(row);
    endRemoveRows();
}

void QExtMvvmViewModelBase::clearRows(QExtMvvmViewItem* parent)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error(
            "Error in QExtMvvmViewModelBase: attempt to use parent from another model");

    if (!parent->rowCount())
        return;

    beginRemoveRows(indexFromItem(parent), 0, parent->rowCount() - 1);
    parent->clear();
    endRemoveRows();
}

//! Insert a row of items at index 'row' to given parent.

void QExtMvvmViewModelBase::insertRow(QExtMvvmViewItem* parent, int row,
                              std::vector<QExtUniquePointer<QExtMvvmViewItem>> items)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error(
            "Error in QExtMvvmViewModelBase: attempt to use parent from another model");

    beginInsertRows(indexFromItem(parent), row, row);
    parent->insertRow(row, std::move(items));
    endInsertRows();
}

//! Appends row of items to given parent.

void QExtMvvmViewModelBase::appendRow(QExtMvvmViewItem* parent, std::vector<QExtUniquePointer<QExtMvvmViewItem>> items)
{
    insertRow(parent, parent->rowCount(), std::move(items));
}

//! Returns the item flags for the given index.

Qt::ItemFlags QExtMvvmViewModelBase::flags(const QModelIndex& index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    if (auto item = itemFromIndex(index); item)
        result |= item->flags();
    return result;
}

//! Sets new root item. Previous item will be deleted, model will be reset.

void QExtMvvmViewModelBase::setRootViewItem(QExtUniquePointer<QExtMvvmViewItem> root_item)
{
    p_impl->root = std::move(root_item);
}
