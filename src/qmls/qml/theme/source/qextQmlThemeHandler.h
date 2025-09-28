/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTQMLTHEMEHANDLER_H
#define _QEXTQMLTHEMEHANDLER_H

#include <qextQmlThemeGlobal.h>

#include <QObject>

class QExtQmlThemeHandlerPrivate;
class QEXT_QMLTHEME_API QExtQmlThemeHandler : public QObject
{
    Q_OBJECT
public:
    QExtQmlThemeHandler(const QString &name, const QString &path);
    ~QExtQmlThemeHandler() override;

    QString themeName() const;
    QString themePath() const;
    QString lastError() const;

    bool isValid() const;
    bool isLoaded() const;

    QVariant propertyData(const QString &fieldKey, const QString &propertyKey);
    const QMap<QString, QVariantMap> themeData() const;
    const QVariantMap themeInfo() const;

Q_SIGNALS:
    void themeDataChanged();

protected:
    void setLastError(const QString &string);
    void setThemeData(const QMap<QString, QVariantMap> &data);

    QScopedPointer<QExtQmlThemeHandlerPrivate> dd_ptr;

private:
    friend class QExtQmlThemeManager;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlThemeHandler)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlThemeHandler)
};

#endif // _QEXTQMLTHEMEHANDLER_H
