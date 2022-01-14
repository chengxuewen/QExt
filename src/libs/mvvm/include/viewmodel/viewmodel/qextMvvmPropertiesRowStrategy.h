#ifndef _QEXTMVVMVIEWMODELPROPERTIESROWSTRATEGY_H
#define _QEXTMVVMVIEWMODELPROPERTIESROWSTRATEGY_H

#include <qextMvvmRowStrategyInterface.h>

class QStandardItem;

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Constructs row of QStandardItem's for given QEXTMvvmSessionItem.
//! Row consists of columns with all PropertyItem's of given QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmPropertiesRowStrategy : public QEXTMvvmRowStrategyInterface
{
public:
    QEXTMvvmPropertiesRowStrategy(std::vector<std::string> labels = {});

    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<QEXTMvvmViewItem>> constructRow(QEXTMvvmSessionItem* item) override;

private:
    void update_column_labels(std::vector<ModelView::QEXTMvvmSessionItem*> items);
    std::vector<std::string> current_column_labels;
    std::vector<std::string> user_defined_column_labels;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELPROPERTIESROWSTRATEGY_H
