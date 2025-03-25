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

#include <qextMvvmViewModelController.h>
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmViewModelBase;
class QExtMvvmChildrenStrategyInterface;
class QExtMvvmRowStrategyInterface;

//! Builder class for QExtMvvmViewModelController.

class QEXT_MVVM_API QExtMvvmViewModelControllerBuilder {
public:
    using self = QExtMvvmViewModelControllerBuilder;

    QExtMvvmViewModelControllerBuilder();
    ~QExtMvvmViewModelControllerBuilder();

    QExtMvvmViewModelControllerBuilder(const QExtMvvmViewModelControllerBuilder& other) = delete;
    QExtMvvmViewModelControllerBuilder& operator=(const QExtMvvmViewModelControllerBuilder& other) = delete;

    self& model(QExtMvvmSessionModel* model);
    self& viewModel(QExtMvvmViewModelBase* view_model);
    self& childrenStrategy(QExtUniquePointer<QExtMvvmChildrenStrategyInterface> children_strategy);
    self& rowStrategy(QExtUniquePointer<QExtMvvmRowStrategyInterface> row_strategy);

    operator QExtUniquePointer<QExtMvvmViewModelController>();

private:
    //! Components necessary to build QExtMvvmViewModelController
    struct Context {
        QExtMvvmSessionModel* model{nullptr};
        QExtMvvmViewModelBase* view_model{nullptr};
        QExtUniquePointer<QExtMvvmChildrenStrategyInterface> children_strategy;
        QExtUniquePointer<QExtMvvmRowStrategyInterface> row_strategy;
    };

    Context context;
};

} // namespace ModelView

#endif // MVVM_FACTORIES_VIEWMODELCONTROLLERBUILDER_H
