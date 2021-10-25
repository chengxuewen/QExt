#ifndef _QEXTQUICK_P_H
#define _QEXTQUICK_P_H

#include <qextquickglobal.h>

#include <qextObject_p.h>

#include <QQmlEngine>
#include <QQuickWindow>
#include <QPointer>



class QEXTQuickWorld;
class QEXTQuick;
class QEXT_QUICK_API QEXTQuickPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTQuickPrivate(QEXTQuick *qq);
    ~QEXTQuickPrivate();

    QPointer<QEXTQuickWorld> m_quickWorld;
    QPointer<QQmlEngine> m_qmlEngine;
    QPointer<QQuickWindow> m_rootWindow;
    Qt::CursorShape m_mouseAreaCurrsor = Qt::ArrowCursor;

private:
    QEXT_DECL_PUBLIC(QEXTQuick)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickPrivate)
};



#endif // _QEXTQUICK_P_H
