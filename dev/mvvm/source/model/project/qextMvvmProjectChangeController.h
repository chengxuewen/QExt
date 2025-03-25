// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECTCHANGECONTROLLER_H
#define MVVM_PROJECT_PROJECTCHANGECONTROLLER_H

#include <qextMvvmGlobal.h>
#include <functional>
#include <memory>
#include <vector>

namespace ModelView {

class QExtMvvmSessionModel;

//! Tracks changes in all models.
//! Allows to check if one or more models have been changed since last call of ::resetChanged().
//! This is intended to work together with the QExtMvvmProject class. It will take care of calling
//! resetChanged after own saving.

//! To avoid extra signaling while being in already "changed" mode, the controller reports only
//! once.

class QEXT_MVVM_API QExtMvvmProjectChangedController {
public:
    using callback_t = std::function<void()>;
    QExtMvvmProjectChangedController(const std::vector<QExtMvvmSessionModel*>& models,
                             callback_t project_changed_callback = {});
    ~QExtMvvmProjectChangedController();

    bool hasChanged() const;

    void resetChanged();

private:
    struct ProjectChangedControllerImpl;
    QExtUniquePointer<ProjectChangedControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTCHANGECONTROLLER_H
