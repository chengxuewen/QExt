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

struct QExtMvvmProjectContext;
struct QExtMvvmUserInteractionContext;

//! Decorator for QExtMvvmProjectManager to provide interaction with the user on open/save-as requests.
//! It relies on the same interface and adds additional logic related to "unsaved" data.

//! For example, on createNewProject it will check if previous project is saved, and will
//! call external dialog save/discard/cancel via provided callback.

class QEXT_MVVM_API QExtMvvmProjectManagerDecorator : public QExtMvvmProjectManagerInterface {
public:
    QExtMvvmProjectManagerDecorator(const QExtMvvmProjectContext& project_context,
                            const QExtMvvmUserInteractionContext& user_context);

    ~QExtMvvmProjectManagerDecorator() override;
    QExtMvvmProjectManagerDecorator(const QExtMvvmProjectManagerDecorator& other) = delete;
    QExtMvvmProjectManagerDecorator& operator=(const QExtMvvmProjectManagerDecorator& other) = delete;

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
