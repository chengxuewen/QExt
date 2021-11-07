// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmModel.h>
#include <qextMvvmModelHasChangedController.h>
#include <qextMvvmProjectChangeController.h>

#include <QSharedPointer>

struct QEXTMvvmProjectChangedController::ProjectChangedControllerImpl {
    QVector<QEXTMvvmModel*> m_models;
    QVector<QSharedPointer<QEXTMvvmModelHasChangedController> > change_controllers;
    QEXTMvvmProjectChangedController::Callback m_project_changed_callback;
    bool m_project_has_changed{false};

    ProjectChangedControllerImpl(const QVector<QEXTMvvmModel*> &models, QEXTMvvmProjectChangedController::Callback callback)
        : m_models(models), m_project_changed_callback(callback)
    {
        create_controllers();
    }

    void create_controllers()
    {
        auto on_model_changed = [this]() { onProjectHasChanged(); };
        change_controllers.clear();
        for (auto model : m_models)
        {
//            QSharedPointer<QEXTMvvmModelHasChangedController> controller(new QEXTMvvmModelHasChangedController(model, on_model_changed));
//            change_controllers.append(controller);
        }
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
            if (m_project_changed_callback.isValid())
            {
                m_project_changed_callback();
            }
        }
    }
};

QEXTMvvmProjectChangedController::QEXTMvvmProjectChangedController(const QVector<QEXTMvvmModel *> &models,
                                                   Callback projectChangedCallback)
    : p_impl(new ProjectChangedControllerImpl(models, projectChangedCallback))
{
}

QEXTMvvmProjectChangedController::~QEXTMvvmProjectChangedController()
{

}

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
