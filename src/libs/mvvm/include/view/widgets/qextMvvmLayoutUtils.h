#ifndef _QEXTMVVMLAYOUTUTILS_H
#define _QEXTMVVMLAYOUTUTILS_H

#include <qextMvvmGlobal.h>

class QLayout;
class QGridLayout;
class QWidget;

//! @namespace LayoutUtils
//! @brief Utility functions to add/remove widgets to the layout on the fly.
//! Taken from https://stackoverflow.com/questions/5395266/removing-widgets-from-qgridlayout
//! Caveat: according to explanations given, grid layouts can only grow and never shrink.

namespace LayoutUtils
{

//! Removes content from box layout.
QEXT_MVVM_API void clearLayout(QLayout* layout, bool deleteWidgets = true);

//! Removes row from grid layout (important: doesn't change row count).
QEXT_MVVM_API void removeRow(QGridLayout* layout, int row, bool deleteWidgets = true);

//! Removes column from grid layout.
QEXT_MVVM_API void removeColumn(QGridLayout* layout, int column, bool deleteWidgets = true);

//! Clear layout completely.
QEXT_MVVM_API void clearGridLayout(QGridLayout* layout, bool deleteWidgets = true);

//! Returns empty widget to occupy place in layout.
QEXT_MVVM_API QWidget* placeHolder();

} // namespace LayoutUtils

#endif // _QEXTMVVMLAYOUTUTILS_H
