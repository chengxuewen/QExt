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

#include <private/qextFramelessNativeEvent_p.h>

#include <QAbstractNativeEventFilter>
#include <QCoreApplication>


QExtFramelessNativeEventFilter::QExtFramelessNativeEventFilter() : m_nativeDispatcher(QEXT_NULLPTR)
{
}

QExtFramelessNativeEventFilter::~QExtFramelessNativeEventFilter()
{
    if (m_nativeDispatcher)
    {
        m_nativeDispatcher->removeNativeEventFilter(this);
    }
}

QExtFramelessNativeEventDispatcher::QExtFramelessNativeEventDispatcher() = default;

QExtFramelessNativeEventDispatcher::~QExtFramelessNativeEventDispatcher()
{
    QVector<QExtFramelessNativeEventFilter *>::Iterator iter;
    for (iter = m_nativeEventFilters.begin(); iter != m_nativeEventFilters.end(); ++iter)
    {
        (*iter)->m_nativeDispatcher = QEXT_NULLPTR;
    }
}

bool QExtFramelessNativeEventDispatcher::nativeDispatch(const QByteArray &eventType, void *message,
                                           QT_NATIVE_EVENT_RESULT_TYPE *result)
{
    QVector<QExtFramelessNativeEventFilter *>::Iterator iter;
    for (iter = m_nativeEventFilters.begin(); iter != m_nativeEventFilters.end(); ++iter)
    {
        if ((*iter)->nativeEventFilter(eventType, message, result))
        {
            return true;
        }
    }
    return false;
}

void QExtFramelessNativeEventDispatcher::installNativeEventFilter(QExtFramelessNativeEventFilter *filter)
{
    if (!filter || filter->m_nativeDispatcher)
    {
        return;
    }

    m_nativeEventFilters.append(filter);
    filter->m_nativeDispatcher = this;
}

void QExtFramelessNativeEventDispatcher::removeNativeEventFilter(QExtFramelessNativeEventFilter *filter)
{
    if (!m_nativeEventFilters.removeOne(filter))
    {
        return;
    }
    filter->m_nativeDispatcher = QEXT_NULLPTR;
}

// Avoid adding multiple global native event filters to QGuiApplication in this library.
class AppMasterNativeEventFilter : public QAbstractNativeEventFilter, public QExtFramelessNativeEventDispatcher
{
public:
    AppMasterNativeEventFilter()
    {
        qApp->installNativeEventFilter(this);
    }

    // The base class removes automatically
    ~AppMasterNativeEventFilter() QEXT_OVERRIDE = default;

    bool nativeEventFilter(const QByteArray &eventType, void *message,
                           QT_NATIVE_EVENT_RESULT_TYPE *result) QEXT_OVERRIDE
    {
        return nativeDispatch(eventType, message, result);
    }

    static AppMasterNativeEventFilter *instance;

    friend class QExtFramelessAppNativeEventFilter;
};

AppMasterNativeEventFilter *AppMasterNativeEventFilter::instance = QEXT_NULLPTR;

QExtFramelessAppNativeEventFilter::QExtFramelessAppNativeEventFilter()
{
    if (!AppMasterNativeEventFilter::instance)
    {
        AppMasterNativeEventFilter::instance = new AppMasterNativeEventFilter();
    }
    AppMasterNativeEventFilter::instance->installNativeEventFilter(this);
}

QExtFramelessAppNativeEventFilter::~QExtFramelessAppNativeEventFilter()
{
    AppMasterNativeEventFilter::instance->removeNativeEventFilter(this);
    if (AppMasterNativeEventFilter::instance->m_nativeEventFilters.isEmpty())
    {
        delete AppMasterNativeEventFilter::instance;
        AppMasterNativeEventFilter::instance = QEXT_NULLPTR;
    }
}
