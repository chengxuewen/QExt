#include <qextMvvmPropertyViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

QEXTMvvmPropertyViewModel::QEXTMvvmPropertyViewModel(QEXTMvvmModel *model, QObject *parent)
    : QEXTMvvmViewModel(new QEXTMvvmPropertyViewModelController(model, this), parent)
{
}
