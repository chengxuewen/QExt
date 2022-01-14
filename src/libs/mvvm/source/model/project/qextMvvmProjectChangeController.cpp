// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionModel.h>
#include <project/qextMvvmModelHasChangedController.h>
#include <project/qextMvvmProjectChangeController.h>

using namespace ModelView;

struct QEXTMvvmProjectChangedController::ProjectChangedControllerImpl {
    std::vector<QEXTMvvmSessionModel*> m_models;
    std::vector<std::unique_ptr<QEXTMvvmModelHasChangedController>> change_controllers;
    callback_t m_project_changed_callback;
    bool m_project_has_changed{false};

    ProjectChangedControllerImpl(const std::vector<QEXTMvvmSessionModel*>& models, callback_t callback)
        : m_models(models), m_project_changed_callback(callback)
    {
        create_controllers();
    }

    void create_controllers()
    {
        auto on_model_changed = [this]() { onProjectHasChanged(); };
        change_controllers.clear();
        for (auto model : m_models)
            change_controllers.emplace_back(
                make_unique<QEXTMvvmModelHasChangedController>(model, on_model_changed));
    }

    bool hasChanged() const { return m_project_has_changed; }

    void resetChanged()
    {
        for (auto& controller : change_controllers)
            controller->resetChanged();
        m_project_has_changed = false;
    }

    void onProjectHasChanged()
    {
        if (!m_project_has_changed) {
            m_project_has_changed = true;
            if (m_project_changed_callback)
                m_project_changed_callback();
        }
    }
};

QEXTMvvmProjectChangedController::QEXTMvvmProjectChangedController(const std::vector<QEXTMvvmSessionModel*>& models,
                                                   callback_t project_changed_callback)
    : p_impl(make_unique<ProjectChangedControllerImpl>(models, project_changed_callback))
{
}

QEXTMvvmProjectChangedController::~QEXTMvvmProjectChangedController() = default;

//! Returns true if the change in the models has been registered since the last call of
//! resetChanged.

bool QEXTMvvmProjectChangedController::hasChanged() const
{
    return p_impl->hasChanged();
}

//! Reset controller to initial state, pretending that no changes has been registered.

void QEXTMvvmProjectChangedController::resetChanged()
{
    return p_impl->resetChanged();
}
