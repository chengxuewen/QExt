#ifndef _QEXTMVVMVIEWMODEL_P_H
#define _QEXTMVVMVIEWMODEL_P_H

#include <qextMvvmGlobal.h>

#include <cfMvvmViewModelBase_p.h>
#include <cfMvvmViewModelController.h>

#include <QScopedPointer>

CF_USE_NAMESPACE

class QEXTMvvmViewModel;
class QEXT_MVVM_API QEXTMvvmViewModelPrivate : public CFMvvmViewModelBasePrivate
{
public:
    explicit QEXTMvvmViewModelPrivate(QEXTMvvmViewModel *qq);
    ~QEXTMvvmViewModelPrivate();

    QScopedPointer<CFMvvmViewModelController> m_modelController;

private:
    CF_DECL_PUBLIC(QEXTMvvmViewModel)
    CF_DECL_DISABLE_COPY_MOVE(QEXTMvvmViewModelPrivate)
};


#endif // _QEXTMVVMVIEWMODEL_P_H
