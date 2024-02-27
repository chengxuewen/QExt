// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#ifndef WIDGETITEMDELEGATE_P_H
#define WIDGETITEMDELEGATE_P_H

#include <qextWidgetGlobal.h>
#include <private/qextFramelessItemDelegate_p.h>

#include <QtCore/QObject>
#include <QtGui/QWindow>

class QEXT_WIDGETS_API WidgetItemDelegate : public QExtFramelessItemDelegate
{
public:
    WidgetItemDelegate();
    ~WidgetItemDelegate() QEXT_OVERRIDE;

public:
    QWindow *window(const QObject *obj) const QEXT_OVERRIDE;
    bool isEnabled(const QObject *obj) const QEXT_OVERRIDE;
    bool isVisible(const QObject *obj) const QEXT_OVERRIDE;
    QRect mapGeometryToScene(const QObject *obj) const QEXT_OVERRIDE;

    QWindow *hostWindow(const QObject *host) const QEXT_OVERRIDE;
    bool isHostSizeFixed(const QObject *host) const QEXT_OVERRIDE;
    bool isWindowActive(const QObject *host) const QEXT_OVERRIDE;
    Qt::WindowStates getWindowState(const QObject *host) const QEXT_OVERRIDE;
    Qt::WindowFlags getWindowFlags(const QObject *host) const QEXT_OVERRIDE;

    void resetQtGrabbedControl(QObject *host) const QEXT_OVERRIDE;
    void setWindowState(QObject *host, Qt::WindowStates state) const QEXT_OVERRIDE;
    void setCursorShape(QObject *host, Qt::CursorShape shape) const QEXT_OVERRIDE;
    void restoreCursorShape(QObject *host) const QEXT_OVERRIDE;
    void setWindowFlags(QObject *host, Qt::WindowFlags flags) const QEXT_OVERRIDE;
    void setWindowVisible(QObject *host, bool visible) const QEXT_OVERRIDE;
    void bringWindowToTop(QObject *host) const QEXT_OVERRIDE;
};

#endif // WIDGETITEMDELEGATE_P_H
