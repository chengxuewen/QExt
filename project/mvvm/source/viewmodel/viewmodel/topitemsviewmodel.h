// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H
#define MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H

#include "viewmodel/viewmodel/viewmodel.h"

namespace ModelView {

//! View model to show top level items of SessionModel in Qt trees and tables.
//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API TopItemsViewModel : public ViewModel {
    Q_OBJECT

public:
    TopItemsViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H
