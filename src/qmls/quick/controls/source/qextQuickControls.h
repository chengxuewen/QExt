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

#ifndef _QEXTQUICKCONTROLS_H
#define _QEXTQUICKCONTROLS_H

#include <qextQuickControlsGlobal.h>
#include <qextQmlSingleton.h>

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QScopedPointer>

class QExtQuickWorld;
class QExtQuickControlsPrivate;
class QEXT_QUICKCONTROLS_API QExtQuickControls : public QExtQmlSingleton<QExtQuickControls>
{
    Q_OBJECT
    QEXT_DECLARE_QML_SINGLETON(QExtQuickControls)
    Q_PROPERTY(QQuickWindow *rootWindow READ rootWindow NOTIFY rootWindowChanged)

public:
    enum ButtonStateEnum
    {
        ButtonStateNormal = 0,
        ButtonStateDisabled,
        ButtonStateHovered,
        ButtonStatePressed,
        ButtonStateChecked,
        ButtonStateUnchecked
    };
    Q_ENUM(ButtonStateEnum)

    enum PositionEnum
    {
        PositionLeft = 0,
        PositionRight,
        PositionTop,
        PositionBottom,
        PositionCenter
    };
    Q_ENUM(PositionEnum)

    enum IconDisplayType
    {
        IconDisplay_TextOnly = 0,
        IconDisplay_IconOnly,
        IconDisplay_Left,
        IconDisplay_Right,
        IconDisplay_Top,
        IconDisplay_Bottom,
    };
    Q_ENUM(IconDisplayType)

    enum IconType
    {
        Icon_Awesome = 0,
        Icon_SVG
    };
    Q_ENUM(IconType)

    //h1=32px h2=24px h3=19px h4=16px h5=14px h6=12px
    enum class PixelSizeType
    {
        PH1 = 32,
        PH2 = 24,
        PH3 = 19,
        PH4 = 16,
        PH5 = 14,
        PH6 = 12,
        PH7 = 10,
        PH8 = 8
    };
    Q_ENUM(PixelSizeType)

    enum DragDirectionType
    {
        DragDirection_Left = 0,
        DragDirection_LeftTop,
        DragDirection_LeftBottom,
        DragDirection_Right,
        DragDirection_RightTop,
        DragDirection_RightBottom,
        DragDirection_Top,
        DragDirection_Bottom,
        DragDirection_Center
    };
    Q_ENUM(DragDirectionType)

    QQuickWindow *rootWindow() const;

    Q_INVOKABLE QString buttonStateToString(int state) const;
    Q_INVOKABLE int buttonStateToEnum(const QString &state) const;

    void initWorld(QExtQuickWorld *world);
    void initQuickRoot(QQuickWindow *rootWindow);

    int mouseAreaCursorShape() const;
    void setMouseAreaCursorShape(const Qt::CursorShape &cursor);

    Q_INVOKABLE int svgIconVersion() const;

    Q_INVOKABLE QString version() const override;
    void registerTypes(const char *url = nullptr) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

Q_SIGNALS:
    void rootWindowChanged(QQuickWindow *window);

protected:
    QExtQuickControls();
    ~QExtQuickControls();

    QScopedPointer<QExtQuickControlsPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQuickControls)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickControls)
};

#endif // _QEXTQUICKCONTROLS_H
