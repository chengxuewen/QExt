#ifndef _QEXTMVVMFACTORIESVIEWMODELCONTROLLERBUILDER_H
#define _QEXTMVVMFACTORIESVIEWMODELCONTROLLERBUILDER_H

#include <qextMvvmViewModelController.h>
#include <qextMvvmGlobal.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmViewModelBase;
class QEXTMvvmChildrenStrategyInterface;
class QEXTMvvmRowStrategyInterface;

//! Builder class for ViewModelController.

class QEXT_MVVM_API QEXTMvvmViewModelControllerBuilder
{
public:
    using self = QEXTMvvmViewModelControllerBuilder;

    QEXTMvvmViewModelControllerBuilder();
    ~QEXTMvvmViewModelControllerBuilder();

    QEXTMvvmViewModelControllerBuilder(const QEXTMvvmViewModelControllerBuilder& other) = delete;
    QEXTMvvmViewModelControllerBuilder& operator=(const QEXTMvvmViewModelControllerBuilder& other) = delete;

    self& model(QEXTMvvmSessionModel* model);
    self& viewModel(QEXTMvvmViewModelBase* view_model);
    self& childrenStrategy(std::unique_ptr<QEXTMvvmChildrenStrategyInterface> children_strategy);
    self& rowStrategy(std::unique_ptr<QEXTMvvmRowStrategyInterface> row_strategy);

    operator std::unique_ptr<QEXTMvvmViewModelController>();

private:
    //! Components necessary to build ViewModelController
    struct Context {
        QEXTMvvmSessionModel* model{nullptr};
        QEXTMvvmViewModelBase* view_model{nullptr};
        std::unique_ptr<QEXTMvvmChildrenStrategyInterface> children_strategy;
        std::unique_ptr<QEXTMvvmRowStrategyInterface> row_strategy;
    };

    Context context;
};

} // namespace ModelView

#endif // _QEXTMVVMFACTORIESVIEWMODELCONTROLLERBUILDER_H
