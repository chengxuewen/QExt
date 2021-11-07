#include <qextMvvmPropertyFlatViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

QEXTMvvmPropertyFlatViewModel::QEXTMvvmPropertyFlatViewModel(QEXTMvvmModel *model, QObject *parent)
    : QEXTMvvmViewModel(new QEXTMvvmPropertyFlatViewModelController(model, this), parent)
{
}
