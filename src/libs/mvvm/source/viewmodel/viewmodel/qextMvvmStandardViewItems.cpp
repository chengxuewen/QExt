// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionItem.h>
#include <viewmodel/qextMvvmStandardViewItems.h>
#include <viewmodel/qextMvvmViewModelUtils.h>

using namespace ModelView;

QEXTMvvmRootViewItem::QEXTMvvmRootViewItem(QEXTMvvmSessionItem* item) : QEXTMvvmViewItem(item, ItemDataRole::DATA) {}

//! ---------------------------------------------------------------------------

QEXTMvvmViewLabelItem::QEXTMvvmViewLabelItem(QEXTMvvmSessionItem* item) : QEXTMvvmViewItem(item, ItemDataRole::DISPLAY) {}

QVariant QEXTMvvmViewLabelItem::data(int role) const
{
    if (!item())
        return QVariant();

    // use item's display role
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QString::fromStdString(item()->displayName());

    return QEXTMvvmViewItem::data(role);
}

//! ---------------------------------------------------------------------------

QEXTMvvmViewDataItem::QEXTMvvmViewDataItem(QEXTMvvmSessionItem* item) : QEXTMvvmViewItem(item, ItemDataRole::DATA) {}

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
        return QEXTMvvmUtils::DecorationRole(*item());
    else if (role == Qt::CheckStateRole)
        return QEXTMvvmUtils::CheckStateRole(*item());

    return QEXTMvvmViewItem::data(role);
}

QEXTMvvmViewEmptyItem::QEXTMvvmViewEmptyItem() : QEXTMvvmViewItem(nullptr, 0) {}

QVariant QEXTMvvmViewEmptyItem::data(int) const
{
    return QVariant();
}
