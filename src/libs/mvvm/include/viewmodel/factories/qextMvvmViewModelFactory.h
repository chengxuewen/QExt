#ifndef _QEXTMVVMVIEWMODELSTANDARDVIEWMODELS_H
#define _QEXTMVVMVIEWMODELSTANDARDVIEWMODELS_H

#include <qextMvvmViewModelControllerFactory.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmGlobal.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmViewModel;

namespace QEXTMvvmFactory
{

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, all items are shown.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmViewModel> CreateDefaultViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmViewModel> CreatePropertyViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Shows all properties of QEXTMvvmCompoundItem in columns of the table, rows of the table represent
//! different CompoundItems. Items of same type and table like structure of the model are expected.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmViewModel> CreatePropertyTableViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Shows only top items.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmViewModel> CreateTopItemsViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
//! Subproperties of group item moved one level up.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmViewModel> CreatePropertyFlatViewModel(QEXTMvvmSessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Use user provided types for ChildrenStrategy and RowStrategy.
template <typename ChildrenStrategy, typename RowStrategy>
std::unique_ptr<QEXTMvvmViewModel> CreateViewModel(QEXTMvvmSessionModel* session_model)
{
    auto controller = CreateController<ChildrenStrategy, RowStrategy>(session_model, nullptr);
    return make_unique<QEXTMvvmViewModel>(std::move(controller));
}

//! Creates view model to represent SessionModel for Qt views.
//! Use user provided controller type.
template <typename ViewModelController>
std::unique_ptr<QEXTMvvmViewModel> CreateViewModel(QEXTMvvmSessionModel* session_model)
{
    auto controller = make_unique<ViewModelController>(session_model);
    return make_unique<QEXTMvvmViewModel>(std::move(controller));
}

} // namespace Factory

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELSTANDARDVIEWMODELS_H
