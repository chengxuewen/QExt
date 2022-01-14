#ifndef _QEXTMVVMINTERFACESPROJECTMANAGERINTERFACE_H
#define _QEXTMVVMINTERFACESPROJECTMANAGERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <string>

namespace ModelView
{

//! Interface class for ProjectManager family.

//! Responsible for handling new/save/save-as/close Project logic, where the Project represents
//! a collection of serialized application models in the project directory.

class QEXT_MVVM_API QEXTMvvmProjectManagerInterface
{
public:
    virtual ~QEXTMvvmProjectManagerInterface() = default;
    virtual bool createNewProject(const std::string& dirname = {}) = 0;

    virtual bool saveCurrentProject() = 0;

    virtual bool saveProjectAs(const std::string& dirname = {}) = 0;

    virtual bool openExistingProject(const std::string& dirname = {}) = 0;

    virtual std::string currentProjectDir() const = 0;

    virtual bool isModified() const = 0;

    virtual bool closeCurrentProject() const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMINTERFACESPROJECTMANAGERINTERFACE_H
