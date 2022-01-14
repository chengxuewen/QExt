#ifndef _QEXTMVVMPROJECTPROJECT_H
#define _QEXTMVVMPROJECTPROJECT_H

#include <qextMvvmProjectInterface.h>

#include <memory>

namespace ModelView
{

struct QEXTMvvmProjectContext;

//! Project represents content of all application models in a folder on disk.
//! Responsible for saving/loading application models to/from disk.

class QEXT_MVVM_API QEXTMvvmProject : public ModelView::QEXTMvvmProjectInterface
{
public:
    QEXTMvvmProject(const QEXTMvvmProjectContext& context);
    ~QEXTMvvmProject();

    std::string projectDir() const override;

    bool save(const std::string& dirname) const override;

    bool load(const std::string& dirname) override;

    bool isModified() const override;

private:
    struct ProjectImpl;
    std::unique_ptr<ProjectImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPROJECTPROJECT_H
