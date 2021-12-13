#ifndef _QEXTNATIVEWINDOWHELPER_P_H
#define _QEXTNATIVEWINDOWHELPER_P_H

#include <qextFramelessHelperGlobal.h>
#include <qextNativeWindowHelper.h>

#include <QPointer>

class QEXTNativeWindowHelper;
class QEXT_FRAMELESSHELPER_API QEXTNativeWindowHelperPrivate
{
    Q_DECLARE_PUBLIC(QEXTNativeWindowHelper)
    Q_DISABLE_COPY(QEXTNativeWindowHelperPrivate)

public:
    explicit QEXTNativeWindowHelperPrivate(QEXTNativeWindowHelper *q);
    virtual ~QEXTNativeWindowHelperPrivate();

    void updateWindowStyle();
    int hitTest(int x, int y) const;
    bool isMaximized() const;

    QMargins draggableMargins() const;
    QMargins maximizedMargins() const;

    QRect availableGeometry() const;

    QEXTNativeWindowHelper * const q_ptr;

    QWindow *m_window;
    QEXTNativeWindowTester *m_tester;
    qreal m_scaleFactor;

#if defined(QEXT_OS_WIN32)
    HWND m_oldWindow;
#endif // defined(QEXT_OS_WIN32)
};

#endif // _QEXTNATIVEWINDOWHELPER_P_H
