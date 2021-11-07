// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmProjectInterface.h>
#include <qextMvvmProjectTypes.h>
#include <qextMvvmProjectManager.h>
#include <qextMvvmProjectManagerDecorator.h>

#include <stdexcept>



namespace
{
const bool succeeded = true;
const bool failed = false;
} // namespace

struct QEXTMvvmProjectManagerDecorator::ProjectManagerImpl {
    QEXTMvvmProjectContext m_project_context;
    QEXTMvvmUserInteractionContext m_user_context;
    QScopedPointer<QEXTMvvmProjectManager> project_manager;

    ProjectManagerImpl(QEXTMvvmProjectContext project_context, QEXTMvvmUserInteractionContext user_context)
        : m_project_context(project_context), m_user_context(user_context)
    {
        project_manager.reset(new QEXTMvvmProjectManager(m_project_context));
    }

    //! Returns true if the project has directory already defined.
    bool projectHasDir() const { return !project_manager->currentProjectDir().isEmpty(); }

    //! Saves project in project directory. If directory is not defined, will acquire
    //! directory susing callback provided.
    bool saveCurrentProject()
    {
        // Feature FIXME?: already saved project (i.e. isModified=false) will be saved again.
        // Files will be same, but creation date will be changed.

        auto save_dir =
            projectHasDir() ? project_manager->currentProjectDir() : acquireNewProjectDir();
        return saveCurrentProjectAs(save_dir);
    }

    //! Saves current project under directory selected.
    bool saveCurrentProjectAs(const QString &dirname)
    {
        // empty dirname varible means 'cancel' during directory selection
        return dirname.isEmpty() ? failed : project_manager->saveProjectAs(dirname);
    }

    QString currentProjectDir() const { return project_manager->currentProjectDir(); }

    bool isModified() const { return project_manager->isModified(); }

    //! Performs saving of previous project before creating a new one.
    bool saveBeforeClosing()
    {
        if (isModified()) {
            switch (acquireSaveChangesAnswer()) {
            case SaveChangesAnswer::SAVE:
                return saveCurrentProject();
            case SaveChangesAnswer::CANCEL:
                return failed; // saving was interrupted by the 'cancel' button
            case SaveChangesAnswer::DISCARD:
                project_manager->closeCurrentProject();
                return succeeded;
            default:
                throw std::runtime_error("Error in QEXTMvvmProjectManager: unexpected answer.");
            }
        }
        return succeeded;
    }

    //! Asks the user whether to save/cancel/discard the project using callback provided.
    SaveChangesAnswer acquireSaveChangesAnswer() const
    {
        if (!m_user_context.m_answer_callback.isValid())
            throw std::runtime_error("Error in QEXTMvvmProjectManager: absent save_callback");
        return m_user_context.m_answer_callback();
    }

    //! Acquire the name of the new project directory using callback provided.
    QString acquireNewProjectDir()
    {
        if (!m_user_context.m_create_dir_callback.isValid())
            throw std::runtime_error("Error in QEXTMvvmProjectManager: absent creat_dir callback.");
        return m_user_context.m_create_dir_callback();
    }

    //! Acquire the name of the existing project directory using callback provided.
    QString acquireExistingProjectDir()
    {
        if (!m_user_context.m_select_dir_callback.isValid())
            throw std::runtime_error("Error in QEXTMvvmProjectManager: absent open_dir callback.");
        return m_user_context.m_select_dir_callback();
    }
};

//! Constructor for QEXTMvvmProjectManagerDecorator.

QEXTMvvmProjectManagerDecorator::QEXTMvvmProjectManagerDecorator(const QEXTMvvmProjectContext& project_context,
                                                 const QEXTMvvmUserInteractionContext& user_context)
    : p_impl(new ProjectManagerImpl(project_context, user_context))
{
}

QEXTMvvmProjectManagerDecorator::~QEXTMvvmProjectManagerDecorator()
{

}

//! Creates a new project in the directory 'dirname', returns 'true' in the case of success.
//! The directory should exist.
//! If provided name is empty, will call directory selector dialog using callback provided.
//! If current project is in unsaved state, will perform 'save-before-closing' procedure before
//! proceeding further.

bool QEXTMvvmProjectManagerDecorator::createNewProject(const QString &dirname)
{
    if (!p_impl->saveBeforeClosing())
        return failed;

    auto project_dir = dirname.isEmpty() ? p_impl->acquireNewProjectDir() : dirname;
    // empty project_dir string denotes 'cancel' during directory creation dialog
    return project_dir.isEmpty() ? failed : p_impl->project_manager->createNewProject(project_dir);
}

//! Saves current project, returns 'true' in the case of success.
//! The project should have a project directory defined, if it is not the case, it will
//! launch the procedure of directory selection using callback provided.

bool QEXTMvvmProjectManagerDecorator::saveCurrentProject()
{
    return p_impl->saveCurrentProject();
}

//! Saves the project under a given directory, returns true in the case of success.
//! The directory should exist already. If provided 'dirname' variable is empty,
//! it will acquire a new project directory using dialog provided.

bool QEXTMvvmProjectManagerDecorator::saveProjectAs(const QString &dirname)
{
    auto project_dir = dirname.isEmpty() ? p_impl->acquireNewProjectDir() : dirname;
    // empty project_dir variable denotes 'cancel' during directory creation dialog
    return project_dir.isEmpty() ? failed : p_impl->saveCurrentProjectAs(project_dir);
}

//! Opens existing project, returns 'true' in the case of success.
//! If provided name is empty, will call directory selector dialog using callback provided.
//! If current project is in unsaved state, it will perform 'save-before-closing' procedure before
//! proceeding further.

bool QEXTMvvmProjectManagerDecorator::openExistingProject(const QString &dirname)
{
    if (!p_impl->saveBeforeClosing())
        return failed;
    auto project_dir = dirname.isEmpty() ? p_impl->acquireExistingProjectDir() : dirname;
    // empty project_dir variable denotes 'cancel' during directory selection dialog
    return project_dir.isEmpty() ? failed : p_impl->project_manager->openExistingProject(project_dir);
}

//! Returns current project directory.

QString QEXTMvvmProjectManagerDecorator::currentProjectDir() const
{
    return p_impl->currentProjectDir();
}

//! Returns true if project was modified since last save.

bool QEXTMvvmProjectManagerDecorator::isModified() const
{
    return p_impl->isModified();
}

//! Closes current project, returns 'true' if succeeded.
//! Will show the dialog, via callback provided, asking the user whether to save/discard/cancel.
//! Returns 'false' only if user has selected 'cancel' button.

bool QEXTMvvmProjectManagerDecorator::closeCurrentProject() const
{
    if (!p_impl->saveBeforeClosing())
        return failed;
    return succeeded;
}
