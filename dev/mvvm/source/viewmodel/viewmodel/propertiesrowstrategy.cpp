// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/propertiesrowstrategy.h"
#include "model/model/itemutils.h"
#include "model/model/sessionitem.h"
#include "viewmodel/viewmodel/standardviewitems.h"

using namespace ModelView;

QExtMvvmPropertiesRowStrategy::QExtMvvmPropertiesRowStrategy(std::vector<std::string> labels)
    : user_defined_column_labels(std::move(labels))
{
}

QStringList QExtMvvmPropertiesRowStrategy::horizontalHeaderLabels() const
{
    QStringList result;
    auto labels =
        user_defined_column_labels.empty() ? current_column_labels : user_defined_column_labels;
    std::transform(labels.begin(), labels.end(), std::back_inserter(result),
                   [](const std::string& str) { return QString::fromStdString(str); });
    return result;
}

std::vector<QExtUniquePointer<QExtMvvmViewItem>> QExtMvvmPropertiesRowStrategy::constructRow(QExtMvvmSessionItem* item)
{
    std::vector<QExtUniquePointer<QExtMvvmViewItem>> result;

    if (!item)
        return result;

    auto items_in_row = Utils::SinglePropertyItems(*item);
    if (user_defined_column_labels.empty())
        update_column_labels(items_in_row);

    for (auto child : items_in_row) {
        if (child->hasData())
            result.emplace_back(qextMakeUnique<QExtMvvmViewDataItem>(child));
        else
            result.emplace_back(qextMakeUnique<QExtMvvmViewLabelItem>(child));
    }

    return result;
}

//! Updates current column labels.

void QExtMvvmPropertiesRowStrategy::update_column_labels(std::vector<QExtMvvmSessionItem*> items)
{
    current_column_labels.clear();
    std::transform(items.begin(), items.end(), std::back_inserter(current_column_labels),
                   [](const QExtMvvmSessionItem* item) { return item->displayName(); });
}
