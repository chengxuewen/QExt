#ifndef _QEXTMVVMBINUTILS_H
#define _QEXTMVVMBINUTILS_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView ::Utils
{

//! Returns true if file is binary
QEXT_MVVM_API bool is_binary(const std::string& filename);

//! Returns true if file is text/ascii
QEXT_MVVM_API bool is_text(const std::string& filename);

} // namespace ModelView::Utils

#endif // _QEXTMVVMBINUTILS_H
