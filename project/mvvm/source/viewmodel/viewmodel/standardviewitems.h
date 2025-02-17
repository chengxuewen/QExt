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

class SessionItem;

//! Represents root item.

class QEXT_MVVM_API RootViewItem : public ViewItem {
public:
    explicit RootViewItem(SessionItem* item);
};

//! Represents empty cell of tree or table.

class QEXT_MVVM_API ViewEmptyItem : public ViewItem {
public:
    ViewEmptyItem();
    QVariant data(int role) const override;
};

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API ViewLabelItem : public ViewItem {
public:
    explicit ViewLabelItem(SessionItem* item);

    QVariant data(int role) const override;
};

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API ViewDataItem : public ViewItem {
public:
    explicit ViewDataItem(SessionItem* item);

    Qt::ItemFlags flags() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDVIEWITEMS_H
