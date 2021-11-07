#ifndef _QEXTMVVMPROJECTMANAGER_H
#define _QEXTMVVMPROJECTMANAGER_H

#include <qextMvvmProjectManagerInterface.h>

#include <QScopedPointer>


struct QEXTMvvmProjectContext;

//! Responsible for handling new/save/save-as/close Project logic, where the Project represents
//! a collection of serialized application models in the project directory.

//! This QEXTMvvmProjectManager requires certain prerequisites to function properly: for example,
//! the creation of a new project will be possible only if the old project is in a saved state. See
//! description to the class methods.

class QEXT_MVVM_API QEXTMvvmProjectManager : public QEXTMvvmProjectManagerInterface
{
public:
    QEXTMvvmProjectManager(const QEXTMvvmProjectContext& context);
    ~QEXTMvvmProjectManager() QEXT_DECL_OVERRIDE;

    QEXTMvvmProjectManager(const QEXTMvvmProjectManager& other) = delete;
    QEXTMvvmProjectManager& operator=(const QEXTMvvmProjectManager& other) = delete;

    bool createNewProject(const QString &dirname) QEXT_DECL_OVERRIDE;

    bool saveCurrentProject() QEXT_DECL_OVERRIDE;

    bool saveProjectAs(const QString &dirname) QEXT_DECL_OVERRIDE;

    bool openExistingProject(const QString &dirname) QEXT_DECL_OVERRIDE;

    QString currentProjectDir() const QEXT_DECL_OVERRIDE;

    bool isModified() const QEXT_DECL_OVERRIDE;

    bool closeCurrentProject() const QEXT_DECL_OVERRIDE;

private:
    struct ProjectManagerImpl;
    QScopedPointer<ProjectManagerImpl> p_impl;
};


#endif // _QEXTMVVMPROJECTMANAGER_H
