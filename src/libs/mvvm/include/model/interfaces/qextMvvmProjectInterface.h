#ifndef _QEXTMVVMPROJECTINTERFACE_H
#define _QEXTMVVMPROJECTINTERFACE_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView
{

//! Interface to manipulate projects on disk.
//! QEXTMvvmProject represents content of all application models in a folder on disk.

class QEXT_MVVM_API QEXTMvvmProjectInterface
{
public:
    virtual ~QEXTMvvmProjectInterface() = default;
    virtual std::string projectDir() const = 0;
    virtual bool save(const std::string& dirname) const = 0;
    virtual bool load(const std::string& dirname) = 0;
    virtual bool isModified() const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMPROJECTINTERFACE_H
