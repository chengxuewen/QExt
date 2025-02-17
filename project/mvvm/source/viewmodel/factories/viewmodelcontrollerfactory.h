// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_VIEWMODELCONTROLLERFACTORY_H
#define MVVM_FACTORIES_VIEWMODELCONTROLLERFACTORY_H

#include "viewmodel/factories/viewmodelcontrollerbuilder.h"
#include "qextMVVMGlobal.h"
#include <memory>

namespace ModelView {

class SessionModel;
class ViewModelBase;
class ViewModelController;

namespace Factory {

//! Create universal controller.

template <typename ChildrenStrategy, typename RowStrategy>
QExtUniquePointer<ViewModelController> CreateController(SessionModel* session_model,
                                                      ViewModelBase* view_model)
{
    return ViewModelControllerBuilder()
        .model(session_model)
        .viewModel(view_model)
        .childrenStrategy(qextMakeUnique<ChildrenStrategy>())
        .rowStrategy(qextMakeUnique<RowStrategy>());
}

} // namespace Factory

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELCONTROLLERFACTORY_H
