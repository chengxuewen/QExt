// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECTMANAGER_H
#define MVVM_PROJECT_PROJECTMANAGER_H

#include <qextMvvmProjectManagerInterface.h>
#include <memory>

namespace ModelView {

struct QExtMvvmProjectContext;

//! Responsible for handling new/save/save-as/close QExtMvvmProject logic, where the QExtMvvmProject represents
//! a collection of serialized application models in the project directory.

//! This QExtMvvmProjectManager requires certain prerequisites to function properly: for example,
//! the creation of a new project will be possible only if the old project is in a saved state. See
//! description to the class methods.

class QEXT_MVVM_API QExtMvvmProjectManager : public ModelView::QExtMvvmProjectManagerInterface {
public:
    QExtMvvmProjectManager(const QExtMvvmProjectContext& context);
    ~QExtMvvmProjectManager() override;

    QExtMvvmProjectManager(const QExtMvvmProjectManager& other) = delete;
    QExtMvvmProjectManager& operator=(const QExtMvvmProjectManager& other) = delete;

    bool createNewProject(const std::string& dirname) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname) override;

    bool openExistingProject(const std::string& dirname) override;

    std::string currentProjectDir() const override;

    bool isModified() const override;

    bool closeCurrentProject() const override;

private:
    struct ProjectManagerImpl;
    QExtUniquePointer<ProjectManagerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTMANAGER_H
