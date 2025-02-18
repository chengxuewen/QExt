// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PROJECT_PROJECTMANAGERDECORATOR_H
#define MVVM_PROJECT_PROJECTMANAGERDECORATOR_H

#include "model/interfaces/projectmanagerinterface.h"
#include <memory>

namespace ModelView {

struct ProjectContext;
struct UserInteractionContext;

//! Decorator for ProjectManager to provide interaction with the user on open/save-as requests.
//! It relies on the same interface and adds additional logic related to "unsaved" data.

//! For example, on createNewProject it will check if previous project is saved, and will
//! call external dialog save/discard/cancel via provided callback.

class QEXT_MVVM_API ProjectManagerDecorator : public ProjectManagerInterface {
public:
    ProjectManagerDecorator(const ProjectContext& project_context,
                            const UserInteractionContext& user_context);

    ~ProjectManagerDecorator() override;
    ProjectManagerDecorator(const ProjectManagerDecorator& other) = delete;
    ProjectManagerDecorator& operator=(const ProjectManagerDecorator& other) = delete;

    bool createNewProject(const std::string& dirname = {}) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname = {}) override;

    bool openExistingProject(const std::string& dirname = {}) override;

    std::string currentProjectDir() const override;

    bool isModified() const override;

    bool closeCurrentProject() const override;

private:
    struct ProjectManagerImpl;
    QExtUniquePointer<ProjectManagerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PROJECT_PROJECTMANAGERDECORATOR_H
