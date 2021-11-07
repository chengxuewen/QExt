#ifndef _QEXTMVVMPROJECTMANAGERINTERFACE_H
#define _QEXTMVVMPROJECTMANAGERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QString>

//! Interface class for QEXTMvvmProjectManager family.

//! Responsible for handling new/save/save-as/close Project logic, where the Project represents
//! a collection of serialized application models in the project directory.

class QEXT_MVVM_API QEXTMvvmProjectManagerInterface
{
public:
    virtual ~QEXTMvvmProjectManagerInterface() { }

    virtual bool createNewProject(const QString &dirName = QString()) = 0;

    virtual bool saveCurrentProject() = 0;

    virtual bool saveProjectAs(const QString &dirName = QString()) = 0;

    virtual bool openExistingProject(const QString &dirName = QString()) = 0;

    virtual QString currentProjectDir() const = 0;

    virtual bool isModified() const = 0;

    virtual bool closeCurrentProject() const = 0;
};


#endif // _QEXTMVVMPROJECTMANAGERINTERFACE_H
