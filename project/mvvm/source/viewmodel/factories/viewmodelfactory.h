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

#include "viewmodel/factories/viewmodelcontrollerfactory.h"
#include "viewmodel/viewmodel/viewmodel.h"
#include "qextMVVMGlobal.h"
#include <memory>

namespace ModelView {

class SessionModel;
class ViewModel;

namespace Factory {

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, all items are shown.
QEXT_MVVM_API QExtUniquePointer<ViewModel> CreateDefaultViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
QEXT_MVVM_API QExtUniquePointer<ViewModel> CreatePropertyViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Shows all properties of CompoundItem in columns of the table, rows of the table represent
//! different CompoundItems. Items of same type and table like structure of the model are expected.
QEXT_MVVM_API QExtUniquePointer<ViewModel> CreatePropertyTableViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Shows only top items.
QEXT_MVVM_API QExtUniquePointer<ViewModel> CreateTopItemsViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
//! Subproperties of group item moved one level up.
QEXT_MVVM_API QExtUniquePointer<ViewModel> CreatePropertyFlatViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Use user provided types for ChildrenStrategy and RowStrategy.
template <typename ChildrenStrategy, typename RowStrategy>
QExtUniquePointer<ViewModel> CreateViewModel(SessionModel* session_model)
{
    auto controller = CreateController<ChildrenStrategy, RowStrategy>(session_model, nullptr);
    return qextMakeUnique<ViewModel>(std::move(controller));
}

//! Creates view model to represent SessionModel for Qt views.
//! Use user provided controller type.
template <typename ViewModelController>
QExtUniquePointer<ViewModel> CreateViewModel(SessionModel* session_model)
{
    auto controller = qextMakeUnique<ViewModelController>(session_model);
    return qextMakeUnique<ViewModel>(std::move(controller));
}

} // namespace Factory

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELFACTORY_H
