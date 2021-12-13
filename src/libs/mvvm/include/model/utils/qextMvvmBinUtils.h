// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_BINUTILS_H
#define MVVM_UTILS_BINUTILS_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView ::Utils
{

//! Returns true if file is binary
QEXT_MVVM_API bool is_binary(const std::string& filename);

//! Returns true if file is text/ascii
QEXT_MVVM_API bool is_text(const std::string& filename);

} // namespace ModelView::Utils

#endif // MVVM_UTILS_BINUTILS_H
