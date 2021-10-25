#ifndef _QEXTMVVMDEFAULTVIEWMODEL_H
#define _QEXTMVVMDEFAULTVIEWMODEL_H

#include <qextMvvmViewModel.h>

#include <cfMvvmModel.h>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmDefaultViewModel : public QEXTMvvmViewModel
{
public:
    QEXTMvvmDefaultViewModel(CFMvvmModel *model, QObject *parent = QEXT_DECL_NULLPTR);
};

#endif // _QEXTMVVMDEFAULTVIEWMODEL_H
