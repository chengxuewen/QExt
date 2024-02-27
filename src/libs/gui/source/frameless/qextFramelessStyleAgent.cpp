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

#include <private/qextFramelessStyleAgent_p.h>

#include <QVariant>


/*!
    \class QExtFramelessStyleAgent
    \brief QExtFramelessStyleAgent provides some features related to system theme.

    Qt6.6 started to support system theme detection, this class is intended as an auxiliary
    support for lower versions of Qt. If your Qt already supports it, it is recommended that
    you don't include this class in your build system.
*/

QExtFramelessStyleAgentPrivate::QExtFramelessStyleAgentPrivate(QExtFramelessStyleAgent *q)
    : q_ptr(q)
{
}

QExtFramelessStyleAgentPrivate::~QExtFramelessStyleAgentPrivate()
{
    removeSystemThemeHook();
}

void QExtFramelessStyleAgentPrivate::init()
{
    setupSystemThemeHook();
}

void QExtFramelessStyleAgentPrivate::notifyThemeChanged(QExtFramelessStyleAgent::SystemTheme theme)
{
    if (theme == systemTheme)
    {
        return;
    }
    systemTheme = theme;

    Q_Q(QExtFramelessStyleAgent);
    Q_EMIT q->systemThemeChanged();
}

/*!
    Constructor. Since it is not related to a concrete window instance, it is better to be used
    as a singleton.
*/
QExtFramelessStyleAgent::QExtFramelessStyleAgent(QObject *parent)
    : QExtFramelessStyleAgent(new QExtFramelessStyleAgentPrivate(this), parent)
{
}

/*!
    Destructor.
*/
QExtFramelessStyleAgent::~QExtFramelessStyleAgent()
{
}

/*!
    Returns the system theme.
*/
QExtFramelessStyleAgent::SystemTheme QExtFramelessStyleAgent::systemTheme() const
{
    Q_D(const QExtFramelessStyleAgent);
    return d->systemTheme;
}

/*!
    \internal
*/
QExtFramelessStyleAgent::QExtFramelessStyleAgent(QExtFramelessStyleAgentPrivate *d, QObject *parent)
    : QObject(parent)
    , dd_ptr(d)
{
    d->init();
}

/*!
    \fn void QExtFramelessStyleAgent::systemThemeChanged()

    This signal is emitted when the system theme changes.
*/

// }
