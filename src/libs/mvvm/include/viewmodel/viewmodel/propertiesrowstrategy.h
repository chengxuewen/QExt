// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
#define MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H

#include <rowstrategyinterface.h>

class QStandardItem;

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Constructs row of QStandardItem's for given QEXTMvvmSessionItem.
//! Row consists of columns with all QEXTMvvmPropertyItem's of given QEXTMvvmSessionItem.

class QEXT_MVVM_API PropertiesRowStrategy : public RowStrategyInterface
{
public:
    PropertiesRowStrategy(std::vector<std::string> labels = {});

    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<ViewItem>> constructRow(QEXTMvvmSessionItem* item) override;

private:
    void update_column_labels(std::vector<ModelView::QEXTMvvmSessionItem*> items);
    std::vector<std::string> current_column_labels;
    std::vector<std::string> user_defined_column_labels;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
