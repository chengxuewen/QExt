// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#ifndef WIDGETWINDOWAGENTPRIVATE_H
#define WIDGETWINDOWAGENTPRIVATE_H

#include <qextFramelessWidgetAgent.h>
#include <private/qextFramelessAgent_p.h>

class WidgetWindowAgentPrivate : public QExtFramelessAgentPrivate
{
public:
    explicit WidgetWindowAgentPrivate(WidgetWindowAgent *q);
    ~WidgetWindowAgentPrivate() QEXT_OVERRIDE;

    void init();

    // Host
    QWidget *hostWidget;

#ifdef Q_OS_MAC
    QWidget *systemButtonAreaWidget;
    QScopedPointer<QObject> systemButtonAreaWidgetEventFilter;
#endif

#if defined(Q_OS_WINDOWS) && QEXT_FEATURE_USE_FRAMELESS_SYSTEM_BORDERS
    void setupWindows10BorderWorkaround();
    QScopedPointer<QObject> borderHandler;
#endif

private:
    Q_DECLARE_PUBLIC(WidgetWindowAgent)
    QEXT_DISABLE_COPY_MOVE(WidgetWindowAgentPrivate)
};

// }

#endif // WIDGETWINDOWAGENTPRIVATE_H
