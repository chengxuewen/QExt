// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_STYLEUTILS_H
#define MVVM_EDITORS_STYLEUTILS_H

#include <qextMvvmGlobal.h>

namespace ModelView::Style {

//! Returns int value corresponding to pixmap in standard Qt table/tree decorations.
QEXT_MVVM_API int DefaultPixmapSize();

//! Returns default height of info bar
QEXT_MVVM_API int DefaultInfoBarHeight();

//! Returns default size of text on info bar.
QEXT_MVVM_API int DefaultInfoBarTextSize();

} // namespace ModelView::Style

#endif // MVVM_EDITORS_STYLEUTILS_H
