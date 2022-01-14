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
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <viewmodel/qextMvvmViewModelUtils.h>
#include <qextMvvmWidgetUtils.h>

namespace
{
const QString AppMimeType = "application/org.bornagainproject.moveitem";
} // namespace

using namespace ModelView;

namespace DragAndView
{

DragViewModel::DragViewModel(QEXTMvvmSessionModel* model, QObject* parent)
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
    auto items = QEXTMvvmUtils::ParentItemsFromIndex(index_list);

    // Saving list of QEXTMvvmSessionItem's identifiers related to all DemoItem

    QStringList identifiers;
    for (auto item : QEXTMvvmUtils::ParentItemsFromIndex(index_list))
        identifiers.append(QString::fromStdString(item->identifier()));

    mimeData->setData(AppMimeType, QEXTMvvmUtils::serialize(identifiers));
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
    auto identifiers = QEXTMvvmUtils::deserialize(data->data(AppMimeType));
    for (auto id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());

        int row = clamp(requested_row, 0, item->parent()->itemCount(item->tag()) - 1);
        sessionModel()->moveItem(item, rootSessionItem(), {"", row});
    }

    return false;
}

} // namespace DragAndView
