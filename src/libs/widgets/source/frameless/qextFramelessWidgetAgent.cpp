// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#include <private/qextFramelessWidgetAgent_p.h>
#include <private/qextFramelessWidgetItemDelegate_p.h>

#include <QDebug>
#include <QtEvents>
#include <QPainter>

/*!
    \class WidgetWindowAgent
    \brief QExtFramelessAgent is the window agent for QtWidgets.

    It provides interfaces for QtWidgets and processes some Qt events related to the QWidget
    instance.
*/

WidgetWindowAgentPrivate::WidgetWindowAgentPrivate(WidgetWindowAgent *q)
    : QExtFramelessAgentPrivate(q)
    , hostWidget(QEXT_NULLPTR)
    , systemButtonAreaWidget(QEXT_NULLPTR)
{
}

WidgetWindowAgentPrivate::~WidgetWindowAgentPrivate()
{

}

void WidgetWindowAgentPrivate::init()
{
}

/*!
    Constructs a widget agent, it's better to set the widget to setup as \a parent.
*/
WidgetWindowAgent::WidgetWindowAgent(QObject *parent)
    : QExtFramelessAgent(new WidgetWindowAgentPrivate(this), parent)
{

}

/*!
    Destructor.
*/
WidgetWindowAgent::~WidgetWindowAgent()
{

}

/*!
    Installs the window agent on the widget. The window agent will take over some of the window
    events, making the window look frameless.
*/
bool WidgetWindowAgent::setup(QWidget *w)
{
    Q_ASSERT(w);
    if (!w)
    {
        return false;
    }

    Q_D(WidgetWindowAgent);
    if (d->hostWidget)
    {
        return false;
    }

    w->setAttribute(Qt::WA_DontCreateNativeAncestors);
    w->setAttribute(Qt::WA_NativeWindow);

    d->setup(w, new WidgetItemDelegate());
    d->hostWidget = w;

#if defined(Q_OS_WINDOWS) && QEXT_FEATURE_USE_FRAMELESS_SYSTEM_BORDERS
    d->setupWindows10BorderWorkaround();
#endif
    return true;
}

/*!
    Returns the title bar widget.
*/
QWidget *WidgetWindowAgent::titleBar() const
{
    Q_D(const WidgetWindowAgent);
    return static_cast<QWidget *>(d->m_context->titleBar());
}

/*!
    Sets the title bar widget, all system button and hit-test visible widget references that
    have been set will be removed.
*/
void WidgetWindowAgent::setTitleBar(QWidget *w)
{
    Q_D(WidgetWindowAgent);
    if (!d->m_context->setTitleBar(w))
    {
        return;
    }
#ifdef Q_OS_MAC
    this->setSystemButtonArea(QEXT_NULLPTR);
#endif
    Q_EMIT titleBarChanged(w);
}

/*!
    Returns the system button of the given type.
*/
QWidget *WidgetWindowAgent::systemButton(SystemButton button) const
{
    Q_D(const WidgetWindowAgent);
    return static_cast<QWidget *>(d->m_context->systemButton(button));
}

/*!
    Sets the system button of the given type, the system buttons always receive mouse events so
    you don't need to call \c setHitTestVisible for them.
*/
void WidgetWindowAgent::setSystemButton(SystemButton button, QWidget *w)
{
    Q_D(WidgetWindowAgent);
    if (!d->m_context->setSystemButton(button, w))
    {
        return;
    }
    Q_EMIT systemButtonChanged(button, w);
}

/*!
    Returns \a true if the widget can receive mouse events on title bar.
*/
bool WidgetWindowAgent::isHitTestVisible(const QWidget *w) const
{
    Q_D(const WidgetWindowAgent);
    return d->m_context->isHitTestVisible(w);
}

/*!
    Makes the widget able to receive mouse events on title bar if \a visible is \c true.
    You're supposed to make sure that the specified widget \a w is a child or descendant
    of the title bar widget.
*/
void WidgetWindowAgent::setHitTestVisible(const QWidget *w, bool visible)
{
    Q_D(WidgetWindowAgent);
    d->m_context->setHitTestVisible(w, visible);
}

/*!
    \internal
*/
WidgetWindowAgent::WidgetWindowAgent(WidgetWindowAgentPrivate *d, QObject *parent)
    : QExtFramelessAgent(d, parent)
{
    d->init();
}

/*!
    \fn void WidgetWindowAgent::titleBarChanged(const QWidget *w)

    This signal is emitted when the title bar widget is replaced.
*/

/*!
    \fn void WidgetWindowAgent::systemButtonChanged(SystemButton button, const QWidget *w)

    This signal is emitted when a system button is replaced.
*/
