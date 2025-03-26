// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_WIDGETUTILS_H
#define MVVM_WIDGETS_WIDGETUTILS_H

#include <qextMvvmGlobal.h>
#include <QString>
#include <QStringList>
#include <string>
#include <vector>

class QColor;
class QSize;
class QMainWindow;
class QLabel;

//! Collection of various widget-related utils.

namespace ModelView
{
namespace Utils
{

//! Returns random color.
QEXT_MVVM_API QColor RandomColor();

//! Returns the name of random color.
QEXT_MVVM_API std::string RandomNamedColor();

//! Returns true if it is Windows.
QEXT_MVVM_API bool IsWindowsHost();

//! Returns true if it is Mac.
QEXT_MVVM_API bool IsMacHost();

//! Returns true if it is Linux.
QEXT_MVVM_API bool IsLinuxHost();

//! Returns a string where Linux path to the file is striped using '~/'.
QEXT_MVVM_API QString WithTildeHomePath(const QString& path);

//! Returns a title composed from last part of project path, and `is_modified` flag.
QEXT_MVVM_API QString ProjectWindowTitle(const QString& project_dir, bool is_modified);

//! Returns width of the letter 'M' deduced from current font metrics.
QEXT_MVVM_API int WidthOfLetterM();

//! Returns height of the letter 'M' deduced from current font metrics.
QEXT_MVVM_API int HeightOfLetterM();

//! Returns size corresponding to actual size of letter `M` basing on current font metrics.
QEXT_MVVM_API QSize SizeOfLetterM();

//! Returns size in points of default system font.
QEXT_MVVM_API int SystemPointSize();

//! Finds main window.
QEXT_MVVM_API QMainWindow* FindMainWindow();

//! Returns text wrapped into 'href' tag to provide clickable links in QLabel.
//! Example: <a href="tag">text</a>, if 'tag' is empty, 'text' will be used instead.
QEXT_MVVM_API QString ClickableText(const QString& text, const QString& tag = {});

//! Set label's font size to system font size scaled by given factor.
QEXT_MVVM_API void ScaleLabelFont(QLabel* label, double scale);

//! Converts vector of strings to QStringList.
QEXT_MVVM_API QStringList toStringList(const std::vector<std::string>& vec);

//! Converts vector of strings to QStringList.
QEXT_MVVM_API std::vector<std::string> fromStringList(const QStringList& string_list);

//! Converts vector of strings to byte array.
QEXT_MVVM_API QByteArray serialize(const QStringList& data);

//! Converts byte array to vector of strings.
QEXT_MVVM_API QStringList deserialize(const QByteArray& byteArray);

}
} // namespace ModelView::Utils

#endif // MVVM_WIDGETS_WIDGETUTILS_H
