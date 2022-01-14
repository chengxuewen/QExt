#ifndef _QEXTMVVMVIEWMODELLABELDATAROWSTRATEGY_H
#define _QEXTMVVMVIEWMODELLABELDATAROWSTRATEGY_H

#include <qextMvvmRowStrategyInterface.h>

class QStandardItem;

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Constructs row of QStandardItem's for given QEXTMvvmSessionItem.
//! Row consists of two columns, ViewLabelItem for QEXTMvvmSessionItem's display role and
//! ViewDataItem for Session's item data role.

class QEXT_MVVM_API QEXTMvvmLabelDataRowStrategy : public QEXTMvvmRowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<QEXTMvvmViewItem>> constructRow(QEXTMvvmSessionItem*) override;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELLABELDATAROWSTRATEGY_H
