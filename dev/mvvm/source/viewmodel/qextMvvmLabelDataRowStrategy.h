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

#include <qextMvvmRowStrategyInterface.h>

namespace ModelView {

class QExtMvvmSessionItem;

//! Constructs row of QExtMvvmViewItem's for given QExtMvvmSessionItem.
//! Row consists of two columns, QExtMvvmViewLabelItem for QExtMvvmSessionItem's display role and
//! QExtMvvmViewDataItem for Session's item data role.

class QEXT_MVVM_API QExtMvvmLabelDataRowStrategy : public QExtMvvmRowStrategyInterface {
public:
    QStringList horizontalHeaderLabels() const override;

    std::vector<QExtUniquePointer<QExtMvvmViewItem>> constructRow(QExtMvvmSessionItem*) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H
