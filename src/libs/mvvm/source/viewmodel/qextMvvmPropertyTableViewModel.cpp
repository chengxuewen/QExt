#include <qextMvvmPropertyTableViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

QEXTMvvmPropertyTableViewModel::QEXTMvvmPropertyTableViewModel(QEXTMvvmModel *model, QObject *parent)
    : QEXTMvvmViewModel(new QEXTMvvmPropertyTableViewModelController(model, this), parent)
{
}
