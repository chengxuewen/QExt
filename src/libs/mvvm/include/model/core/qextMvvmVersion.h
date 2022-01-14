#ifndef _QEXTMVVMCOREVERSION_H
#define _QEXTMVVMCOREVERSION_H

//! @file version.h
//! Automatically generated from mvvm_version.h.in

#include <string>

namespace ModelView
{

//! Returns major project version.
inline int ProjectVersionMajor()
{
    const int project_version_major = 0;
    return project_version_major;
}

//! Returns minor project version.
inline int ProjectVersionMinor()
{
    const int project_version_minor = 2;
    return project_version_minor;
}

//! Returns patch project version.
inline int ProjectVersionPatch()
{
    const int project_version_path = 0;
    return project_version_path;
}

//! Returns project version string
inline std::string ProjectVersion()
{
    const std::string project_version = "0.2.0";
    return project_version;
}

} // namespace ModelView

#endif // _QEXTMVVMCOREVERSION_H
