// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projecthandler.h"
#include "recentprojectsettings.h"
#include "samplemodel.h"
#include "userinteractor.h"
#include <qextMvvmProjectManagerFactory.h>
#include <qextMvvmProjectTypes.h>
#include <qextMvvmWidgetUtils.h>
#include <QMainWindow>

using namespace ModelView;

ProjectHandler::ProjectHandler(SampleModel* sample_model, QMainWindow* main_window)
    : QObject(main_window)
    , m_recentProjectSettings(qextMakeUnique<RecentProjectSettings>())
    , m_userInteractor(qextMakeUnique<UserInteractor>(m_recentProjectSettings.get(), main_window))
    , m_model(sample_model)
{
    initProjectManager();
    updateRecentProjectNames();
}

ProjectHandler::~ProjectHandler() = default;

//! Update names (name of the current project, recent project name list, notifies the world).

void ProjectHandler::updateNames()
{
    updateCurrentProjectName();
    updateRecentProjectNames();
}

//! Returns 'true' if current project can be closed.
//! Internally will perform check for unsaved data, and proceed via save/discard/cancel dialog.

bool ProjectHandler::canCloseProject() const
{
    return m_projectManager->closeCurrentProject();
}

void ProjectHandler::onCreateNewProject()
{
    if (m_projectManager->createNewProject())
        updateNames();
}

void ProjectHandler::onOpenExistingProject(const QString& dirname)
{
    if (m_projectManager->openExistingProject(dirname.toStdString()))
        updateNames();
}

void ProjectHandler::onSaveCurrentProject()
{
    if (m_projectManager->saveCurrentProject())
        updateNames();
}

void ProjectHandler::onSaveProjectAs()
{
    if (m_projectManager->saveProjectAs())
        updateNames();
}

void ProjectHandler::initProjectManager()
{
    auto modified_callback = [this]() { updateCurrentProjectName(); };
    auto models_callback = [this]() -> std::vector<QExtMvvmSessionModel*> { return {m_model}; };
    QExtMvvmProjectContext project_context{modified_callback, models_callback};

    auto select_dir_callback = [this]() { return m_userInteractor->onSelectDirRequest(); };
    auto create_dir_callback = [this]() { return m_userInteractor->onCreateDirRequest(); };
    auto answer_callback = [this]() { return m_userInteractor->onSaveChangesRequest(); };
    QExtMvvmUserInteractionContext user_context{select_dir_callback, create_dir_callback, answer_callback};

    m_projectManager = qextMvvmCreateProjectManager(project_context, user_context);
}

//! Updates the name of the current project on main window, notifies the world.

void ProjectHandler::updateCurrentProjectName()
{
    const auto current_project_dir = QString::fromStdString(m_projectManager->currentProjectDir());
    const auto is_modified = m_projectManager->isModified();

    // set main window title
    auto title = ModelView::Utils::ProjectWindowTitle(current_project_dir, is_modified);
    auto main_window = ModelView::Utils::FindMainWindow();
    if (main_window) main_window->setWindowTitle(title);

    currentProjectModified(current_project_dir, is_modified);
}

//! Update recent project list in settings, notifies the world.

void ProjectHandler::updateRecentProjectNames()
{
    m_recentProjectSettings->addToRecentProjects(
        QString::fromStdString(m_projectManager->currentProjectDir()));
    recentProjectsListModified(m_recentProjectSettings->recentProjects());
}
