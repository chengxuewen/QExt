#ifndef _QEXTMVVMPROJECTCHANGECONTROLLER_H
#define _QEXTMVVMPROJECTCHANGECONTROLLER_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

#include <QVector>
#include <QScopedPointer>

class QEXTMvvmModel;
class QEXTMvvmModelHasChangedController;

//! Tracks changes in all models.
//! Allows to check if one or more models have been changed since last call of ::resetChanged().
//! This is intended to work together with the Project class. It will take care of calling
//! resetChanged after own saving.

//! To avoid extra signaling while being in already "changed" mode, the controller reports only
//! once.

class QEXT_MVVM_API QEXTMvvmProjectChangedController
{
public:
    typedef QEXTFunction<void> Callback;

    QEXTMvvmProjectChangedController(const QVector<QEXTMvvmModel*> &models,
                                     Callback projectChangedCallback = Callback());
    virtual ~QEXTMvvmProjectChangedController();

    bool hasChanged() const;
    void resetChanged();

private:
    struct ProjectChangedControllerImpl;
    QScopedPointer<ProjectChangedControllerImpl> p_impl;
};


#endif // _QEXTMVVMPROJECTCHANGECONTROLLER_H
