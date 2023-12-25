/****************************************************************************
**
** Library: QEXTQmlQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
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

#ifndef _QEXTQMLQUICKWORLD_H
#define _QEXTQMLQUICKWORLD_H

#include <qextQmlQuickGlobal.h>

#include <QObject>
#include <QQuickItem>
#include <QScopedPointer>

/***
 * the class is very important in QEXTQmlQuick
 * class can do some setup work:
 *  1.add theme file dir
 *  2.set app start up theme
 *  3.enable generate theme template json file to make some different theme file
 *
 * QEXTQmlQuickWorld initilize the whole application system, so it must created in App ApplicationWindow.
 *
 * QML:
 * QEXTQmlQuickWorld{
 *       appStartupTheme: "dark"
 *       appThemePaths:[
 *           "qrc:/themes/"
 *       ]
 * }
 * */
class QEXTQmlQuickWorldPrivate;
class QEXT_QUICK_API QEXTQmlQuickWorld : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTQmlQuickWorld)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTQmlQuickWorld)

    Q_PROPERTY(int mouseAreaCursorShape READ mouseAreaCursorShape WRITE setMouseAreaCursorShape)

public:
    explicit QEXTQmlQuickWorld(QQuickItem* parent = QEXT_NULLPTR);
    ~QEXTQmlQuickWorld();

    int mouseAreaCursorShape() const;
    void setMouseAreaCursorShape(const int &iShape);

protected Q_SLOTS:
    void onParentChanged(QQuickItem *parent);

protected:
    QScopedPointer<QEXTQmlQuickWorldPrivate> dd_ptr;
};

#endif // _QEXTQMLQUICKWORLD_H
