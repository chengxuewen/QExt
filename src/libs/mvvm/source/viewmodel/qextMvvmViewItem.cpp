#include <qextMvvmViewItem.h>
#include <qextMvvmViewItem_p.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmUtils.h>
#include <qextMvvmViewModelUtils.h>

#include <QVector>

#include <algorithm>
#include <stdexcept>


QEXTMvvmViewItemPrivate::QEXTMvvmViewItemPrivate(QEXTMvvmViewItem *q)
    : q_ptr(q)
    , m_columns(0)
    , m_rows(0)
    , m_role(0)
    , m_item(QEXT_DECL_NULLPTR)
    , m_parentViewItem(QEXT_DECL_NULLPTR)
{

}

QEXTMvvmViewItemPrivate::~QEXTMvvmViewItemPrivate()
{
    qDeleteAll(m_children);
}

void QEXTMvvmViewItemPrivate::appendRow(QVector<QEXTMvvmViewItem *> items)
{
    this->insertRow(m_rows, items);
}

void QEXTMvvmViewItemPrivate::insertRow(int row, QVector<QEXTMvvmViewItem *> items)
{
    if (items.isEmpty())
    {
        throw std::runtime_error("Error in ViewItemImpl: attempt to insert empty row");
    }

    if (m_columns > 0 && items.size() != m_columns)
    {
        throw std::runtime_error("Error in ViewItemImpl: wrong number of columns.");
    }

    if (row < 0 || row > m_rows)
    {
        throw std::runtime_error("Error in ViewItemImpl: invalid row index.");
    }

    for (int i = 0; i < items.size(); ++i) {
        m_children.insert(row * m_columns + i, items.at(i));
    }

    m_columns = items.size();
    ++m_rows;
}

void QEXTMvvmViewItemPrivate::removeRow(int row)
{
    if (row < 0 || row >= m_rows)
    {
        throw std::runtime_error("Error in RefViewItem: invalid row index.");
    }

    for (int i = 0; i < m_columns; ++i) {
        delete m_children.at(row * m_columns);
        m_children.remove(row * m_columns);
    }
    --m_rows;
    if (m_rows == 0)
    {
        m_columns = 0;
    }
}

QEXTMvvmViewItem *QEXTMvvmViewItemPrivate::child(int row, int column) const
{
    if (row < 0 || row >= m_rows)
    {
        throw std::runtime_error("Error in RefViewItem: wrong row)");
    }

    if (column < 0 || column >= m_columns)
    {
        throw std::runtime_error("Error in RefViewItem: wrong column)");
    }

    return m_children.at(column + row * m_columns);
}

QEXTMvvmViewItem *QEXTMvvmViewItemPrivate::parent() const
{
    return m_parentViewItem;
}

int QEXTMvvmViewItemPrivate::indexOfChild(QEXTMvvmViewItem *child)
{
    return m_children.indexOf(child);
}

QVariant QEXTMvvmViewItemPrivate::data() const
{
    return m_item ? m_item->data<QVariant>(m_role) : QVariant();
}

QVector<QEXTMvvmViewItem *> QEXTMvvmViewItemPrivate::children() const
{
    return m_children;
}



QEXTMvvmViewItem::QEXTMvvmViewItem(QEXTMvvmItem *item, int role)
    : d_ptr(new QEXTMvvmViewItemPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmViewItem);
    d->m_item = item;
    d->m_role = role;
}

QEXTMvvmViewItem::~QEXTMvvmViewItem()
{

}

int QEXTMvvmViewItem::rowCount() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    return d->m_rows;
}

//! Returns the number of child item columns that the item has.

int QEXTMvvmViewItem::columnCount() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    return d->m_columns;
}

//! Appends a row containing items. Number of items should be the same as columnCount()
//! (if there are already some rows). If it is a first row, then items can be of any size.

void QEXTMvvmViewItem::appendRow(const QVector<QEXTMvvmViewItem *> &items)
{
    QEXT_DECL_D(QEXTMvvmViewItem);
    for (int i = 0; i < items.size(); ++i)
    {
        QEXTMvvmViewItem *item = items.at(i);
        item->setParent(this);
    }
    d->appendRow(items);
}

//! Insert a row of items at index 'row'.

void QEXTMvvmViewItem::insertRow(int row, const QVector<QEXTMvvmViewItem *> &items)
{
    QEXT_DECL_D(QEXTMvvmViewItem);
    for (int i = 0; i < items.size(); ++i)
    {
        QEXTMvvmViewItem *item = items.at(i);
        item->setParent(this);
    }
    d->insertRow(row, items);
}

//! Removes row of items at given 'row'. Items will be deleted.

void QEXTMvvmViewItem::removeRow(int row)
{
    QEXT_DECL_D(QEXTMvvmViewItem);
    d->removeRow(row);
}

void QEXTMvvmViewItem::clear()
{
    QEXT_DECL_D(QEXTMvvmViewItem);
    d->m_children.clear();
    d->m_rows = 0;
    d->m_columns = 0;
}

QEXTMvvmViewItem *QEXTMvvmViewItem::parent() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    return d->parent();
}

QEXTMvvmViewItem *QEXTMvvmViewItem::child(int row, int column) const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    return d->child(row, column);
}

QEXTMvvmItem *QEXTMvvmViewItem::item() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    return d->m_item;
}

int QEXTMvvmViewItem::itemRole() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    return d->m_role;
}

//! Returns the row where the item is located in its parent's child table, or -1 if the item has no
//! parent.

int QEXTMvvmViewItem::row() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    int index = this->parent() ? this->parent()->d_func()->indexOfChild(const_cast<QEXTMvvmViewItem *>(this)) : -1;
    return index >= 0 ? index / this->parent()->d_func()->m_columns : -1;
}

//! Returns the column where the item is located in its parent's child table, or -1 if the item has
//! no parent.

int QEXTMvvmViewItem::column() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    int index = this->parent() ? this->parent()->d_func()->indexOfChild(const_cast<QEXTMvvmViewItem *>(this)) : -1;
    return index >= 0 ? index % this->parent()->d_func()->m_columns : -1;
}

//! Returns the data for given role according to Qt::QEXTMvvmItem namespace definitions.
//! Converts data and roles from underlying QEXTMvvmItem to what Qt expects.

QVariant QEXTMvvmViewItem::data(int role) const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    if (!d->m_item)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return d->data();
    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    else if (role == Qt::ForegroundRole)
#else
    else if (role == Qt::TextColorRole)
#endif
    {
        return QEXTMvvmViewModelUtils::TextColorRole(*d->m_item);
    }
    else if (role == Qt::ToolTipRole)
    {
        return QEXTMvvmViewModelUtils::ToolTipRole(*d->m_item);
    }
    else
    {
        return QVariant();
    }
}

//! Sets the data to underlying QEXTMvvmItem.
//! Converts data and roles from Qt definitions to what QEXTMvvmItem expects.

bool QEXTMvvmViewItem::setData(const QVariant &value, int role)
{
    QEXT_DECL_D(QEXTMvvmViewItem);
    if (d->m_item && role == Qt::EditRole)
    {
        return d->m_item->setData(value, d->m_role);
    }
    return false;
}

//! Returns Qt's item flags.
//! Converts internal QEXTMvvmItem's status enable/disabled/readonly to what Qt expects.

Qt::ItemFlags QEXTMvvmViewItem::flags() const
{
    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return result;
}

QVector<QEXTMvvmViewItem *> QEXTMvvmViewItem::children() const
{
    QEXT_DECL_DC(QEXTMvvmViewItem);
    return d->children();
}

void QEXTMvvmViewItem::setParent(QEXTMvvmViewItem *parent)
{
    QEXT_DECL_D(QEXTMvvmViewItem);
    d->m_parentViewItem = parent;
}
