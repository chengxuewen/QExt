// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmStandardViewItems.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmViewModelUtils.h>

using namespace ModelView;

QExtMvvmRootViewItem::QExtMvvmRootViewItem(QExtMvvmSessionItem* item) : QExtMvvmViewItem(item, ItemDataRole::DATA) {}

//! ---------------------------------------------------------------------------

QExtMvvmViewLabelItem::QExtMvvmViewLabelItem(QExtMvvmSessionItem* item) : QExtMvvmViewItem(item, ItemDataRole::DISPLAY) {}

QVariant QExtMvvmViewLabelItem::data(int role) const
{
    if (!item())
        return QVariant();

    // use item's display role
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QString::fromStdString(item()->displayName());

    return QExtMvvmViewItem::data(role);
}

//! ---------------------------------------------------------------------------

QExtMvvmViewDataItem::QExtMvvmViewDataItem(QExtMvvmSessionItem* item) : QExtMvvmViewItem(item, ItemDataRole::DATA) {}

Qt::ItemFlags QExtMvvmViewDataItem::flags() const
{
    Qt::ItemFlags result = QExtMvvmViewItem::flags();
    if (item() && item()->isEditable() && item()->isEnabled() && item()->data<QVariant>().isValid())
        result |= Qt::ItemIsEditable;

    return result;
}

QVariant QExtMvvmViewDataItem::data(int role) const
{
    if (role == Qt::DecorationRole)
        return Utils::DecorationRole(*item());
    else if (role == Qt::CheckStateRole)
        return Utils::CheckStateRole(*item());

    return QExtMvvmViewItem::data(role);
}

QExtMvvmViewEmptyItem::QExtMvvmViewEmptyItem() : QExtMvvmViewItem(nullptr, 0) {}

QVariant QExtMvvmViewEmptyItem::data(int) const
{
    return QVariant();
}
