#ifndef _QEXTMVVMFACTORIESVIEWMODELCONTROLLERFACTORY_H
#define _QEXTMVVMFACTORIESVIEWMODELCONTROLLERFACTORY_H

#include <qextMvvmViewModelControllerBuilder.h>
#include <qextMvvmGlobal.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionModel;
class QEXTMvvmViewModelBase;
class QEXTMvvmViewModelController;

namespace QEXTMvvmFactory
{

//! Create universal controller.

template <typename ChildrenStrategy, typename RowStrategy>
std::unique_ptr<QEXTMvvmViewModelController> CreateController(QEXTMvvmSessionModel* session_model,
                                                      QEXTMvvmViewModelBase* view_model)
{
    return QEXTMvvmViewModelControllerBuilder()
        .model(session_model)
        .viewModel(view_model)
        .childrenStrategy(make_unique<ChildrenStrategy>())
        .rowStrategy(make_unique<RowStrategy>());
}

} // namespace Factory

} // namespace ModelView

#endif // _QEXTMVVMFACTORIESVIEWMODELCONTROLLERFACTORY_H
