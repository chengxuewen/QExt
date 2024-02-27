// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#ifndef WIN32WINDOWCONTEXT_P_H
#define WIN32WINDOWCONTEXT_P_H

//
//  W A R N I N G !!!
//  -----------------
//
// This file is not part of the QWindowKit API. It is used purely as an
// implementation detail. This header file may change from version to
// version without notice, or may even be removed.
//

#include "../qwindowkit_windows.h"
#include "../contexts/abstractwindowcontext_p.h"

// namespace QWK
// {

class Win32WindowContext : public QExtAbstractFramelessContext
{
    Q_OBJECT
public:
    Win32WindowContext();
    ~Win32WindowContext() QEXT_OVERRIDE;

    enum WindowPart
    {
        Outside,
        ClientArea,
        ChromeButton,
        ResizeBorder,
        FixedBorder,
        TitleBar,
    };

    QString key() const QEXT_OVERRIDE;
    void virtualHook(int id, void *data) QEXT_OVERRIDE;

    QVariant windowAttribute(const QString &key) const QEXT_OVERRIDE;

protected:
    void winIdChanged() QEXT_OVERRIDE;
    bool windowAttributeChanged(const QString &key, const QVariant &attribute,
                                const QVariant &oldAttribute) QEXT_OVERRIDE;

public:
    bool windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT *result);

    bool systemMenuHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam,
                           LRESULT *result);

    // In order to perfectly apply Windows 11 Snap Layout into the Qt window, we need to
    // intercept and emulate most of the  mouse events, so that the processing logic
    // is quite complex. Simultaneously, in order to make the handling code of other
    // Windows messages clearer, we have separated them into this function.
    bool snapLayoutHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam,
                           LRESULT *result);

    bool customWindowHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam,
                             LRESULT *result);

    bool nonClientCalcSizeHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam,
                                  LRESULT *result);

protected:
    WId windowId = 0;

    // The last hit test result, helpful to handle WM_MOUSEMOVE and WM_NCMOUSELEAVE.
    WindowPart lastHitTestResult = WindowPart::Outside;

    // Whether the last mouse leave message is blocked, mainly for handling the unexpected
    // WM_MOUSELEAVE.
    bool mouseLeaveBlocked = false;

    bool initialCentered = false;
};
// }

#endif // WIN32WINDOWCONTEXT_P_H
