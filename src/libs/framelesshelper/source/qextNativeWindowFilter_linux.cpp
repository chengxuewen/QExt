#include <qextNativeWindowFilter.h>
#include <qextNativeWindowFilter_p.h>
#include <qextNativeWindowHelper_p.h>

#include <QCoreApplication>

#if defined(QEXT_OS_LINUX)

//#include <windows.h>
//#pragma comment (lib,"user32.lib")

void QEXTNativeWindowFilter::deliver(QWindow *window, QEXTNativeWindowHelper *helper)
{
    Q_CHECK_PTR(window);

    if (!QEXTNativeWindowFilterPrivate::instance) {
        QCoreApplication *appc = QCoreApplication::instance();
        if (appc) {
            QEXTNativeWindowFilter *filter = new QEXTNativeWindowFilter();
            QEXTNativeWindowFilterPrivate::instance.reset(filter);
            appc->installNativeEventFilter(filter);
        }
    }

    if (helper) {
        WId newId = window->winId();
        WId oldId = QEXTNativeWindowFilterPrivate::windows.value(helper);
        if (newId != oldId) {
            QEXTNativeWindowFilterPrivate::helpers.insert(newId, helper);
            QEXTNativeWindowFilterPrivate::helpers.remove(oldId);
            QEXTNativeWindowFilterPrivate::windows.insert(helper, newId);

            QEXTNativeWindowFilterPrivate::winIds.insert(window, newId);
        }
    } else {
        WId oldId = QEXTNativeWindowFilterPrivate::winIds.take(window);
        QEXTNativeWindowHelper *helper = QEXTNativeWindowFilterPrivate::helpers.take(oldId);
        QEXTNativeWindowFilterPrivate::windows.remove(helper);
    }
}

bool QEXTNativeWindowFilter::nativeEventFilter(const QByteArray &eventType,
                                               void *message, long *result)
{
    Q_UNUSED(eventType);

//    LPMSG msg = reinterpret_cast<LPMSG>(message);
//    if (auto h = QEXTNativeWindowFilterPrivate::helpers.value(reinterpret_cast<WId>(msg->hwnd)))
//        return h->nativeEventFilter(msg, result);

    return false;
}

// class QEXTNativeWindowFilterPrivate

QScopedPointer<QEXTNativeWindowFilter> QEXTNativeWindowFilterPrivate::instance;

QHash<QEXTNativeWindowHelper *, WId> QEXTNativeWindowFilterPrivate::windows;
QHash<QWindow *, WId> QEXTNativeWindowFilterPrivate::winIds;
QHash<WId, QEXTNativeWindowHelper *> QEXTNativeWindowFilterPrivate::helpers;

#endif // defined(QEXT_OS_LINUX)
