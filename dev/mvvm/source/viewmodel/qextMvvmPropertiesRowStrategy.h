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

#include <qextMvvmRowStrategyInterface.h>

namespace ModelView {

class QExtMvvmSessionItem;

//! Constructs row of QExtMvvmViewItem's for given QExtMvvmSessionItem.
//! Row consists of columns with all QExtMvvmPropertyItem's of given QExtMvvmSessionItem.

class QEXT_MVVM_API QExtMvvmPropertiesRowStrategy : public QExtMvvmRowStrategyInterface {
public:
    QExtMvvmPropertiesRowStrategy(std::vector<std::string> labels = {});

    QStringList horizontalHeaderLabels() const override;

    std::vector<QExtUniquePointer<QExtMvvmViewItem>> constructRow(QExtMvvmSessionItem* item) override;

private:
    void update_column_labels(std::vector<ModelView::QExtMvvmSessionItem*> items);
    std::vector<std::string> current_column_labels;
    std::vector<std::string> user_defined_column_labels;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
