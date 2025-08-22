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

#ifndef _QEXTQUICKKEYBOARD_H
#define _QEXTQUICKKEYBOARD_H

#include <qextQuickKeyboardGlobal.h>

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QScopedPointer>

class QExtQuickKeyboardWorld;
class QExtQuickKeyboardPrivate;
class QEXT_QUICKKEYBOARD_API QExtQuickKeyboard : public QObject
{
    Q_OBJECT

public:
    ~QExtQuickKeyboard();
    static QObject *qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QExtQuickKeyboard *instance();

    Q_INVOKABLE QString version() const;

    void registerTypes(const char *url);
    void initQmlEngine(QQmlEngine *engine, const char *uri);
    void initQuickRoot(QQuickWindow *rootWindow);

protected:
    explicit QExtQuickKeyboard(QObject *parent = QEXT_NULLPTR);

    QScopedPointer<QExtQuickKeyboardPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQuickKeyboard)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickKeyboard)
};

#endif // _QEXTQUICKKEYBOARD_H
