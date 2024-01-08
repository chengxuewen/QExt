#ifndef _QEXTQUICK_P_H
#define _QEXTQUICK_P_H

#include <qextQuick.h>

#include <QQmlEngine>
#include <QQuickWindow>
#include <QPointer>

class QExtQuickWorld;
class QEXT_QUICK_API QExtQuickPrivate
{
    QExtQuick * const q_ptr;
    Q_DECLARE_PUBLIC(QExtQuick)
    Q_DISABLE_COPY(QExtQuickPrivate)
public:
    explicit QExtQuickPrivate(QExtQuick *q);
    virtual ~QExtQuickPrivate();

    QPointer<QExtQuickWorld> m_quickWorld;
    QPointer<QQmlEngine> m_qmlEngine;
    QPointer<QQuickWindow> m_rootWindow;
    Qt::CursorShape m_mouseAreaCurrsor = Qt::ArrowCursor;
};

#endif // _QEXTQUICK_P_H
