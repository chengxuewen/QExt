// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dragviewmodel.h"
#include <QByteArray>
#include <QDataStream>
#include <QMimeData>
#include <algorithm>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmViewModelUtils.h>
#include <qextMvvmWidgetUtils.h>

namespace
{
const QString AppMimeType = "application/org.bornagainproject.moveitem";
} // namespace



namespace DragAndView
{

DragViewModel::DragViewModel(QEXTMvvmModel* model, QObject* parent)
    : QEXTMvvmPropertyTableViewModel(model, parent)
{
}

Qt::ItemFlags DragViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = QEXTMvvmPropertyTableViewModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QMimeData* DragViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto mimeData = new QMimeData;
    auto items = QEXTMvvmViewModelUtils::ParentItemsFromIndex(index_list);

    // Saving list of QEXTMvvmItem's identifiers related to all DemoItem

    QStringList identifiers;
    for (auto item : QEXTMvvmViewModelUtils::ParentItemsFromIndex(index_list))
        identifiers.append(item->identifier());

    mimeData->setData(AppMimeType, QEXTMvvmWidgetUtils::serialize(identifiers));
    return mimeData;
}

Qt::DropActions DragViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

Qt::DropActions DragViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

bool DragViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction, int, int,
                                    const QModelIndex&) const
{
    if (!data->hasFormat(AppMimeType))
        return false;

    return true;
}

bool DragViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    int requested_row = parent.isValid() ? parent.row() : row;

    // retrieving list of item identifiers and accessing items
    auto identifiers = QEXTMvvmWidgetUtils::deserialize(data->data(AppMimeType));
    for (auto id : identifiers) {
        auto item = model()->findItem(id);

        int max = item->parent()->itemCount(item->tag()) - 1;
        int row = qMin(requested_row, item->parent()->itemCount(item->tag()) - 1);
        row = qMax(0, row);
        model()->moveItem(item, rootItem(), {"", row});
    }

    return false;
}

} // namespace DragAndView
