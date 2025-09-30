/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#ifndef _QEXTQMLFONTICON_H
#define _QEXTQMLFONTICON_H

#include <qextQmlFontIconGlobal.h>
#include <qextQmlFontIconInfo.h>
#include <qextQmlSingleton.h>

#include <QObject>
#include <QQmlEngine>
#include <QScopedPointer>

class QExtQmlWorld;
class QExtQmlFontIconPrivate;
class QEXT_QMLFONTICON_API QExtQmlFontIcon : public QExtQmlModuleSingleton<QExtQmlFontIcon>
{
    Q_OBJECT
    QEXT_DECLARE_QML_SINGLETON(QExtQmlFontIcon)
public:
    Q_INVOKABLE bool isFontIconUrl(const QString &url);
    Q_INVOKABLE QExtQmlFontIconInfo fontIconInfoFromUrl(const QString &url);
    Q_INVOKABLE bool parseFontIconInfoFromUrl(const QString &url, QExtQmlFontIconInfo *fontIconInfo);
    Q_INVOKABLE QString fontIconUrl(const QString &family, const QString &key);

    Q_INVOKABLE QString version() const override;
    void registerTypes(const char *url = nullptr) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

protected:
    QExtQmlFontIcon();
    ~QExtQmlFontIcon() override;

    QScopedPointer<QExtQmlFontIconPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlFontIcon)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlFontIcon)
};

#endif // _QEXTQMLFONTICON_H
