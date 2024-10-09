#include <qextWindowUtils.h>
#include <qextGuiConfig.h>

#include <QDebug>

#ifdef Q_OS_WIN
#   include <windows.h>
#else
#endif
#if QEXT_FEATURE_X11EXTRAS
#   include <QX11Info>
#   include <X11/Xatom.h>
#   include <X11/Xlib.h>
#endif

namespace detail
{
#if defined(Q_OS_WIN)
struct handle_data
{
    unsigned long process_id;
    HWND best_handle;
};

BOOL IsMainWindow(HWND handle)
{
    return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    handle_data &data = *(handle_data*)lParam;
    unsigned long process_id = 0;
    GetWindowThreadProcessId(handle, &process_id);
    if (data.process_id != process_id || !IsMainWindow(handle))
    {
        return TRUE;
    }
    data.best_handle = handle;
    return FALSE;
}
HWND FindMainWindow(unsigned long process_id)
{
    handle_data data;
    data.process_id = process_id;
    data.best_handle = 0;
    EnumWindows(EnumWindowsCallback, (LPARAM)&data);
    return data.best_handle;
}
#else
#   if QEXT_FEATURE_X11EXTRAS
void searchMainWindow(unsigned long pid, Display *display, Window wRoot, Atom atomPID, QList<Window> &result)
{
    // Get the PID for the current Window.
    Atom type;
    int format;
    unsigned long nItems;
    unsigned long bytesAfter;
    unsigned char *propPID = 0;
    if (Success == XGetWindowProperty(display, wRoot, atomPID, 0, 1, False,
                                      XA_CARDINAL, &type, &format, &nItems,
                                      &bytesAfter, &propPID))
    {
        if (propPID != 0)
        {
            // If the PID matches, add this window to the result set.
            if (*((unsigned long *)propPID) == pid)
            {
                XWindowAttributes attr;
                XGetWindowAttributes(display, wRoot, &attr);
                if (2 == attr.map_state)
                {
                    result.append(wRoot);
                }
            }
            XFree(propPID);
        }
    }

    // Recurse into child windows.
    Window wParent;
    Window wChildRoot;
    Window *wChild = NULL;
    unsigned nChildren = 0;
    if(0 != XQueryTree(display, wRoot, &wChildRoot, &wParent, &wChild, &nChildren))
    {
        for(unsigned i = 0; i < nChildren; i++)
        {
            searchMainWindow(pid, display, wChild[i], atomPID, result);
        }
    }
}

unsigned long FindMainWindow(unsigned long pid)
{
    QList<Window> result;
    unsigned long winId = 0;
    // Get the PID property atom.
    Display *display = XOpenDisplay(0);
    Window wRoot = XDefaultRootWindow(display);
    Atom atomPID = XInternAtom(display, "_NET_WM_PID", True);
    if (None != atomPID)
    {
        // Get the PID for the current Window.
        searchMainWindow(pid, display, wRoot, atomPID, result);
        if (!result.isEmpty())
        {
            qSort(result.begin(), result.end());
            winId = result.first();
        }
        XCloseDisplay(display);
    }
    return winId;
}
#   else

#   endif
#endif
}


QExtWindowUtils::QExtWindowUtils()
{

}

WId QExtWindowUtils::winIdFromProcessId(qint64 pid)
{
    return (WId)detail::FindMainWindow(pid);
}
