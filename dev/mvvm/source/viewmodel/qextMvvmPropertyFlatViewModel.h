// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_PROPERTYFLATVIEWMODEL_H
#define MVVM_VIEWMODEL_PROPERTYFLATVIEWMODEL_H

#include <qextMvvmViewModel.h>

namespace ModelView {

//! View model to show content of QExtMvvmSessionModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class QEXT_MVVM_API QExtMvvmPropertyFlatViewModel : public QExtMvvmViewModel {
    Q_OBJECT
public:
    QExtMvvmPropertyFlatViewModel(QExtMvvmSessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTYFLATVIEWMODEL_H
