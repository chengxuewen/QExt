#ifndef _QEXTMVVMSTYLEUTILS_H
#define _QEXTMVVMSTYLEUTILS_H

#include <qextMvvmGlobal.h>

namespace Style
{

//! Returns int value corresponding to pixmap in standard Qt table/tree decorations.
QEXT_MVVM_API int DefaultPixmapSize();

//! Returns default height of info bar
QEXT_MVVM_API int DefaultInfoBarHeight();

//! Returns default size of text on info bar.
QEXT_MVVM_API int DefaultInfoBarTextSize();

} // namespace Style


#endif // _QEXTMVVMSTYLEUTILS_H
