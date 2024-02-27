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

#ifndef _QEXTFRAMELESSSHAREDEVENT_P_H
#define _QEXTFRAMELESSSHAREDEVENT_P_H

#include <qextFramelessUtils.h>

class QExtFramelessSharedEventFilter;

class QEXT_GUI_API QExtFramelessSharedEventDispatcher
{
public:
    QExtFramelessSharedEventDispatcher();
    virtual ~QExtFramelessSharedEventDispatcher();

public:
    virtual bool sharedDispatch(QObject *obj, QEvent *event);

public:
    void installQExtFramelessSharedEventFilter(QExtFramelessSharedEventFilter *filter);
    void removeQExtFramelessSharedEventFilter(QExtFramelessSharedEventFilter *filter);

protected:
    QVector<QExtFramelessSharedEventFilter *> m_sharedEventFilters;

private:
    friend class QExtFramelessSharedEventFilter;
    Q_DISABLE_COPY(QExtFramelessSharedEventDispatcher)
};

class QEXT_GUI_API QExtFramelessSharedEventFilter
{
public:
    QExtFramelessSharedEventFilter();
    virtual ~QExtFramelessSharedEventFilter();

public:
    virtual bool sharedEventFilter(QObject *obj, QEvent *event) = 0;

protected:
    QExtFramelessSharedEventDispatcher *m_sharedDispatcher;

private:
    friend class QExtFramelessSharedEventDispatcher;
    Q_DISABLE_COPY(QExtFramelessSharedEventFilter)
};

#endif // _QEXTFRAMELESSSHAREDEVENT_P_H
