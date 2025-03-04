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
//! For LayerItem two items will be generated: QExtMvvmViewLabelItem and QExtMvvmViewEmptyItem, both uneditable.
//! For LayerItem's thickness property, two items will be generated: QExtMvvmViewLabelItem and QExtMvvmViewDataItem.

QStringList QExtMvvmLabelDataRowStrategy::horizontalHeaderLabels() const
{
    return QStringList() << "Name"
                         << "Value";
}

std::vector<QExtUniquePointer<QExtMvvmViewItem>> QExtMvvmLabelDataRowStrategy::constructRow(QExtMvvmSessionItem* item)
{
    std::vector<QExtUniquePointer<QExtMvvmViewItem>> result;

    if (!item)
        return result;

    result.emplace_back(qextMakeUnique<QExtMvvmViewLabelItem>(item));
    result.emplace_back(qextMakeUnique<QExtMvvmViewDataItem>(item));
    return result;
}
