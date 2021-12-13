// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemUtils.h>
#include <qextMvvmSessionItem.h>
#include <viewmodel/qextMvvmPropertiesRowStrategy.h>
#include <viewmodel/qextMvvmStandardViewItems.h>

using namespace ModelView;

PropertiesRowStrategy::PropertiesRowStrategy(std::vector<std::string> labels)
    : user_defined_column_labels(std::move(labels))
{
}

QStringList PropertiesRowStrategy::horizontalHeaderLabels() const
{
    QStringList result;
    auto labels =
        user_defined_column_labels.empty() ? current_column_labels : user_defined_column_labels;
    std::transform(labels.begin(), labels.end(), std::back_inserter(result),
                   [](const std::string& str) { return QString::fromStdString(str); });
    return result;
}

std::vector<std::unique_ptr<ViewItem>> PropertiesRowStrategy::constructRow(QEXTMvvmSessionItem* item)
{
    std::vector<std::unique_ptr<ViewItem>> result;

    if (!item)
        return result;

    auto items_in_row = Utils::SinglePropertyItems(*item);
    if (user_defined_column_labels.empty())
        update_column_labels(items_in_row);

    for (auto child : items_in_row) {
        if (child->hasData())
            result.emplace_back(std::make_unique<ViewDataItem>(child));
        else
            result.emplace_back(std::make_unique<ViewLabelItem>(child));
    }

    return result;
}

//! Updates current column labels.

void PropertiesRowStrategy::update_column_labels(std::vector<QEXTMvvmSessionItem*> items)
{
    current_column_labels.clear();
    std::transform(items.begin(), items.end(), std::back_inserter(current_column_labels),
                   [](const QEXTMvvmSessionItem* item) { return item->displayName(); });
}
