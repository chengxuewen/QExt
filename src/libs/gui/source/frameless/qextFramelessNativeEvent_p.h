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

#ifndef _QEXTFRAMELESSNATIVEEVENT_P_H
#define _QEXTFRAMELESSNATIVEEVENT_P_H

#include <qextFramelessUtils.h>

class QExtFramelessNativeEventFilter;

class QEXT_GUI_API QExtFramelessNativeEventDispatcher
{
public:
    QExtFramelessNativeEventDispatcher();
    virtual ~QExtFramelessNativeEventDispatcher();

public:
    virtual bool nativeDispatch(const QByteArray &eventType, void *message, QT_NATIVE_EVENT_RESULT_TYPE *result);

public:
    void installNativeEventFilter(QExtFramelessNativeEventFilter *filter);
    void removeNativeEventFilter(QExtFramelessNativeEventFilter *filter);

protected:
    QVector<QExtFramelessNativeEventFilter *> m_nativeEventFilters;

    friend class QExtFramelessNativeEventFilter;

    Q_DISABLE_COPY(QExtFramelessNativeEventDispatcher)
};

class QEXT_GUI_API QExtFramelessNativeEventFilter
{
public:
    QExtFramelessNativeEventFilter();
    virtual ~QExtFramelessNativeEventFilter();

public:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, QT_NATIVE_EVENT_RESULT_TYPE *result) = 0;

protected:
    QExtFramelessNativeEventDispatcher *m_nativeDispatcher;

    friend class QExtFramelessNativeEventDispatcher;

    Q_DISABLE_COPY(QExtFramelessNativeEventFilter)
};

// Automatically install to QCoreApplication at construction
class QEXT_GUI_API QExtFramelessAppNativeEventFilter : public QExtFramelessNativeEventFilter
{
public:
    QExtFramelessAppNativeEventFilter();
    ~QExtFramelessAppNativeEventFilter() QEXT_OVERRIDE;
};

#endif // _QEXTFRAMELESSNATIVEEVENT_P_H
