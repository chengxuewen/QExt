#ifndef _QEXTNATIVEWINDOWHELPER_H
#define _QEXTNATIVEWINDOWHELPER_H

#include <qextFramelessHelperGlobal.h>

#include <QPoint>
#include <QWindow>
#include <QMargins>

class QEXTNativeWindowTester;
class QEXTNativeWindowHelperPrivate;
class QEXT_FRAMELESSHELPER_API QEXTNativeWindowHelper : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTNativeWindowHelper)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTNativeWindowHelper)

public:
    QEXTNativeWindowHelper(QWindow *window, QEXTNativeWindowTester *tester);
    explicit QEXTNativeWindowHelper(QWindow *window);
    ~QEXTNativeWindowHelper();

    qreal scaleFactor() const;

    bool nativeEventFilter(void *msg, long *result);

signals:
    void scaleFactorChanged(qreal factor);

protected:
    bool eventFilter(QObject *obj, QEvent *ev) final;

    QScopedPointer<QEXTNativeWindowHelperPrivate> dd_ptr;
};

#endif // _QEXTNATIVEWINDOWHELPER_H
