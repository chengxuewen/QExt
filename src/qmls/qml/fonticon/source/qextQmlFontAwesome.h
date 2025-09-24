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

#ifndef _QEXTQMLFONTAWESOME_H
#define _QEXTQMLFONTAWESOME_H

#include <qextQmlFontIconGlobal.h>
#include <qextQmlRegistration.h>
#include <qextFontAwesome.h>

#include <QQmlEngine>

class QEXT_QMLFONTICON_API QExtQmlFontAwesome : public QExtFontAwesome
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    QEXT_QML_SINGLETON()
public:
    ~QExtQmlFontAwesome();
    static QEXT_QML_SINGLETON_TYPE(QExtQmlFontAwesome) *create(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QExtQmlFontAwesome *instance();

    Q_INVOKABLE QString fontUrl(int value) const;
    Q_INVOKABLE QString fontUrl(const QString &key) const;

protected:
    explicit QExtQmlFontAwesome(QObject *parent = QEXT_NULLPTR);
};

#endif // _QEXTQMLFONTAWESOME_H
