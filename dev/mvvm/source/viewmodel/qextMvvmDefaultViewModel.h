// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
#define MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H

#include <qextMvvmViewModel.h>

namespace ModelView {

//! View model to show the content of QExtMvvmSessionModel in Qt widgets. Represents two-column tree with
//! label/data, with one-to-one child/parent correspondence as in the original QExtMvvmSessionModel. All
//! items (including hidden) are shown.

class QEXT_MVVM_API QExtMvvmDefaultViewModel : public QExtMvvmViewModel {
    Q_OBJECT

public:
    QExtMvvmDefaultViewModel(QExtMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
