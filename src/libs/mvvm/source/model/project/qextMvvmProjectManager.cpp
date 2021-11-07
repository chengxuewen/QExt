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
#include <qextMvvmProjectUtils.h>

namespace
{
const bool succeeded = true;
const bool failed = false;
} // namespace

struct QEXTMvvmProjectManager::ProjectManagerImpl {
    QScopedPointer<QEXTMvvmProjectInterface> m_currentProject;
    QEXTMvvmProjectContext m_projectContext;

    ProjectManagerImpl(QEXTMvvmProjectContext context) : m_projectContext(context)
    {
        createNewProject();
    }

    //! Closes current project. Used in assumption that project was already saved.
    void createNewProject()
    {
        m_currentProject.reset(ProjectUtils::CreateUntitledProject(m_projectContext));
    }

    //! Returns true if the project has directory already defined.
    bool projectHasDir() const { return !m_currentProject->projectDir().isEmpty(); }

    //! Saves project in project directory. If directory is not defined
    bool saveCurrentProject() { return saveCurrentProjectAs(m_currentProject->projectDir()); }

    //! Saves the project into a given directory.
    bool saveCurrentProjectAs(const QString &dirname)
    {
        return m_currentProject->save(dirname);
    }

    //! Loads the project from a given directory.
    bool loadFrom(const QString &dirname) { return m_currentProject->load(dirname); }

    //! Returns true if project has been modified after the last save.
    bool isModified() const { return m_currentProject->isModified(); }
};

//! Constructor for QEXTMvvmProjectManager.

QEXTMvvmProjectManager::QEXTMvvmProjectManager(const QEXTMvvmProjectContext& context)
    : p_impl(new ProjectManagerImpl(context))
{
}

QEXTMvvmProjectManager::~QEXTMvvmProjectManager()
{

}

//! Creates a new project, returns 'true' in the case of success.
//! Current project has to be in a saved state, otherwise will return false.

bool QEXTMvvmProjectManager::createNewProject(const QString &dirname)
{
    if (p_impl->isModified())
        return failed;
    p_impl->createNewProject();
    return p_impl->saveCurrentProjectAs(dirname);
}

//! Saves current project, returns 'true' in the case of success.
//! The project should have a project directory defined to succeed.

bool QEXTMvvmProjectManager::saveCurrentProject()
{
    if (!p_impl->projectHasDir())
        return failed;
    return p_impl->saveCurrentProject();
}

//! Saves the project under a given directory, returns true in the case of success.
//! The directory should exist already.

bool QEXTMvvmProjectManager::saveProjectAs(const QString &dirname)
{
    return p_impl->saveCurrentProjectAs(dirname);
}

//! Opens existing project, returns 'true' in the case of success.
//! Current project should be in a saved state, new project should exist.

bool QEXTMvvmProjectManager::openExistingProject(const QString &dirname)
{
    if (p_impl->isModified())
        return failed;
    p_impl->createNewProject();
    return p_impl->loadFrom(dirname);
}

//! Returns current project directory.

QString QEXTMvvmProjectManager::currentProjectDir() const
{
    return p_impl->m_currentProject ? p_impl->m_currentProject->projectDir() : QString();
}

//! Returns true if project was modified since last save.

bool QEXTMvvmProjectManager::isModified() const
{
    return p_impl->isModified();
}

//! Closes current project (without saving).
//! No checks whether it is modified or not being performed.

bool QEXTMvvmProjectManager::closeCurrentProject() const
{
    // no special operation is required to close the project
    p_impl->createNewProject(); // ready for further actions
    return succeeded;
}
