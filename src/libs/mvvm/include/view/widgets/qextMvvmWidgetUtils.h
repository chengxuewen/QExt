#ifndef _QEXTMVVMWIDGETUTILS_H
#define _QEXTMVVMWIDGETUTILS_H

#include <QString>
#include <QStringList>
#include <qextMvvmGlobal.h>
#include <string>
#include <QVector>

class QColor;
class QSize;
class QMainWindow;
class QLabel;

//! Collection of various widget-related utils.

struct QEXT_MVVM_API QEXTMvvmWidgetUtils
{

//! Returns random color.
    static QColor RandomColor();

//! Returns the name of random color.
    static QString RandomNamedColor();

//! Returns true if it is Windows.
    static bool IsWindowsHost();

//! Returns true if it is Mac.
    static bool IsMacHost();

//! Returns true if it is Linux.
    static bool IsLinuxHost();

//! Returns a string where Linux path to the file is striped using '~/'.
    static QString WithTildeHomePath(const QString &path);

//! Returns a title composed from last part of project path, and `is_modified` flag.
    static QString ProjectWindowTitle(const QString &project_dir, bool is_modified);

//! Returns width of the letter 'M' deduced from current font metrics.
    static int WidthOfLetterM();

//! Returns height of the letter 'M' deduced from current font metrics.
    static int HeightOfLetterM();

//! Returns size corresponding to actual size of letter `M` basing on current font metrics.
    static QSize SizeOfLetterM();

//! Returns size in points of default system font.
    static int SystemPointSize();

//! Finds main window.
    static QMainWindow *FindMainWindow();

//! Returns text wrapped into 'href' tag to provide clickable links in QLabel.
//! Example: <a href="tag">text</a>, if 'tag' is empty, 'text' will be used instead.
    static QString ClickableText(const QString &text, const QString &tag = {});

//! Set label's font size to system font size scaled by given factor.
    static void ScaleLabelFont(QLabel *label, double scale);

//! Converts vector of strings to QStringList.
    static QStringList toStringList(const QVector<QString> &vec);

//! Converts vector of strings to QStringList.
    static QVector<QString> fromStringList(const QStringList &string_list);

//! Converts vector of strings to byte array.
    static QByteArray serialize(const QStringList &data);

//! Converts byte array to vector of strings.
    static QStringList deserialize(const QByteArray &byteArray);

};

#endif // _QEXTMVVMWIDGETUTILS_H
