/****************************************************************************
**
** Library: QEXTQmlQuick
**
** MIT License
**
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
** Copyright (c) 2019 toou http://www.toou.net
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

#ifndef _QEXTQMLTHEMEHANDLER_H
#define _QEXTQMLTHEMEHANDLER_H

#include <qextQmlThemeGlobal.h>

#include <QObject>

class QEXTQmlThemeHandlerPrivate;
class QEXT_QMLTHEME_API QEXTQmlThemeHandler : public QObject
{
    Q_OBJECT
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QEXTQmlThemeHandler)
    Q_DISABLE_COPY(QEXTQmlThemeHandler)

public:
    QEXTQmlThemeHandler(const QString &name, const QString &path);
    ~QEXTQmlThemeHandler();

    QString themeName() const;
    QString themePath() const;
    QString lastErrorString() const;

    bool isValid() const;
    bool isLoad() const;

    QVariant propertyData(const QString &fieldKey, const QString &propertyKey);
    const QMap<QString, QVariantMap> themeData() const;
    const QVariantMap themeInfo() const;

signals:
    void themeDataChanged();

protected:
    void setLastErrorString(const QString &string);
    void setThemeData(const QMap<QString, QVariantMap> &data);

    QScopedPointer<QEXTQmlThemeHandlerPrivate> dd_ptr;

private:
    friend class QEXTQmlThemeManager;
};

#endif // _QEXTQMLTHEMEHANDLER_H
