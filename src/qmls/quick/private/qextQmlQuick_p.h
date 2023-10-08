#ifndef _QEXTQMLQUICK_P_H
#define _QEXTQMLQUICK_P_H

#include <qextQmlQuickGlobal.h>

#include <QQmlEngine>
#include <QQuickWindow>
#include <QPointer>

class QEXTQmlQuickWorld;
class QEXTQmlQuick;
class QEXT_QUICK_API QEXTQmlQuickPrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuick)
public:
    explicit QEXTQmlQuickPrivate(QEXTQmlQuick *q);
    virtual ~QEXTQmlQuickPrivate();

    QEXTQmlQuick * const q_ptr;

    QPointer<QEXTQmlQuickWorld> m_quickWorld;
    QPointer<QQmlEngine> m_qmlEngine;
    QPointer<QQuickWindow> m_rootWindow;
    Qt::CursorShape m_mouseAreaCurrsor = Qt::ArrowCursor;

private:
};



#endif // _QEXTQMLQUICK_P_H
