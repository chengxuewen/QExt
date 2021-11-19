#include <qextNativeWindowHelper.h>
#include <qextNativeWindowHelper_p.h>
#include <qextNativeWindowFilter.h>
#include <qextNativeWindowTester.h>

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#pragma comment (lib,"user32.lib")

#include <QScreen>
#include <QEvent>
#include <QOperatingSystemVersion>

#if defined(__GNUC__)
//我电脑上的mingw报错，说没定义，那咋就给它定义一个
//make mingw happy
#define WM_DPICHANGED       0x02E0
#endif

QEXTNativeWindowHelperPrivate::QEXTNativeWindowHelperPrivate(QEXTNativeWindowHelper *q)
    : q_ptr(q)
    , m_window(nullptr)
    , m_tester(nullptr)
    , m_oldWindow(NULL)
    , m_scaleFactor(1.0)
{
}

QEXTNativeWindowHelperPrivate::~QEXTNativeWindowHelperPrivate()
{
    if (m_window)
        QEXTNativeWindowFilter::deliver(m_window, nullptr);
}

void QEXTNativeWindowHelperPrivate::updateWindowStyle()
{
    Q_Q(QEXTNativeWindowHelper);

    Q_CHECK_PTR(m_window);

    HWND hWnd = reinterpret_cast<HWND>(m_window->winId());
    if (NULL == hWnd)
        return;
    else if (m_oldWindow == hWnd) {
        return;
    }
    m_oldWindow = hWnd;

    QEXTNativeWindowFilter::deliver(m_window, q);

    QOperatingSystemVersion currentVersion = QOperatingSystemVersion::current();
    if (currentVersion < QOperatingSystemVersion::Windows8) {
        return;
    }

    LONG oldStyle = WS_OVERLAPPEDWINDOW | WS_THICKFRAME
            | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;;
    LONG newStyle = WS_POPUP            | WS_THICKFRAME;

    //    if (QtWin::isCompositionEnabled())
    //        newStyle |= WS_CAPTION;

    if (m_window->flags() & Qt::CustomizeWindowHint) {
        if (m_window->flags() & Qt::WindowSystemMenuHint)
            newStyle |= WS_SYSMENU;
        if (m_window->flags() & Qt::WindowMinimizeButtonHint)
            newStyle |= WS_MINIMIZEBOX;
        if (m_window->flags() & Qt::WindowMaximizeButtonHint)
            newStyle |= WS_MAXIMIZEBOX;
    } else {
        newStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    }

    LONG currentStyle = GetWindowLong(hWnd, GWL_STYLE);
    SetWindowLong(hWnd, GWL_STYLE, (currentStyle & ~oldStyle) | newStyle);

    SetWindowPos(hWnd, NULL, 0, 0, 0 , 0,
                 SWP_NOOWNERZORDER | SWP_NOZORDER |
                 SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

    //    if (QtWin::isCompositionEnabled())
    //        QtWin::extendFrameIntoClientArea(window, 1, 1, 1, 1);
}

int QEXTNativeWindowHelperPrivate::hitTest(int x, int y) const
{
    Q_CHECK_PTR(m_window);

    x = x / m_window->devicePixelRatio();
    y = y / m_window->devicePixelRatio();

    enum RegionMask {
        Client = 0x0000,
        Top    = 0x0001,
        Left   = 0x0010,
        Right  = 0x0100,
        Bottom = 0x1000,
    };

    auto wfg = m_window->frameGeometry();
    QMargins draggableMargins
            = this->draggableMargins();

    int top = draggableMargins.top();
    int left = draggableMargins.left();
    int right = draggableMargins.right();
    int bottom = draggableMargins.bottom();

    if (top <= 0)
        top = GetSystemMetrics(SM_CYFRAME);
    if (left <= 0)
        left = GetSystemMetrics(SM_CXFRAME);
    if (right <= 0)
        right = GetSystemMetrics(SM_CXFRAME);
    if (bottom <= 0)
        bottom = GetSystemMetrics(SM_CYFRAME);

    auto result =
            (Top *    (y < (wfg.top() +    top))) |
            (Left *   (x < (wfg.left() +   left))) |
            (Right *  (x > (wfg.right() -  right))) |
            (Bottom * (y > (wfg.bottom() - bottom)));

    bool wResizable = m_window->minimumWidth() < m_window->maximumWidth();
    bool hResizable = m_window->minimumHeight() < m_window->maximumHeight();

    switch (result) {
    case Top | Left    : return wResizable && hResizable ? HTTOPLEFT     : HTCLIENT;
    case Top           : return hResizable               ? HTTOP         : HTCLIENT;
    case Top | Right   : return wResizable && hResizable ? HTTOPRIGHT    : HTCLIENT;
    case Right         : return wResizable               ? HTRIGHT       : HTCLIENT;
    case Bottom | Right: return wResizable && hResizable ? HTBOTTOMRIGHT : HTCLIENT;
    case Bottom        : return hResizable               ? HTBOTTOM      : HTCLIENT;
    case Bottom | Left : return wResizable && hResizable ? HTBOTTOMLEFT  : HTCLIENT;
    case Left          : return wResizable               ? HTLEFT        : HTCLIENT;
    }

    auto pos = m_window->mapFromGlobal(QPoint(x, y));
    return ((nullptr != m_tester) && !m_tester->hitTest(pos)) ? HTCLIENT : HTCAPTION;
}

bool QEXTNativeWindowHelperPrivate::isMaximized() const
{
    Q_CHECK_PTR(m_window);

    HWND hWnd = reinterpret_cast<HWND>(m_window->winId());
    if (NULL == hWnd)
        return false;

    WINDOWPLACEMENT windowPlacement;
    if (!GetWindowPlacement(hWnd, &windowPlacement))
        return false;

    return (SW_MAXIMIZE == windowPlacement.showCmd);
}

QMargins QEXTNativeWindowHelperPrivate::draggableMargins() const
{
    return m_tester ? m_tester->draggableMargins() * m_scaleFactor : QMargins();
}

QMargins QEXTNativeWindowHelperPrivate::maximizedMargins() const
{
    return m_tester ? m_tester->maximizedMargins() * m_scaleFactor : QMargins();
}

QRect QEXTNativeWindowHelperPrivate::availableGeometry() const
{
    MONITORINFO mi{0};
    mi.cbSize = sizeof(MONITORINFO);

    auto hWnd = reinterpret_cast<HWND>(m_window->winId());
    auto hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    if (!hMonitor || !GetMonitorInfoW(hMonitor, &mi)) {
        Q_ASSERT(NULL != hMonitor);
        return m_window->screen()->availableGeometry();
    }

    return QRect(mi.rcWork.left, mi.rcWork.top, mi.rcWork.right - mi.rcWork.left, mi.rcWork.bottom - mi.rcWork.top);
}




QEXTNativeWindowHelper::QEXTNativeWindowHelper(QWindow *window, QEXTNativeWindowTester *tester)
    : QObject(window)
    , d_ptr(new QEXTNativeWindowHelperPrivate(this))
{
    Q_D(QEXTNativeWindowHelper);
    Q_CHECK_PTR(window);
    Q_CHECK_PTR(tester);

    d->m_window = window;
    d->m_tester = tester;

    if (d->m_window) {
        d->m_scaleFactor = d->m_window->screen()->devicePixelRatio();

        if (d->m_window->flags() & Qt::FramelessWindowHint) {
            d->m_window->installEventFilter(this);
            d->updateWindowStyle();
        }
    }
}

QEXTNativeWindowHelper::QEXTNativeWindowHelper(QWindow *window)
    : QObject(window)
    , d_ptr(new QEXTNativeWindowHelperPrivate(this))
{
    Q_D(QEXTNativeWindowHelper);
    Q_CHECK_PTR(window);
    d->m_window = window;

    if (d->m_window) {
        d->m_scaleFactor = d->m_window->screen()->devicePixelRatio();

        if (d->m_window->flags() & Qt::FramelessWindowHint) {
            d->m_window->installEventFilter(this);
            d->updateWindowStyle();
        }
    }
}

QEXTNativeWindowHelper::~QEXTNativeWindowHelper()
{
}

bool QEXTNativeWindowHelper::nativeEventFilter(void *msg, long *result)
{
    Q_D(QEXTNativeWindowHelper);
    Q_CHECK_PTR(d->m_window);

    LPMSG lpMsg = reinterpret_cast<LPMSG>(msg);
    WPARAM wParam = lpMsg->wParam;
    LPARAM lParam = lpMsg->lParam;

    if (WM_NCHITTEST == lpMsg->message) {
        *result = d->hitTest(GET_X_LPARAM(lParam),
                             GET_Y_LPARAM(lParam));
        return true;
    } else if (WM_NCACTIVATE == lpMsg->message) {
        //        if (!QtWin::isCompositionEnabled()) {
        //            if (result) *result = 1;
        //            return true;
        //        }
    } else if (WM_NCCALCSIZE == lpMsg->message) {
        if (TRUE == wParam) {
            if (d->isMaximized()) {
                NCCALCSIZE_PARAMS &params = *reinterpret_cast<NCCALCSIZE_PARAMS *>(lParam);

                QRect g = d->availableGeometry();
                QMargins m = d->maximizedMargins();

                params.rgrc[0].top = g.top() - m.top();
                params.rgrc[0].left = g.left() - m.left();
                params.rgrc[0].right = g.right() + m.right() + 1;
                params.rgrc[0].bottom = g.bottom() + m.bottom() + 1;
            }

            if (result) *result = 0;
            return true;
        }
    } else if (WM_GETMINMAXINFO == lpMsg->message) {
        LPMINMAXINFO lpMinMaxInfo = reinterpret_cast<LPMINMAXINFO>(lParam);

        QRect g = d->availableGeometry();
        QMargins m = d->maximizedMargins();

        lpMinMaxInfo->ptMaxPosition.x = - m.left();
        lpMinMaxInfo->ptMaxPosition.y =  - m.top();
        lpMinMaxInfo->ptMaxSize.x = g.right() - g.left() + 1 + m.left() + m.right();
        lpMinMaxInfo->ptMaxSize.y = g.bottom() - g.top() + 1 + m.top() + m.bottom();

        lpMinMaxInfo->ptMinTrackSize.x = d->m_window->minimumWidth();
        lpMinMaxInfo->ptMinTrackSize.y = d->m_window->minimumHeight();
        lpMinMaxInfo->ptMaxTrackSize.x = d->m_window->maximumWidth();
        lpMinMaxInfo->ptMaxTrackSize.y = d->m_window->maximumHeight();

        if (result) *result = 0;
        return true;
    } else if (WM_NCLBUTTONDBLCLK == lpMsg->message) {
        auto minimumSize = d->m_window->minimumSize();
        auto maximumSize = d->m_window->maximumSize();
        if ((minimumSize.width() >= maximumSize.width())
                || (minimumSize.height() >= maximumSize.height())) {
            if (result) *result = 0;
            return true;
        }
    } else if (WM_DPICHANGED == lpMsg->message) {
        qreal old = d->m_scaleFactor;
        if (HIWORD(wParam) < 144) {
            d->m_scaleFactor = 1.0;
        } else {
            d->m_scaleFactor = 2.0;
        }

        if (!qFuzzyCompare(old, d->m_scaleFactor)) {
            emit scaleFactorChanged(d->m_scaleFactor);
        }

        auto hWnd = reinterpret_cast<HWND>(d->m_window->winId());
        auto rect = reinterpret_cast<LPRECT>(lParam);
        SetWindowPos(hWnd,
                     NULL,
                     rect->left,
                     rect->top,
                     rect->right - rect->left,
                     rect->bottom - rect->top,
                     SWP_NOZORDER | SWP_NOACTIVATE);
    }

    return false;
}

bool QEXTNativeWindowHelper::eventFilter(QObject *obj, QEvent *ev)
{
    Q_D(QEXTNativeWindowHelper);
    if (ev->type() == QEvent::WinIdChange) {
        d->updateWindowStyle();
    } else if (ev->type() == QEvent::Show) {
        d->updateWindowStyle();
    }

    return QObject::eventFilter(obj, ev);
}

qreal QEXTNativeWindowHelper::scaleFactor() const
{
    Q_D(const QEXTNativeWindowHelper);
    return d->m_scaleFactor;
}
