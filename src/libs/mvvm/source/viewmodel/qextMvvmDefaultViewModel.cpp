#include <qextMvvmDefaultViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

QEXTMvvmDefaultViewModel::QEXTMvvmDefaultViewModel(QEXTMvvmModel *model, QObject *parent)
    : QEXTMvvmViewModel(new QEXTMvvmDefaultViewModelController(model, this), parent)
{
}
