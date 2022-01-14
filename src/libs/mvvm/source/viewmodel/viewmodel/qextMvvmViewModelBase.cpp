// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/qextMvvmStandardViewItems.h>
#include <viewmodel/qextMvvmViewModelBase.h>
#include <stdexcept>

using namespace ModelView;

struct QEXTMvvmViewModelBase::ViewModelBaseImpl {
    QEXTMvvmViewModelBase* model{nullptr};
    std::unique_ptr<QEXTMvvmViewItem> root;
    ViewModelBaseImpl(QEXTMvvmViewModelBase* model) : model(model) {}

    bool item_belongs_to_model(QEXTMvvmViewItem* item)
    {
        return model->indexFromItem(item).isValid() || item == model->rootItem();
    }
};

QEXTMvvmViewModelBase::QEXTMvvmViewModelBase(QObject* parent)
    : QAbstractItemModel(parent), p_impl(make_unique<ViewModelBaseImpl>(this))
{
    beginResetModel();
    setRootViewItem(make_unique<QEXTMvvmRootViewItem>(nullptr));
    endResetModel();
}

QEXTMvvmViewModelBase::~QEXTMvvmViewModelBase() = default;

QModelIndex QEXTMvvmViewModelBase::index(int row, int column, const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent) ? itemFromIndex(parent) : rootItem();
    const bool is_valid_row = row >= 0 && row < rowCount(parent);
    const bool is_valid_column = column >= 0 && column < columnCount(parent);
    return is_valid_row && is_valid_column
               ? createIndex(row, column, parent_item->child(row, column))
               : QModelIndex();
}

QModelIndex QEXTMvvmViewModelBase::parent(const QModelIndex& child) const
{
    if (auto child_item = itemFromIndex(child); child_item) {
        auto parent_item = child_item->parent();
        return parent_item == rootItem()
                   ? QModelIndex()
                   : createIndex(parent_item->row(), parent_item->column(), parent_item);
    }

    return QModelIndex();
}

int QEXTMvvmViewModelBase::rowCount(const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent);
    int count = parent_item ? parent_item->rowCount() : rootItem()->rowCount();
    return count;
}

int QEXTMvvmViewModelBase::columnCount(const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent);
    int count = parent_item ? parent_item->columnCount() : rootItem()->columnCount();
    return count;
}

QVariant QEXTMvvmViewModelBase::data(const QModelIndex& index, int role) const
{
    if (!rootItem())
        return QVariant();

    auto item = itemFromIndex(index);
    return item ? item->data(role) : QVariant();
}

bool QEXTMvvmViewModelBase::setData(const QModelIndex& index, const QVariant& value, int role)
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

QEXTMvvmViewItem* QEXTMvvmViewModelBase::rootItem() const
{
    return p_impl->root.get();
}

//! Returns a pointer to the RefViewItem associated with the given index.
//! If index is invalid, returns nullptr.

QEXTMvvmViewItem* QEXTMvvmViewModelBase::itemFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? static_cast<QEXTMvvmViewItem*>(index.internalPointer()) : nullptr;
}

//! Returns the QModelIndex associated with the given item.

QModelIndex QEXTMvvmViewModelBase::indexFromItem(const QEXTMvvmViewItem* item) const
{
    return item && item->parent()
               ? createIndex(item->row(), item->column(), const_cast<QEXTMvvmViewItem*>(item))
               : QModelIndex();
}

void QEXTMvvmViewModelBase::removeRow(QEXTMvvmViewItem* parent, int row)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error(
            "Error in ViewModelBase: attempt to use parent from another model");

    beginRemoveRows(indexFromItem(parent), row, row);
    parent->removeRow(row);
    endRemoveRows();
}

void QEXTMvvmViewModelBase::clearRows(QEXTMvvmViewItem* parent)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error(
            "Error in ViewModelBase: attempt to use parent from another model");

    if (!parent->rowCount())
        return;

    beginRemoveRows(indexFromItem(parent), 0, parent->rowCount() - 1);
    parent->clear();
    endRemoveRows();
}

//! Insert a row of items at index 'row' to given parent.

void QEXTMvvmViewModelBase::insertRow(QEXTMvvmViewItem* parent, int row,
                              std::vector<std::unique_ptr<QEXTMvvmViewItem>> items)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error(
            "Error in ViewModelBase: attempt to use parent from another model");

    beginInsertRows(indexFromItem(parent), row, row);
    parent->insertRow(row, std::move(items));
    endInsertRows();
}

//! Appends row of items to given parent.

void QEXTMvvmViewModelBase::appendRow(QEXTMvvmViewItem* parent, std::vector<std::unique_ptr<QEXTMvvmViewItem>> items)
{
    insertRow(parent, parent->rowCount(), std::move(items));
}

//! Returns the item flags for the given index.

Qt::ItemFlags QEXTMvvmViewModelBase::flags(const QModelIndex& index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    if (auto item = itemFromIndex(index); item)
        result |= item->flags();
    return result;
}

//! Sets new root item. Previous item will be deleted, model will be reset.

void QEXTMvvmViewModelBase::setRootViewItem(std::unique_ptr<QEXTMvvmViewItem> root_item)
{
    p_impl->root = std::move(root_item);
}
