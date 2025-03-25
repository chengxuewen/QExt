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

#include <qextMvvmViewModel.h>

namespace ModelView {

//! View model to show top level items of QExtMvvmSessionModel in Qt trees and tables.
//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class QEXT_MVVM_API QExtMvvmTopItemsViewModel : public QExtMvvmViewModel {
    Q_OBJECT

public:
    QExtMvvmTopItemsViewModel(QExtMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H
