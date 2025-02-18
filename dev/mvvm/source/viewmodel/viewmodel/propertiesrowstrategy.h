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

#include "viewmodel/interfaces/rowstrategyinterface.h"

namespace ModelView {

class SessionItem;

//! Constructs row of ViewItem's for given SessionItem.
//! Row consists of columns with all PropertyItem's of given SessionItem.

class QEXT_MVVM_API PropertiesRowStrategy : public RowStrategyInterface {
public:
    PropertiesRowStrategy(std::vector<std::string> labels = {});

    QStringList horizontalHeaderLabels() const override;

    std::vector<QExtUniquePointer<ViewItem>> constructRow(SessionItem* item) override;

private:
    void update_column_labels(std::vector<ModelView::SessionItem*> items);
    std::vector<std::string> current_column_labels;
    std::vector<std::string> user_defined_column_labels;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
