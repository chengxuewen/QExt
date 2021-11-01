#ifndef _QEXTMVVMPROJECTMANAGER_H
#define _QEXTMVVMPROJECTMANAGER_H

#include <memory>
#include <qextMvvmProjectManagerInterface.h>

namespace ModelView
{

struct QEXTMvvmProjectContext;

//! Responsible for handling new/save/save-as/close QEXTMvvmProject logic, where the QEXTMvvmProject represents
//! a collection of serialized application models in the project directory.

//! This QEXTMvvmProjectManager requires certain prerequisites to function properly: for example,
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

#endif // _QEXTMVVMPROJECTMANAGER_H
