#ifndef _QEXTMVVMPROJECTPROJECTMANAGERDECORATOR_H
#define _QEXTMVVMPROJECTPROJECTMANAGERDECORATOR_H

#include <qextMvvmProjectManagerInterface.h>

#include <memory>

namespace ModelView
{

struct QEXTMvvmProjectContext;
struct UserInteractionContext;

//! Decorator for ProjectManager to provide interaction with the user on open/save-as requests.
//! It relies on the same interface and adds additional logic related to "unsaved" data.

//! For example, on createNewProject it will check if previous project is saved, and will
//! call external dialog save/discard/cancel via provided callback.

class QEXT_MVVM_API QEXTMvvmProjectManagerDecorator : public QEXTMvvmProjectManagerInterface
{
public:
    QEXTMvvmProjectManagerDecorator(const QEXTMvvmProjectContext& project_context,
                            const UserInteractionContext& user_context);

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

#endif // _QEXTMVVMPROJECTPROJECTMANAGERDECORATOR_H
