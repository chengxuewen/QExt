// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H
#define MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H

#include <rowstrategyinterface.h>

class QStandardItem;

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Constructs row of QStandardItem's for given QEXTMvvmSessionItem.
//! Row consists of two columns, ViewLabelItem for QEXTMvvmSessionItem's display role and
//! ViewDataItem for Session's item data role.

class QEXT_MVVM_API LabelDataRowStrategy : public RowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<ViewItem>> constructRow(QEXTMvvmSessionItem*) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H
