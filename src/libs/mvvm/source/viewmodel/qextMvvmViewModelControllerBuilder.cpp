#include <qextMvvmViewModelControllerBuilder.h>
#include <qextMvvmChildrenStrategyInterface.h>
#include <qextMvvmRowStrategyInterface.h>
#include <qextMvvmModel.h>
#include <qextMvvmViewModelController.h>
#include <stdexcept>


QEXTMvvmViewModelControllerBuilder::operator QEXTMvvmViewModelController*()
{
    if (!context.model)
        throw std::runtime_error("Error in QEXTMvvmViewModelController: undefined model");

    if (!context.childrenStrategy)
        throw std::runtime_error("Error in QEXTMvvmViewModelController: no children strategy defined.");

    if (!context.rowStrategy)
        throw std::runtime_error("Error in QEXTMvvmViewModelController: no row strategy defined.");

    auto result = new QEXTMvvmViewModelController(context.model, context.viewModel);
    result->setChildrenStrategy(context.childrenStrategy.take());
    result->setRowStrategy(context.rowStrategy.take());

    return result;
}

QEXTMvvmViewModelControllerBuilder::QEXTMvvmViewModelControllerBuilder()
{

}

QEXTMvvmViewModelControllerBuilder::~QEXTMvvmViewModelControllerBuilder()
{

}

QEXTMvvmViewModelControllerBuilder::Self& QEXTMvvmViewModelControllerBuilder::model(QEXTMvvmModel* model)
{
    context.model = model;
    return *this;
}

QEXTMvvmViewModelControllerBuilder::Self& QEXTMvvmViewModelControllerBuilder::viewModel(QEXTMvvmViewModelBase *viewModel)
{
    context.viewModel = viewModel;
    return *this;
}

QEXTMvvmViewModelControllerBuilder::Self &QEXTMvvmViewModelControllerBuilder::childrenStrategy(QEXTMvvmChildrenStrategyInterface *childrenStrategy)
{
    context.childrenStrategy.reset(childrenStrategy);
    return *this;
}

QEXTMvvmViewModelControllerBuilder::Self &QEXTMvvmViewModelControllerBuilder::rowStrategy(QEXTMvvmRowStrategyInterface *rowStrategy)
{
    context.rowStrategy.reset(rowStrategy);
    return *this;
}
