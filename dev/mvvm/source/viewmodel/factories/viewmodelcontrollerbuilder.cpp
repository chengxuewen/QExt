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

ViewModelControllerBuilder::ViewModelControllerBuilder() = default;

ViewModelControllerBuilder::~ViewModelControllerBuilder() = default;

ViewModelControllerBuilder::operator QExtUniquePointer<ViewModelController>()
{
    if (!context.model)
        throw std::runtime_error("Error in ViewModelController: undefined model");

    if (!context.children_strategy)
        throw std::runtime_error("Error in ViewModelController: no children strategy defined.");

    if (!context.row_strategy)
        throw std::runtime_error("Error in ViewModelController: no row strategy defined.");

    auto result = qextMakeUnique<ViewModelController>(context.model, context.view_model);
    result->setChildrenStrategy(std::move(context.children_strategy));
    result->setRowStrategy(std::move(context.row_strategy));

    return result;
}

ViewModelControllerBuilder::self& ViewModelControllerBuilder::model(SessionModel* model)
{
    context.model = model;
    return *this;
}

ViewModelControllerBuilder::self& ViewModelControllerBuilder::viewModel(ViewModelBase* view_model)
{
    context.view_model = view_model;
    return *this;
}

ViewModelControllerBuilder::self& ViewModelControllerBuilder::childrenStrategy(
    QExtUniquePointer<ChildrenStrategyInterface> children_strategy)
{
    context.children_strategy = std::move(children_strategy);
    return *this;
}

ViewModelControllerBuilder::self&
ViewModelControllerBuilder::rowStrategy(QExtUniquePointer<RowStrategyInterface> row_strategy)
{
    context.row_strategy = std::move(row_strategy);
    return *this;
}

} // namespace ModelView
