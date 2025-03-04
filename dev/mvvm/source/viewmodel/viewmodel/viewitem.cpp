// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/viewitem.h"
#include "model/model/customvariants.h"
#include "model/model/sessionitem.h"
#include "model/utils/containerutils.h"
#include "viewmodel/viewmodel/viewmodelutils.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace ModelView;

struct QExtMvvmViewItem::ViewItemImpl {
    std::vector<QExtUniquePointer<QExtMvvmViewItem>> children; //! buffer to hold rows x columns
    int rows{0};
    int columns{0};
    QExtMvvmSessionItem* item{nullptr};
    int role{0};
    QExtMvvmViewItem* parent_view_item{nullptr};
    ViewItemImpl(QExtMvvmSessionItem* item, int role) : item(item), role(role) {}

    void appendRow(std::vector<QExtUniquePointer<QExtMvvmViewItem>> items)
    {
        insertRow(rows, std::move(items));
    }

    void insertRow(int row, std::vector<QExtUniquePointer<QExtMvvmViewItem>> items)
    {
        if (items.empty())
            throw std::runtime_error("Error in ViewItemImpl: attempt to insert empty row");

        if (columns > 0 && items.size() != static_cast<size_t>(columns))
            throw std::runtime_error("Error in ViewItemImpl: wrong number of columns.");

        if (row < 0 || row > rows)
            throw std::runtime_error("Error in ViewItemImpl: invalid row index.");

        children.insert(std::next(children.begin(), row * columns),
                        std::make_move_iterator(items.begin()),
                        std::make_move_iterator(items.end()));

        columns = static_cast<int>(items.size());
        ++rows;
    }

    void removeRow(int row)
    {
        if (row < 0 || row >= rows)
            throw std::runtime_error("Error in RefViewItem: invalid row index.");

        auto begin = std::next(children.begin(), row * columns);
        auto end = std::next(begin, columns);
        children.erase(begin, end);
        --rows;
        if (rows == 0)
            columns = 0;
    }

    QExtMvvmViewItem* child(int row, int column) const
    {
        if (row < 0 || row >= rows)
            throw std::runtime_error("Error in RefViewItem: wrong row)");

        if (column < 0 || column >= columns)
            throw std::runtime_error("Error in RefViewItem: wrong column)");

        return children.at(static_cast<size_t>(column + row * columns)).get();
    }

    QExtMvvmViewItem* parent() { return parent_view_item; }

    int index_of_child(const QExtMvvmViewItem* child)
    {
        return Utils::IndexOfItem(children.begin(), children.end(), child);
    }

    //! Returns item data associated with this RefViewItem.

    QVariant data() const { return item ? item->data<QVariant>(role) : QVariant(); }

    //! Returns vector of children.

    std::vector<QExtMvvmViewItem*> get_children() const
    {
        std::vector<QExtMvvmViewItem*> result;
        std::transform(children.begin(), children.end(), std::back_inserter(result),
                       [](const QExtUniquePointer<QExtMvvmViewItem>& x) { return x.get(); });
        return result;
    }
};

QExtMvvmViewItem::QExtMvvmViewItem(QExtMvvmSessionItem* item, int role) : p_impl(qextMakeUnique<ViewItemImpl>(item, role))
{
}

QExtMvvmViewItem::~QExtMvvmViewItem() = default;

//! Returns the number of child item rows that the item has.

int QExtMvvmViewItem::rowCount() const
{
    return p_impl->rows;
}

//! Returns the number of child item columns that the item has.

int QExtMvvmViewItem::columnCount() const
{
    return p_impl->columns;
}

//! Appends a row containing items. Number of items should be the same as columnCount()
//! (if there are already some rows). If it is a first row, then items can be of any size.

void QExtMvvmViewItem::appendRow(std::vector<QExtUniquePointer<QExtMvvmViewItem>> items)
{
    for (auto& x : items)
        x->setParent(this);
    p_impl->appendRow(std::move(items));
}

//! Insert a row of items at index 'row'.

void QExtMvvmViewItem::insertRow(int row, std::vector<QExtUniquePointer<QExtMvvmViewItem>> items)
{
    for (auto& x : items)
        x->setParent(this);
    p_impl->insertRow(row, std::move(items));
}

//! Removes row of items at given 'row'. Items will be deleted.

void QExtMvvmViewItem::removeRow(int row)
{
    p_impl->removeRow(row);
}

void QExtMvvmViewItem::clear()
{
    p_impl->children.clear();
    p_impl->rows = 0;
    p_impl->columns = 0;
}

QExtMvvmViewItem* QExtMvvmViewItem::parent() const
{
    return p_impl->parent();
}

QExtMvvmViewItem* QExtMvvmViewItem::child(int row, int column) const
{
    return p_impl->child(row, column);
}

QExtMvvmSessionItem* QExtMvvmViewItem::item() const
{
    return p_impl->item;
}

int QExtMvvmViewItem::item_role() const
{
    return p_impl->role;
}

//! Returns the row where the item is located in its parent's child table, or -1 if the item has no
//! parent.

int QExtMvvmViewItem::row() const
{
    auto index = parent() ? parent()->p_impl->index_of_child(this) : -1;
    return index >= 0 ? index / parent()->p_impl->columns : -1;
}

//! Returns the column where the item is located in its parent's child table, or -1 if the item has
//! no parent.

int QExtMvvmViewItem::column() const
{
    auto index = parent() ? parent()->p_impl->index_of_child(this) : -1;
    return index >= 0 ? index % parent()->p_impl->columns : -1;
}

//! Returns the data for given role according to Qt::ItemDataRole namespace definitions.
//! Converts data and roles from underlying QExtMvvmSessionItem to what Qt expects.

QVariant QExtMvvmViewItem::data(int qt_role) const
{
    if (!p_impl->item)
        return QVariant();

    if (qt_role == Qt::DisplayRole || qt_role == Qt::EditRole)
        return Utils::toQtVariant(p_impl->data());
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    else if (qt_role == Qt::ForegroundRole)
#else
    else if (qt_role == Qt::TextColorRole)
#endif
        return Utils::TextColorRole(*p_impl->item);
    else if (qt_role == Qt::ToolTipRole)
        return Utils::ToolTipRole(*p_impl->item);
    else
        return QVariant();
}

//! Sets the data to underlying QExtMvvmSessionItem.
//! Converts data and roles from Qt definitions to what QExtMvvmSessionItem expects.

bool QExtMvvmViewItem::setData(const QVariant& value, int qt_role)
{
    if (p_impl->item && qt_role == Qt::EditRole)
        return p_impl->item->setData(Utils::toCustomVariant(value), p_impl->role);
    return false;
}

//! Returns Qt's item flags.
//! Converts internal QExtMvvmSessionItem's status enable/disabled/readonly to what Qt expects.

Qt::ItemFlags QExtMvvmViewItem::flags() const
{
    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return result;
}

std::vector<QExtMvvmViewItem*> QExtMvvmViewItem::children() const
{
    return p_impl->get_children();
}

void QExtMvvmViewItem::setParent(QExtMvvmViewItem* parent)
{
    p_impl->parent_view_item = parent;
}
