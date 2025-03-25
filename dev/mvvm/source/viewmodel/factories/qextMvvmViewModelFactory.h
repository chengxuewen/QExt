// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_VIEWMODELFACTORY_H
#define MVVM_FACTORIES_VIEWMODELFACTORY_H

#include <qextMvvmViewModelControllerFactory.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmViewModel;

namespace Factory {

//! Creates view model to represent QExtMvvmSessionModel for Qt views.
//! The model has two columns, all items are shown.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmViewModel> CreateDefaultViewModel(QExtMvvmSessionModel* model);

//! Creates view model to represent QExtMvvmSessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmViewModel> CreatePropertyViewModel(QExtMvvmSessionModel* model);

//! Creates view model to represent QExtMvvmSessionModel for Qt views.
//! Shows all properties of QExtMvvmCompoundItem in columns of the table, rows of the table represent
//! different CompoundItems. Items of same type and table like structure of the model are expected.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmViewModel> CreatePropertyTableViewModel(QExtMvvmSessionModel* model);

//! Creates view model to represent QExtMvvmSessionModel for Qt views.
//! Shows only top items.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmViewModel> CreateTopItemsViewModel(QExtMvvmSessionModel* model);

//! Creates view model to represent QExtMvvmSessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
//! Subproperties of group item moved one level up.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmViewModel> CreatePropertyFlatViewModel(QExtMvvmSessionModel* model);

//! Creates view model to represent QExtMvvmSessionModel for Qt views.
//! Use user provided types for ChildrenStrategy and RowStrategy.
template <typename ChildrenStrategy, typename RowStrategy>
QExtUniquePointer<QExtMvvmViewModel> CreateViewModel(QExtMvvmSessionModel* session_model)
{
    auto controller = CreateController<ChildrenStrategy, RowStrategy>(session_model, nullptr);
    return qextMakeUnique<QExtMvvmViewModel>(std::move(controller));
}

//! Creates view model to represent QExtMvvmSessionModel for Qt views.
//! Use user provided controller type.
template <typename QExtMvvmViewModelController>
QExtUniquePointer<QExtMvvmViewModel> CreateViewModel(QExtMvvmSessionModel* session_model)
{
    auto controller = qextMakeUnique<QExtMvvmViewModelController>(session_model);
    return qextMakeUnique<QExtMvvmViewModel>(std::move(controller));
}

} // namespace Factory

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELFACTORY_H
