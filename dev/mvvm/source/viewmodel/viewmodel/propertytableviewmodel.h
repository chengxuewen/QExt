// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H
#define MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H

#include "viewmodel/viewmodel/viewmodel.h"

namespace ModelView {

//! View model to show content of QExtMvvmSessionModel in Qt widgets: all item properties as a table row.
//! Intended to show registered properties of items in table-like view.
//! Registered properties will form columns of the table, top level items will form table rows.

class QEXT_MVVM_API QExtMvvmPropertyTableViewModel : public QExtMvvmViewModel {
    Q_OBJECT

public:
    QExtMvvmPropertyTableViewModel(QExtMvvmSessionModel* model, QObject* parent = nullptr);

    void insertRow(QExtMvvmViewItem* parent, int row, std::vector<QExtUniquePointer<QExtMvvmViewItem>> items) override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H
