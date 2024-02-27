/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024~Present ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2023-2024 Stdware Collections
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

#ifndef _QEXTFRAMELESSITEMDELEGATE_P_H
#define _QEXTFRAMELESSITEMDELEGATE_P_H


#include <QPoint>
#include <QObject>
#include <QWindow>

#include <qextFramelessUtils.h>

class QEXT_GUI_API QExtFramelessItemDelegate
{
public:
    QExtFramelessItemDelegate();
    virtual ~QExtFramelessItemDelegate();

public:
    // Item property query
    virtual QWindow *window(const QObject *obj) const = 0;
    virtual bool isEnabled(const QObject *obj) const = 0;
    virtual bool isVisible(const QObject *obj) const = 0;
    virtual QRect mapGeometryToScene(const QObject *obj) const = 0;

    // Host property query
    virtual QWindow *hostWindow(const QObject *host) const = 0;
    virtual bool isHostSizeFixed(const QObject *host) const = 0;
    virtual bool isWindowActive(const QObject *host) const = 0;
    virtual Qt::WindowStates getWindowState(const QObject *host) const = 0;
    virtual Qt::WindowFlags getWindowFlags(const QObject *host) const = 0;

    // Callbacks
    virtual void resetQtGrabbedControl(QObject *host) const;
    virtual void setWindowState(QObject *host, Qt::WindowStates state) const = 0;
    virtual void setCursorShape(QObject *host, Qt::CursorShape shape) const = 0;
    virtual void restoreCursorShape(QObject *host) const = 0;
    virtual void setWindowFlags(QObject *host, Qt::WindowFlags flags) const = 0;
    virtual void setWindowVisible(QObject *host, bool visible) const = 0;
    virtual void bringWindowToTop(QObject *host) const = 0;

private:
    Q_DISABLE_COPY(QExtFramelessItemDelegate)
};

#endif // _QEXTFRAMELESSITEMDELEGATE_P_H
