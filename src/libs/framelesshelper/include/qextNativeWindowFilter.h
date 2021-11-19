#ifndef _QEXTNATIVEWINDOWFILTER_H
#define _QEXTNATIVEWINDOWFILTER_H

#include <qextFramelessHelperGlobal.h>

#include <QAbstractNativeEventFilter>

class QWindow;

class QEXTNativeWindowHelper;
class QEXT_FRAMELESSHELPER_API QEXTNativeWindowFilter : public QAbstractNativeEventFilter
{
public:
    static void deliver(QWindow *window, QEXTNativeWindowHelper *helper);

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) final;
};

#endif // _QEXTNATIVEWINDOWFILTER_H
