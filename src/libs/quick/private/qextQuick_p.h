#ifndef _QEXTQUICK_P_H
#define _QEXTQUICK_P_H

#include <qextQuickGlobal.h>
#include <qextQuickWorld.h>

#include <QQmlEngine>
#include <QQuickWindow>
#include <QPointer>

class QEXTQuick;
class QEXT_QUICK_API QEXTQuickPrivate
{
    Q_DISABLE_COPY(QEXTQuickPrivate)
    Q_DECLARE_PUBLIC(QEXTQuick)
public:
    explicit QEXTQuickPrivate(QEXTQuick *q);
    virtual ~QEXTQuickPrivate();

    QEXTQuick * const q_ptr;

    QPointer<QEXTQuickWorld> m_quickWorld;
    QPointer<QQmlEngine> m_qmlEngine;
    QPointer<QQuickWindow> m_rootWindow;
    Qt::CursorShape m_mouseAreaCurrsor;
};

#endif // _QEXTQUICK_P_H
