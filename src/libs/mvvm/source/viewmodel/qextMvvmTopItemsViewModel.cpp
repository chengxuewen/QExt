#include <qextMvvmStandardViewModelControllers.h>
#include <qextMvvmTopItemsViewModel.h>

QEXTMvvmTopItemsViewModel::QEXTMvvmTopItemsViewModel(QEXTMvvmModel *model, QObject *parent)
    : QEXTMvvmViewModel(new QEXTMvvmTopItemsViewModelController(model, this), parent)
{
}
