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

#ifndef _QEXTQML_H
#define _QEXTQML_H

#include <qextQmlGlobal.h>
#include <qextQmlSingleton.h>

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QScopedPointer>

class QExtQmlWorld;
class QExtQmlPrivate;
class QEXT_QML_API QExtQml : public QExtQmlModuleSingleton<QExtQml>
{
    Q_OBJECT
    QEXT_DECLARE_QML_SINGLETON(QExtQml)
    Q_PROPERTY(QQuickWindow* rootWindow READ rootWindow WRITE setRootWindow NOTIFY rootWindowChanged)
public:
    enum StateEnum
    {
        StateNormal = 0,
        StateHovered,
        StatePressed,
        StateChecked
    };
    Q_ENUM(StateEnum)

    enum PositionEnum
    {
        PositionLeft = 0,
        PositionRight,
        PositionTop,
        PositionBottom,
        PositionCenter
    };
    Q_ENUM(PositionEnum)

    Q_INVOKABLE QString stateToString(int state) const;
    Q_INVOKABLE int stateToEnum(const QString &state) const;

    Q_INVOKABLE QString qtVersion() const;
    Q_INVOKABLE int qtVersionMajor() const;
    Q_INVOKABLE int qtVersionMinor() const;
    Q_INVOKABLE int qtVersionPatch() const;

    QQuickWindow *rootWindow() const;
    void setRootWindow(QQuickWindow *window);

    Q_INVOKABLE QString version() const override;
    void registerTypes(const char *url = nullptr) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

Q_SIGNALS:
    void rootWindowChanged(QQuickWindow *window);

protected:
    QExtQml();
    ~QExtQml() override;

    QScopedPointer<QExtQmlPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQml)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQml)
};

#endif // _QEXTQML_H
