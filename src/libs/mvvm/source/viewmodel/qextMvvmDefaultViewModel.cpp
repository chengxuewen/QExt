#include <qextMvvmDefaultViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

QEXTMvvmDefaultViewModel::QEXTMvvmDefaultViewModel(CFMvvmModel *model, QObject *parent)
    : QEXTMvvmViewModel(new QEXTMvvmDefaultViewModelController(model, this), parent)
{

}
