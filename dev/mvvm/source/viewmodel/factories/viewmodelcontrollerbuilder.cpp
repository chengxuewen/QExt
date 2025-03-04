// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/factories/viewmodelcontrollerbuilder.h"
#include "viewmodel/interfaces/childrenstrategyinterface.h"
#include "viewmodel/interfaces/rowstrategyinterface.h"
#include "viewmodel/viewmodel/viewmodelcontroller.h"
#include <stdexcept>

namespace ModelView {

QExtMvvmViewModelControllerBuilder::QExtMvvmViewModelControllerBuilder() = default;

QExtMvvmViewModelControllerBuilder::~QExtMvvmViewModelControllerBuilder() = default;

QExtMvvmViewModelControllerBuilder::operator QExtUniquePointer<QExtMvvmViewModelController>()
{
    if (!context.model)
        throw std::runtime_error("Error in QExtMvvmViewModelController: undefined model");

    if (!context.children_strategy)
        throw std::runtime_error("Error in QExtMvvmViewModelController: no children strategy defined.");

    if (!context.row_strategy)
        throw std::runtime_error("Error in QExtMvvmViewModelController: no row strategy defined.");

    auto result = qextMakeUnique<QExtMvvmViewModelController>(context.model, context.view_model);
    result->setChildrenStrategy(std::move(context.children_strategy));
    result->setRowStrategy(std::move(context.row_strategy));

    return result;
}

QExtMvvmViewModelControllerBuilder::self& QExtMvvmViewModelControllerBuilder::model(QExtMvvmSessionModel* model)
{
    context.model = model;
    return *this;
}

QExtMvvmViewModelControllerBuilder::self& QExtMvvmViewModelControllerBuilder::viewModel(QExtMvvmViewModelBase* view_model)
{
    context.view_model = view_model;
    return *this;
}

QExtMvvmViewModelControllerBuilder::self& QExtMvvmViewModelControllerBuilder::childrenStrategy(
    QExtUniquePointer<QExtMvvmChildrenStrategyInterface> children_strategy)
{
    context.children_strategy = std::move(children_strategy);
    return *this;
}

QExtMvvmViewModelControllerBuilder::self&
QExtMvvmViewModelControllerBuilder::rowStrategy(QExtUniquePointer<QExtMvvmRowStrategyInterface> row_strategy)
{
    context.row_strategy = std::move(row_strategy);
    return *this;
}

} // namespace ModelView
