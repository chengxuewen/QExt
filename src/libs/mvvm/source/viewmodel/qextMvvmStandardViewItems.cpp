#include <qextMvvmItem.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmViewModelUtils.h>



QEXTMvvmRootViewItem::QEXTMvvmRootViewItem(QEXTMvvmItem* item) : QEXTMvvmViewItem(item, QEXTMvvmItem::Role_Data) {}

//! ---------------------------------------------------------------------------

QEXTMvvmViewLabelItem::QEXTMvvmViewLabelItem(QEXTMvvmItem* item) : QEXTMvvmViewItem(item, QEXTMvvmItem::Role_Display) {}

QVariant QEXTMvvmViewLabelItem::data(int role) const
{
    if (!item())
        return QVariant();

    // use item's display role
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return item()->displayName();

    return QEXTMvvmViewItem::data(role);
}

//! ---------------------------------------------------------------------------

QEXTMvvmViewDataItem::QEXTMvvmViewDataItem(QEXTMvvmItem* item) : QEXTMvvmViewItem(item, QEXTMvvmItem::Role_Data) {}

Qt::ItemFlags QEXTMvvmViewDataItem::flags() const
{
    Qt::ItemFlags result = QEXTMvvmViewItem::flags();
    if (item() && item()->isEditable() && item()->isEnabled() && item()->data<QVariant>().isValid())
        result |= Qt::ItemIsEditable;

    return result;
}

QVariant QEXTMvvmViewDataItem::data(int role) const
{
    if (role == Qt::DecorationRole)
        return QEXTMvvmViewModelUtils::DecorationRole(*item());
    else if (role == Qt::CheckStateRole)
        return QEXTMvvmViewModelUtils::CheckStateRole(*item());

    return QEXTMvvmViewItem::data(role);
}

QEXTMvvmViewEmptyItem::QEXTMvvmViewEmptyItem() : QEXTMvvmViewItem(nullptr, 0) {}

QVariant QEXTMvvmViewEmptyItem::data(int) const
{
    return QVariant();
}
