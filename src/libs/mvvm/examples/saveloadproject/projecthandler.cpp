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
#include "recentprojectwidget.h"
#include "samplemodel.h"
#include "userinteractor.h"

#include <QMainWindow>

#include <qextMvvmProjectManagerInterface.h>
#include <qextMvvmFactory.h>
#include <qextMvvmProjectTypes.h>
#include <qextMvvmWidgetUtils.h>



ProjectHandler::ProjectHandler(SampleModel *sampleModel, QMainWindow* main_window)
    : QObject(main_window)
    , m_recentProjectSettings(new RecentProjectSettings)
    , m_userInteractor(new UserInteractor(m_recentProjectSettings.get(), main_window))
    , m_model(sampleModel)
{
    initProjectManager();
    updateRecentProjectNames();
}

ProjectHandler::~ProjectHandler()
{

}

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

void ProjectHandler::onOpenExistingProject(const QString &dirname)
{
    if (m_projectManager->openExistingProject(dirname))
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
    auto models_callback = [this]() -> QVector<QEXTMvvmModel *> { return {m_model}; };
    QEXTMvvmProjectContext project_context{modified_callback, models_callback};

    auto select_dir_callback = [this]() { return m_userInteractor->onSelectDirRequest(); };
    auto create_dir_callback = [this]() { return m_userInteractor->onCreateDirRequest(); };
    auto answer_callback = [this]() { return m_userInteractor->onSaveChangesRequest(); };
    QEXTMvvmUserInteractionContext user_context{select_dir_callback, create_dir_callback, answer_callback};

    m_projectManager.reset(QEXTMvvmFactory::createProjectManager(project_context, user_context));
}

//! Updates the name of the current project on main window, notifies the world.

void ProjectHandler::updateCurrentProjectName()
{
    const auto current_project_dir = m_projectManager->currentProjectDir();
    const auto is_modified = m_projectManager->isModified();

    // set main window title
    auto title = QEXTMvvmWidgetUtils::ProjectWindowTitle(current_project_dir, is_modified);
    if (auto main_window = QEXTMvvmWidgetUtils::FindMainWindow(); main_window)
        main_window->setWindowTitle(title);

    currentProjectModified(current_project_dir, is_modified);
}

//! Update recent project list in settings, notifies the world.

void ProjectHandler::updateRecentProjectNames()
{
    m_recentProjectSettings->addToRecentProjects(m_projectManager->currentProjectDir());
    recentProjectsListModified(m_recentProjectSettings->recentProjects());
}
