#ifndef _QEXTMVVMFILEUTILS_H
#define _QEXTMVVMFILEUTILS_H

#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView
{

namespace Utils
{

//! Returns true if file exists.
QEXT_MVVM_API bool exists(const std::string& fileName);

//! Joins two path elements into the path.
QEXT_MVVM_API std::string join(const std::string& part1, const std::string& part2);

//! Create directory, parent directory must exist. If path resolves to existing directory,
//! no error reported.
QEXT_MVVM_API bool create_directory(const std::string& path);

//! Removes file or empty directory.
QEXT_MVVM_API bool remove(const std::string& path);

//! Removes directory with all its content.
QEXT_MVVM_API void remove_all(const std::string& path);

//! Provide the filename of a file path.
QEXT_MVVM_API std::string base_name(const std::string& path);

//! Returns list of files with given extention found in given directory.
QEXT_MVVM_API std::vector<std::string> FindFiles(const std::string& dirname,
                                                     const std::string& ext);

//! Returns the path to the parent directory.
QEXT_MVVM_API std::string parent_path(const std::string& path);

//! Returns true if the file indicated by 'path' refers to empty file or directory.
QEXT_MVVM_API bool is_empty(const std::string& path);

} // namespace Utils

} // namespace ModelView

#endif // _QEXTMVVMFILEUTILS_H
