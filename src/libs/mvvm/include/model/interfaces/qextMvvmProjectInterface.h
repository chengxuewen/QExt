#ifndef _QEXTMVVMPROJECTINTERFACE_H
#define _QEXTMVVMPROJECTINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QString>

//! Interface to manipulate projects on disk.
//! Project represents content of all application models in a folder on disk.

class QEXT_MVVM_API QEXTMvvmProjectInterface
{
public:
    virtual ~QEXTMvvmProjectInterface() { }

    virtual QString projectDir() const = 0;
    virtual bool save(const QString &dirName) = 0;
    virtual bool load(const QString &dirName) = 0;
    virtual bool isModified() const = 0;
};


#endif // _QEXTMVVMPROJECTINTERFACE_H
