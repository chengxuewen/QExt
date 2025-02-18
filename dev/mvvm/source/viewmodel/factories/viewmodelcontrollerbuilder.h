// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_VIEWMODELCONTROLLERBUILDER_H
#define MVVM_FACTORIES_VIEWMODELCONTROLLERBUILDER_H

#include "viewmodel/viewmodel/viewmodelcontroller.h"
#include "qextMVVMGlobal.h"
#include <memory>

namespace ModelView {

class SessionModel;
class ViewModelBase;
class ChildrenStrategyInterface;
class RowStrategyInterface;

//! Builder class for ViewModelController.

class QEXT_MVVM_API ViewModelControllerBuilder {
public:
    using self = ViewModelControllerBuilder;

    ViewModelControllerBuilder();
    ~ViewModelControllerBuilder();

    ViewModelControllerBuilder(const ViewModelControllerBuilder& other) = delete;
    ViewModelControllerBuilder& operator=(const ViewModelControllerBuilder& other) = delete;

    self& model(SessionModel* model);
    self& viewModel(ViewModelBase* view_model);
    self& childrenStrategy(QExtUniquePointer<ChildrenStrategyInterface> children_strategy);
    self& rowStrategy(QExtUniquePointer<RowStrategyInterface> row_strategy);

    operator QExtUniquePointer<ViewModelController>();

private:
    //! Components necessary to build ViewModelController
    struct Context {
        SessionModel* model{nullptr};
        ViewModelBase* view_model{nullptr};
        QExtUniquePointer<ChildrenStrategyInterface> children_strategy;
        QExtUniquePointer<RowStrategyInterface> row_strategy;
    };

    Context context;
};

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELCONTROLLERBUILDER_H
