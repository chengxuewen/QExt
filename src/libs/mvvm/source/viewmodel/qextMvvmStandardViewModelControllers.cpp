#include <qextMvvmStandardViewModelControllers.h>
#include <qextMvvmStandardChildrenStrategies.h>
#include <qextMvvmLabelDataRowStrategy.h>

QEXTMvvmDefaultViewModelController::QEXTMvvmDefaultViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel)
    : CFMvvmViewModelController(model, viewModel)
{
    this->setChildrenStrategy(new QEXTMvvmAllChildrenStrategy);
    this->setRowStrategy(new QEXTMvvmLabelDataRowStrategy);
}

QEXTMvvmTopItemsViewModelController::QEXTMvvmTopItemsViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel)
    : CFMvvmViewModelController(model, viewModel)
{

}

QEXTMvvmPropertyViewModelController::QEXTMvvmPropertyViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel)
    : CFMvvmViewModelController(model, viewModel)
{

}

void QEXTMvvmPropertyViewModelController::onDataChange(CFMvvmItem *item, int role)
{

}

QEXTMvvmPropertyTableViewModelController::QEXTMvvmPropertyTableViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel, const std::vector<std::string> &labels)
    : CFMvvmViewModelController(model, viewModel)
{

}

QEXTMvvmPropertyFlatViewModelController::QEXTMvvmPropertyFlatViewModelController(CFMvvmModel *model, CFMvvmViewModelBase *viewModel)
    : CFMvvmViewModelController(model, viewModel)
{

}

void QEXTMvvmPropertyFlatViewModelController::onDataChange(CFMvvmItem *item, int role)
{

}
