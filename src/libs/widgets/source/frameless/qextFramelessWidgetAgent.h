// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#ifndef WIDGETWINDOWAGENT_H
#define WIDGETWINDOWAGENT_H

#include <QWidget>
#include <QScopedPointer>

#include <qextWidgetGlobal.h>
#include <qextFramelessAgent.h>

class WidgetWindowAgentPrivate;
class QEXT_WIDGETS_API WidgetWindowAgent : public QExtFramelessAgent
{
    Q_OBJECT
public:
    explicit WidgetWindowAgent(QObject *parent = QEXT_NULLPTR);
    ~WidgetWindowAgent() QEXT_OVERRIDE;

public:
    bool setup(QWidget *w);

    QWidget *titleBar() const;
    void setTitleBar(QWidget *w);

    QWidget *systemButton(SystemButton button) const;
    void setSystemButton(SystemButton button, QWidget *w);

#ifdef Q_OS_MAC
    // The system button area APIs are experimental, very likely to change in the future.
    QWidget *systemButtonArea() const;
    void setSystemButtonArea(QWidget *widget);

    QExtScreenRectCallbackInterface *systemButtonAreaCallback() const;
    void setSystemButtonAreaCallback(QExtScreenRectCallbackInterface *callback);
#endif

    bool isHitTestVisible(const QWidget *w) const;
    void setHitTestVisible(const QWidget *w, bool visible = true);

Q_SIGNALS:
    void titleBarChanged(const QWidget *w);
    void systemButtonChanged(SystemButton button, const QWidget *w);

protected:
    WidgetWindowAgent(WidgetWindowAgentPrivate *d, QObject *parent = QEXT_NULLPTR);

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, WidgetWindowAgent)
    QEXT_DISABLE_COPY_MOVE(WidgetWindowAgent)
};

#endif // WIDGETWINDOWAGENT_H
