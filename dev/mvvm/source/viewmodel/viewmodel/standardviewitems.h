// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_STANDARDVIEWITEMS_H
#define MVVM_VIEWMODEL_STANDARDVIEWITEMS_H

#include "viewmodel/viewmodel/viewitem.h"

namespace ModelView {

class QExtMvvmSessionItem;

//! Represents root item.

class QEXT_MVVM_API QExtMvvmRootViewItem : public QExtMvvmViewItem {
public:
    explicit QExtMvvmRootViewItem(QExtMvvmSessionItem* item);
};

//! Represents empty cell of tree or table.

class QEXT_MVVM_API QExtMvvmViewEmptyItem : public QExtMvvmViewItem {
public:
    QExtMvvmViewEmptyItem();
    QVariant data(int role) const override;
};

//! Represents display name of QExtMvvmSessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QExtMvvmViewLabelItem : public QExtMvvmViewItem {
public:
    explicit QExtMvvmViewLabelItem(QExtMvvmSessionItem* item);

    QVariant data(int role) const override;
};

//! Represents data role of QExtMvvmSessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QExtMvvmViewDataItem : public QExtMvvmViewItem {
public:
    explicit QExtMvvmViewDataItem(QExtMvvmSessionItem* item);

    Qt::ItemFlags flags() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDVIEWITEMS_H
