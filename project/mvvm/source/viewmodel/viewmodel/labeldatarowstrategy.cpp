// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/labeldatarowstrategy.h"
#include "viewmodel/viewmodel/standardviewitems.h"

using namespace ModelView;

//! Example:
//! For LayerItem two items will be generated: ViewLabelItem and ViewEmptyItem, both uneditable.
//! For LayerItem's thickness property, two items will be generated: ViewLabelItem and ViewDataItem.

QStringList LabelDataRowStrategy::horizontalHeaderLabels() const
{
    return QStringList() << "Name"
                         << "Value";
}

std::vector<QExtUniquePointer<ViewItem>> LabelDataRowStrategy::constructRow(SessionItem* item)
{
    std::vector<QExtUniquePointer<ViewItem>> result;

    if (!item)
        return result;

    result.emplace_back(qextMakeUnique<ViewLabelItem>(item));
    result.emplace_back(qextMakeUnique<ViewDataItem>(item));
    return result;
}
