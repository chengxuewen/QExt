#ifndef _QEXTMVVMPROJECTMANAGERDECORATOR_H
#define _QEXTMVVMPROJECTMANAGERDECORATOR_H

#include <qextMvvmProjectManagerInterface.h>

#include <QScopedPointer>

struct QEXTMvvmProjectContext;
struct QEXTMvvmUserInteractionContext;

//! Decorator for QEXTMvvmProjectManager to provide interaction with the user on open/save-as requests.
//! It relies on the same interface and adds additional logic related to "unsaved" data.

//! For example, on createNewProject it will check if previous project is saved, and will
//! call external dialog save/discard/cancel via provided callback.

class QEXT_MVVM_API QEXTMvvmProjectManagerDecorator : public QEXTMvvmProjectManagerInterface
{
public:
    QEXTMvvmProjectManagerDecorator(const QEXTMvvmProjectContext& project_context,
                            const QEXTMvvmUserInteractionContext& user_context);

    ~QEXTMvvmProjectManagerDecorator() QEXT_DECL_OVERRIDE;
    QEXTMvvmProjectManagerDecorator(const QEXTMvvmProjectManagerDecorator& other) = delete;
    QEXTMvvmProjectManagerDecorator& operator=(const QEXTMvvmProjectManagerDecorator& other) = delete;

    bool createNewProject(const QString &dirname = QString()) QEXT_DECL_OVERRIDE;

    bool saveCurrentProject() QEXT_DECL_OVERRIDE;

    bool saveProjectAs(const QString &dirname = QString()) QEXT_DECL_OVERRIDE;

    bool openExistingProject(const QString &dirname = QString()) QEXT_DECL_OVERRIDE;

    QString currentProjectDir() const QEXT_DECL_OVERRIDE;

    bool isModified() const QEXT_DECL_OVERRIDE;

    bool closeCurrentProject() const QEXT_DECL_OVERRIDE;

private:
    struct ProjectManagerImpl;
    QScopedPointer<ProjectManagerImpl> p_impl;
};



#endif // MVVM_PROJECT_PROJECTMANAGERDECORATOR_H
