#ifndef _QEXTMVVMPROJECTPROJECTMANAGER_H
#define _QEXTMVVMPROJECTPROJECTMANAGER_H

#include <qextMvvmProjectManagerInterface.h>

#include <memory>

namespace ModelView
{

struct QEXTMvvmProjectContext;

//! Responsible for handling new/save/save-as/close Project logic, where the Project represents
//! a collection of serialized application models in the project directory.

//! This ProjectManager requires certain prerequisites to function properly: for example,
//! the creation of a new project will be possible only if the old project is in a saved state. See
//! description to the class methods.

class QEXT_MVVM_API QEXTMvvmProjectManager : public ModelView::QEXTMvvmProjectManagerInterface
{
public:
    QEXTMvvmProjectManager(const QEXTMvvmProjectContext& context);
    ~QEXTMvvmProjectManager() override;

    QEXTMvvmProjectManager(const QEXTMvvmProjectManager& other) = delete;
    QEXTMvvmProjectManager& operator=(const QEXTMvvmProjectManager& other) = delete;

    bool createNewProject(const std::string& dirname) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname) override;

    bool openExistingProject(const std::string& dirname) override;

    std::string currentProjectDir() const override;

    bool isModified() const override;

    bool closeCurrentProject() const override;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPROJECTPROJECTMANAGER_H
