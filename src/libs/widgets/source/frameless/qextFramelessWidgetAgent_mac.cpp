// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#include <private/qextFramelessWidgetAgent_p.h>

#include <QtGui/QtEvents>

struct QExtWidgetScreenRectCallbacker : public QExtScreenRectCallbackInterface
{
    QExtWidgetScreenRectCallbacker(QWidget *w) : widget(w) {}
    QRect screenRect(const QSize &) QEXT_OVERRIDE
    {
        return widget ? QRect(widget->mapTo(widget->window(), QPoint()), widget->size())
                      : QRect();
    }
    QWidget *widget;
};

class SystemButtonAreaWidgetEventFilter : public QObject
{
public:
    SystemButtonAreaWidgetEventFilter(QWidget *widget, QExtAbstractFramelessContext *ctx,
                                      QObject *parent = QEXT_NULLPTR)
        : QObject(parent), widget(widget), ctx(ctx)
    {
        widget->installEventFilter(this);
        ctx->setSystemButtonAreaCallback(new QExtWidgetScreenRectCallbacker(widget));
    }
    ~SystemButtonAreaWidgetEventFilter() QEXT_OVERRIDE = default;

protected:
    bool eventFilter(QObject *obj, QEvent *event) QEXT_OVERRIDE
    {
        Q_UNUSED(obj)
        switch (event->type())
        {
        case QEvent::Move:
        case QEvent::Resize:
        {
            ctx->virtualHook(QExtAbstractFramelessContext::SystemButtonAreaChangedHook, QEXT_NULLPTR);
            break;
        }

        default:
            break;
        }
        return false;
    }

protected:
    QWidget *widget;
    QExtAbstractFramelessContext *ctx;
};

/*!
    Returns the widget that acts as the system button area.
*/
QWidget *WidgetWindowAgent::systemButtonArea() const
{
    Q_D(const WidgetWindowAgent);
    return d->systemButtonAreaWidget;
}

/*!
    Sets the widget that acts as the system button area. The system button will be centered in
    its area, it is recommended to place the widget in a layout and set a fixed size policy.

    The system button will be visible in the system title bar area.
*/
void WidgetWindowAgent::setSystemButtonArea(QWidget *widget)
{
    Q_D(WidgetWindowAgent);
    if (d->systemButtonAreaWidget == widget)
    {
        return;
    }

    QExtAbstractFramelessContext *ctx = d->m_context.get();
    d->systemButtonAreaWidget = widget;
    if (!widget)
    {
        d->m_context->setSystemButtonAreaCallback({ });
        d->systemButtonAreaWidgetEventFilter.reset();
        return;
    }
    d->systemButtonAreaWidgetEventFilter.reset(new SystemButtonAreaWidgetEventFilter(widget, ctx));
}

/*!
    Returns the the system button area callback.
*/
QExtScreenRectCallbackInterface *WidgetWindowAgent::systemButtonAreaCallback() const
{
    Q_D(const WidgetWindowAgent);
    return d->systemButtonAreaWidget ? QEXT_NULLPTR : d->m_context->systemButtonAreaCallback();
}

/*!
    Sets the the system button area callback, the \c size of the callback is the native title
    bar size.

    The system button position will be updated when the window resizes.
*/
void WidgetWindowAgent::setSystemButtonAreaCallback(QExtScreenRectCallbackInterface *callback)
{
    Q_D(WidgetWindowAgent);
    this->setSystemButtonArea(QEXT_NULLPTR);
    d->m_context->setSystemButtonAreaCallback(callback);
}

// }
