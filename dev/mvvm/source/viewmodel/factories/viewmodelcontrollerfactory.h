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
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmViewModelBase;
class QExtMvvmViewModelController;

namespace Factory {

//! Create universal controller.

template <typename ChildrenStrategy, typename RowStrategy>
QExtUniquePointer<QExtMvvmViewModelController> CreateController(QExtMvvmSessionModel* session_model,
                                                      QExtMvvmViewModelBase* view_model)
{
    return QExtMvvmViewModelControllerBuilder()
        .model(session_model)
        .viewModel(view_model)
        .childrenStrategy(qextMakeUnique<ChildrenStrategy>())
        .rowStrategy(qextMakeUnique<RowStrategy>());
}

} // namespace Factory

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELCONTROLLERFACTORY_H
