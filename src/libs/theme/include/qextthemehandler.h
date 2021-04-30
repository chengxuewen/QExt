/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#ifndef QEXTTHEMEHANDLER_H
#define QEXTTHEMEHANDLER_H

#include <qextobject.h>

#include <qextthemeglobal.h>

#include <QObject>
#include <QMap>
#include <QVariantMap>

class QEXTThemeHandlerPrivate;
class QEXT_THEME_API QEXTThemeHandler : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTThemeHandler(const QString &themeName, const QString &themePath);
    ~QEXTThemeHandler();

    QString themeName() const;
    QString themePath() const;
    QString lastError() const;
    bool isThemeValid() const;
    bool isTHemeLoad() const;

    void setLastError(const QString &text);
    void setThemeData(const QMap<QString, QVariantMap> &data);

    QVariant propertyData(const QString &fieldKey, const QString &propertyKey);
    QMap<QString, QVariantMap> themeDataMap() const;
    QVariantMap themeInfo() const;

Q_SIGNALS:
    void themeDataChanged();

private:
    QEXT_DECLARE_PRIVATE(QEXTThemeHandler)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeHandler)
};

#endif // QEXTTHEMEHANDLER_H
