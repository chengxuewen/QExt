#include <qextMvvmGroupItem.h>
#include <qextMvvmLabelDataRowStrategy.h>
#include <qextMvvmPropertiesRowStrategy.h>
#include <qextMvvmStandardChildrenStrategies.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmStandardViewModelControllers.h>

QEXTMvvmDefaultViewModelController::QEXTMvvmDefaultViewModelController(QEXTMvvmModel *model,
                                                                       QEXTMvvmViewModelBase *viewModel)
    : QEXTMvvmViewModelController(model, viewModel)
{
    this->setChildrenStrategy(new QEXTMvvmAllChildrenStrategy);
    this->setRowStrategy(new QEXTMvvmLabelDataRowStrategy);
}

QEXTMvvmTopItemsViewModelController::QEXTMvvmTopItemsViewModelController(QEXTMvvmModel *model,
                                                                         QEXTMvvmViewModelBase *viewModel)
    : QEXTMvvmViewModelController(model, viewModel)
{
    this->setChildrenStrategy(new QEXTMvvmTopItemsStrategy);
    this->setRowStrategy(new QEXTMvvmLabelDataRowStrategy);
}

QEXTMvvmPropertyViewModelController::QEXTMvvmPropertyViewModelController(QEXTMvvmModel *model,
                                                                         QEXTMvvmViewModelBase *viewModel)
    : QEXTMvvmViewModelController(model, viewModel)
{
    this->setChildrenStrategy(new QEXTMvvmPropertyItemsStrategy);
    this->setRowStrategy(new QEXTMvvmLabelDataRowStrategy);
}

void QEXTMvvmPropertyViewModelController::onDataChange(QEXTMvvmItem *item, int role)
{
    QEXTMvvmViewModelController::onDataChange(item, role);
    // If data change occured with QEXTMvvmGroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    QEXTMvvmGroupItem *group = dynamic_cast<QEXTMvvmGroupItem *>(item);
    if (group)
    {
        this->updateBranch(group);
    }
}


// FIXME What to do with group property?
QEXTMvvmPropertyTableViewModelController::QEXTMvvmPropertyTableViewModelController(QEXTMvvmModel *model,
                                                                                   QEXTMvvmViewModelBase *viewModel,
                                                                                   const QVector<QString> &labels)
    : QEXTMvvmViewModelController(model, viewModel)
{
    this->setChildrenStrategy(new QEXTMvvmTopItemsStrategy);
    this->setRowStrategy(new QEXTMvvmPropertiesRowStrategy(labels));
}


QEXTMvvmPropertyFlatViewModelController::QEXTMvvmPropertyFlatViewModelController(QEXTMvvmModel *model,
                                                                                 QEXTMvvmViewModelBase *viewModel)
    : QEXTMvvmViewModelController(model, viewModel)
{
    this->setChildrenStrategy(new QEXTMvvmPropertyItemsFlatStrategy);
    this->setRowStrategy(new QEXTMvvmLabelDataRowStrategy);
}

void QEXTMvvmPropertyFlatViewModelController::onDataChange(QEXTMvvmItem *item, int role)
{
    QEXTMvvmViewModelController::onDataChange(item, role);
    // If data change occured with QEXTMvvmGroupItem, performs cleanup and regeneration of
    // ViewItems, corresponding to groupItem's current index.
    QEXTMvvmGroupItem *group = dynamic_cast<QEXTMvvmGroupItem *>(item);
    if (group)
    {
        this->updateBranch(group->parent());
    }
}
