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

#include <private/qextFramelessAgent_p.h>
#include <qextFramelessUtils.h>
#include <qextGuiConfig.h>

#if defined(Q_OS_WINDOWS) && !QEXT_FEATURE_USE_FRAMELESS_QT_CONTEXT
#   include <private/qextFramelessContext_win_p.h>
#elif defined(Q_OS_MAC) && !QEXT_FEATURE_USE_FRAMELESS_QT_CONTEXT
#   include <private/qextFramelessContext_cocoa_p.h>
#else
#   include <private/qextFramelessContext_p.h>
#endif

Q_LOGGING_CATEGORY(qWindowKitLog, "qwindowkit")

/*!
        \class QExtFramelessAgent
        \brief QExtFramelessAgent is the base class of the specifiy window agent for QtWidgets and
        QtQuick.

        It processes some system events to remove the window's default title bar, and provides some
        shared methods for derived classes to call.
    */

QExtFramelessAgentPrivate::WindowContextFactoryMethod QExtFramelessAgentPrivate::windowContextFactoryMethod = QEXT_NULLPTR;

QExtFramelessAgentPrivate::QExtFramelessAgentPrivate(QExtFramelessAgent *q)
    : q_ptr(q)
    , m_context(QEXT_NULLPTR)
{
}

QExtFramelessAgentPrivate::~QExtFramelessAgentPrivate() = default;

void QExtFramelessAgentPrivate::init()
{
}

QExtAbstractFramelessContext *QExtFramelessAgentPrivate::createContext() const
{
    if (windowContextFactoryMethod)
    {
        return windowContextFactoryMethod();
    }

#if defined(Q_OS_WINDOWS) && !QEXT_FEATURE_USE_FRAMELESS_QT_CONTEXT
    return new Win32WindowContext();
#elif defined(Q_OS_MAC) && !QEXT_FEATURE_USE_FRAMELESS_QT_CONTEXT
    return new QExtCocoaFramelessContext();
#else
    return new QExtFramelessWindowContext();
#endif
}

void QExtFramelessAgentPrivate::setup(QObject *host, QExtFramelessItemDelegate *delegate)
{
    QExtAbstractFramelessContext *ctx = this->createContext();
    ctx->setup(host, delegate);
    m_context.reset(ctx);
}

/*!
        Destructor.
    */
QExtFramelessAgent::~QExtFramelessAgent()
{

}

/*!
        Returns the window attribute value.

        \sa setWindowAttribute()
    */
QVariant QExtFramelessAgent::windowAttribute(const QString &key) const
{
    Q_D(const QExtFramelessAgent);
    return d->m_context->windowAttribute(key);
}

/*!
        Sets the platform-related attribute for the window. Available attributes:

        On Windows,
            \li \c dwm-blur: Specify a boolean value to enable or disable dwm blur effect, this
                   attribute is available on Windows 10 or later.
            \li \c dark-mode: Specify a boolean value to enable or disable the dark mode, it is
                   enabled by default on Windows 10 if the system borders config is enabled. This
                   attribute is available on Windows 10 or later.
            \li \c acrylic-material: Specify a boolean value to enable or disable acrylic material,
                   this attribute is only available on Windows 11.
            \li \c mica: Specify a boolean value to enable or disable mica material,
                   this attribute is only available on Windows 11.
            \li \c mica-alt: Specify a boolean value to enable or disable mica-alt material,
                   this attribute is only available on Windows 11.
            \li \c extra-margins: Specify a margin value to change the \c dwm extended area
                   geometry, you shouldn't change this attribute because it may break the
                   internal state.

        On macOS,
            \li \c no-system-buttons: Specify a boolean value to set the system buttons'
                   visibility.
            \li \c blur-effect: You can specify a string value, "dark" to enable dark mode, "light"
                   to set enable mode, "none" to disable. You can also specify a boolean value,
                   \c true to enable current theme mode, \c false to disable.
            \li \c title-bar-height: Returns the system title bar height, the system button display
                   area will be limited to this height. (Readonly)
    */
bool QExtFramelessAgent::setWindowAttribute(const QString &key, const QVariant &attribute)
{
    Q_D(QExtFramelessAgent);
    return d->m_context->setWindowAttribute(key, attribute);
}

/*!
        Shows the system menu, it's only implemented on Windows.
    */
void QExtFramelessAgent::showSystemMenu(const QPoint &pos)
{
    Q_D(QExtFramelessAgent);
    d->m_context->showSystemMenu(pos);
}

/*!
        Makes the window show in center of the current screen.
    */
void QExtFramelessAgent::centralize()
{
    Q_D(QExtFramelessAgent);
    d->m_context->virtualHook(QExtAbstractFramelessContext::CentralizeHook, QEXT_NULLPTR);
}

/*!
        Brings the window to top.
    */
void QExtFramelessAgent::raise()
{
    Q_D(QExtFramelessAgent);
    d->m_context->virtualHook(QExtAbstractFramelessContext::RaiseWindowHook, QEXT_NULLPTR);
}

/*!
        \internal
    */
QExtFramelessAgent::QExtFramelessAgent(QExtFramelessAgentPrivate *d, QObject *parent)
    : QObject(parent)
    , dd_ptr(d)
{
    d->init();
}
