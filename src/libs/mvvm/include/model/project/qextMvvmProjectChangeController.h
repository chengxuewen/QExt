#ifndef _QEXTMVVMPROJECTPROJECTCHANGECONTROLLER_H
#define _QEXTMVVMPROJECTPROJECTCHANGECONTROLLER_H

#include <qextMvvmGlobal.h>

#include <functional>
#include <memory>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionModel;
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
    using callback_t = std::function<void()>;
    QEXTMvvmProjectChangedController(const std::vector<QEXTMvvmSessionModel*>& models,
                             callback_t project_changed_callback = {});
    ~QEXTMvvmProjectChangedController();

    bool hasChanged() const;

    void resetChanged();

private:
    struct ProjectChangedControllerImpl;
    std::unique_ptr<ProjectChangedControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPROJECTPROJECTCHANGECONTROLLER_H
