#ifndef _QEXTMVVMPROJECTMANAGERDECORATOR_H
#define _QEXTMVVMPROJECTMANAGERDECORATOR_H

#include <memory>
#include <qextMvvmProjectManagerInterface.h>

namespace ModelView
{

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

    ~QEXTMvvmProjectManagerDecorator() override;
    QEXTMvvmProjectManagerDecorator(const QEXTMvvmProjectManagerDecorator& other) = delete;
    QEXTMvvmProjectManagerDecorator& operator=(const QEXTMvvmProjectManagerDecorator& other) = delete;

    bool createNewProject(const std::string& dirname = {}) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname = {}) override;

    bool openExistingProject(const std::string& dirname = {}) override;

    std::string currentProjectDir() const override;

    bool isModified() const override;

    bool closeCurrentProject() const override;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTMANAGERDECORATOR_H
