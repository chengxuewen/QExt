// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_STANDARDVIEWMODELS_H
#define MVVM_VIEWMODEL_STANDARDVIEWMODELS_H

#include <memory>
#include <factories/viewmodelcontrollerfactory.h>
#include <viewmodel/viewmodel.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionModel;
class ViewModel;

namespace Factory
{

//! Creates view model to represent QEXTMvvmSessionModel for Qt views.
//! The model has two columns, all items are shown.
QEXT_MVVM_API std::unique_ptr<ViewModel> CreateDefaultViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent QEXTMvvmSessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
QEXT_MVVM_API std::unique_ptr<ViewModel> CreatePropertyViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent QEXTMvvmSessionModel for Qt views.
//! Shows all properties of QEXTMvvmCompoundItem in columns of the table, rows of the table represent
//! different CompoundItems. Items of same type and table like structure of the model are expected.
QEXT_MVVM_API std::unique_ptr<ViewModel> CreatePropertyTableViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent QEXTMvvmSessionModel for Qt views.
//! Shows only top items.
QEXT_MVVM_API std::unique_ptr<ViewModel> CreateTopItemsViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent QEXTMvvmSessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
//! Subproperties of group item moved one level up.
QEXT_MVVM_API std::unique_ptr<ViewModel> CreatePropertyFlatViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent QEXTMvvmSessionModel for Qt views.
//! Use user provided types for ChildrenStrategy and RowStrategy.
template <typename ChildrenStrategy, typename RowStrategy>
std::unique_ptr<ViewModel> CreateViewModel(QEXTMvvmSessionModel* session_model)
{
    auto controller = CreateController<ChildrenStrategy, RowStrategy>(session_model, nullptr);
    return std::make_unique<ViewModel>(std::move(controller));
}

//! Creates view model to represent QEXTMvvmSessionModel for Qt views.
//! Use user provided controller type.
template <typename ViewModelController>
std::unique_ptr<ViewModel> CreateViewModel(QEXTMvvmSessionModel* session_model)
{
    auto controller = std::make_unique<ViewModelController>(session_model);
    return std::make_unique<ViewModel>(std::move(controller));
}

} // namespace Factory

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDVIEWMODELS_H
