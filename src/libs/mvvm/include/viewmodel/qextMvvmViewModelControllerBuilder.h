#ifndef _QEXTMVVMVIEWMODELCONTROLLERBUILDER_H
#define _QEXTMVVMVIEWMODELCONTROLLERBUILDER_H

#include <qextMvvmViewModelController.h>
#include <qextMvvmGlobal.h>

#include <QSharedPointer>

class QEXTMvvmModel;
class QEXTMvvmViewModelBase;
class QEXTMvvmChildrenStrategyInterface;
class QEXTMvvmRowStrategyInterface;

//! Builder class for QEXTMvvmViewModelController.

class QEXT_MVVM_API QEXTMvvmViewModelControllerBuilder
{
public:
    typedef QEXTMvvmViewModelControllerBuilder Self;

    QEXTMvvmViewModelControllerBuilder();
    virtual ~QEXTMvvmViewModelControllerBuilder();

    Self &model(QEXTMvvmModel *model);
    Self &viewModel(QEXTMvvmViewModelBase *viewModel);
    Self &childrenStrategy(QEXTMvvmChildrenStrategyInterface *childrenStrategy);
    Self &rowStrategy(QEXTMvvmRowStrategyInterface *rowStrategy);

    operator QEXTMvvmViewModelController*();

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmViewModelControllerBuilder)
    //! Components necessary to build QEXTMvvmViewModelController
    struct Context
    {
        QEXTMvvmModel *model{nullptr};
        QEXTMvvmViewModelBase *viewModel{nullptr};
        QScopedPointer<QEXTMvvmChildrenStrategyInterface> childrenStrategy;
        QScopedPointer<QEXTMvvmRowStrategyInterface> rowStrategy;
    };

    Context context;
};


#endif // _QEXTMVVMVIEWMODELCONTROLLERBUILDER_H
