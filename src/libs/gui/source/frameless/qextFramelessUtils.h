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

#ifndef _QEXTFRAMELESSUTILS_H
#define _QEXTFRAMELESSUTILS_H

#include <qextGuiGlobal.h>

#include <QObject>
#include <QMouseEvent>
#include <QLoggingCategory>

namespace Private
{

class ObjectHelper : public QObject
{
public:
    static inline bool sendEvent(QObject *obj, QEvent *event)
    {
        return static_cast<ObjectHelper *>(obj)->event(event);
    }
};
}


inline QPoint getMouseEventScenePos(const QMouseEvent *event)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return event->scenePosition().toPoint();
#else
    return event->windowPos().toPoint();
#endif
}

inline QPoint getMouseEventGlobalPos(const QMouseEvent *event)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return event->globalPosition().toPoint();
#else
    return event->screenPos().toPoint();
#endif
}



#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
using QT_NATIVE_EVENT_RESULT_TYPE = qintptr;
using QT_ENTER_EVENT_TYPE = QEnterEvent;
#else
using QT_NATIVE_EVENT_RESULT_TYPE = long;
using QT_ENTER_EVENT_TYPE = QEvent;
#endif

// #ifndef QWINDOWKIT_CONFIG
// #  define QWINDOWKIT_CONFIG(feature) ((1 / QWINDOWKIT_##feature) == 1)
// #endif

struct QExtScreenRectCallbackInterface
{
    virtual ~QExtScreenRectCallbackInterface() {}
    virtual QRect screenRect(const QSize &) = 0;
};

// typedef QRect(*QExtScreenRectCallbackFunc)(const QSize &);
// using ScreenRectCallback = std::function<QRect(const QSize &)>;


#endif // QEXTFRAMELESSUTILS_H
