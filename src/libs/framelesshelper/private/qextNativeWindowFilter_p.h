#ifndef _QEXTNATIVEWINDOWFILTER_P_H
#define _QEXTNATIVEWINDOWFILTER_P_H

#include <qextFramelessHelperGlobal.h>
#include <qextNativeWindowFilter.h>

#include <QHash>
#include <QWindow>

class QEXT_FRAMELESSHELPER_API QEXTNativeWindowFilterPrivate
{
public:
    static QScopedPointer<QEXTNativeWindowFilter> instance;

    static QHash<QEXTNativeWindowHelper *, WId> windows;
    static QHash<QWindow *, WId> winIds;
    static QHash<WId, QEXTNativeWindowHelper *> helpers;
};

#endif // _QEXTNATIVEWINDOWFILTER_P_H
