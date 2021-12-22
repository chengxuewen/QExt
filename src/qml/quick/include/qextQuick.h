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

#ifndef _QEXTQUICK_H
#define _QEXTQUICK_H

#include <qextQuickGlobal.h>

#include <QQmlEngine>
#include <QQuickWindow>
#include <QObject>
#include <QScopedPointer>

class QEXTQuickWorld;
class QEXTQuickPrivate;
class QEXT_QUICK_API QEXTQuick : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTQuick)
    Q_DISABLE_COPY(QEXTQuick)

//    QML_ELEMENT

public:
    enum StateType {
        State_None = 0,
        State_Normal,
        State_Hovered,
        State_Pressed,
        State_Checked,
        State_Unchecked,
        State_PartiallyChecked,
    };
    Q_ENUMS(StateType)

    enum PositionType {
        Position_Left = 0,
        Position_Right,
        Position_Top,
        Position_Bottom,
        Position_Center
    };
    Q_ENUMS(PositionType)

    enum IconDisplayType {
        IconDisplay_TextOnly = 0,
        IconDisplay_IconOnly,
        IconDisplay_Left,
        IconDisplay_Right,
        IconDisplay_Top,
        IconDisplay_Bottom,
    };
    Q_ENUMS(IconDisplayType)

    enum IconType {
        Icon_Awesome = 0,
        Icon_SVG
    };
    Q_ENUMS(IconType)

    //h1=32px h2=24px h3=19px h4=16px h5=14px h6=12px
    enum class PixelSizeType {
        PH1 = 32,
        PH2 = 24,
        PH3 = 19,
        PH4 = 16,
        PH5 = 14,
        PH6 = 12,
        PH7 = 10,
        PH8 = 8
    };
    Q_ENUMS(PixelSizeType)

    enum DragDirectionType {
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
    Q_ENUMS(DragDirectionType)

    ~QEXTQuick();
    static QObject *qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QEXTQuick *instance();

    Q_INVOKABLE QString version() const;

    Q_INVOKABLE QString stateToString(int state) const;
    Q_INVOKABLE int stateToEnum(const QString &state) const;

    void registerTypes(const char *url);
    void initQmlEngine(QQmlEngine *engine, const char *uri);
    void initQuickRoot(QQuickWindow *rootWindow);
    void initWorld(QEXTQuickWorld *world);

    Q_INVOKABLE int mouseAreaCursorShape() const;
    void setMouseAreaCursorShape(const Qt::CursorShape &cursor);

protected:
    explicit QEXTQuick(QObject *parent = QEXT_DECL_NULLPTR);

    QScopedPointer<QEXTQuickPrivate> dd_ptr;
};



#endif // _QEXTQUICK_H
