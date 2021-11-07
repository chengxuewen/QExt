#include <qextMvvmViewModelFactory.h>
#include <qextMvvmDefaultViewModel.h>
#include <qextMvvmPropertyFlatViewModel.h>
#include <qextMvvmPropertyTableViewModel.h>
#include <qextMvvmPropertyViewModel.h>
#include <qextMvvmTopItemsViewModel.h>

QEXTMvvmViewModel *QEXTMvvmViewModelFactory::createDefaultViewModel(QEXTMvvmModel *model)
{
    return new QEXTMvvmDefaultViewModel(model);
}

QEXTMvvmViewModel *QEXTMvvmViewModelFactory::createPropertyViewModel(QEXTMvvmModel *model)
{
    return new QEXTMvvmPropertyViewModel(model);
}

QEXTMvvmViewModel *QEXTMvvmViewModelFactory::createPropertyTableViewModel(QEXTMvvmModel *model)
{
    return new QEXTMvvmPropertyTableViewModel(model);
}

QEXTMvvmViewModel *QEXTMvvmViewModelFactory::createTopItemsViewModel(QEXTMvvmModel *model)
{
    return new QEXTMvvmTopItemsViewModel(model);
}

QEXTMvvmViewModel *QEXTMvvmViewModelFactory::createPropertyFlatViewModel(QEXTMvvmModel *model)
{
    return new QEXTMvvmPropertyFlatViewModel(model);
}
