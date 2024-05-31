#ifndef _QEXTQML_P_H
#define _QEXTQML_P_H

#include <qextQml.h>

#include <QQmlEngine>
#include <QQuickWindow>
#include <QPointer>

class QExtQmlWorld;
class QEXT_QML_API QExtQmlPrivate
{
    QExtQml * const q_ptr;
    Q_DECLARE_PUBLIC(QExtQml)
    Q_DISABLE_COPY(QExtQmlPrivate)
public:
    explicit QExtQmlPrivate(QExtQml *q);
    virtual ~QExtQmlPrivate();

    QPointer<QExtQmlWorld> m_quickWorld;
    QPointer<QQmlEngine> m_qmlEngine;
    QPointer<QQuickWindow> m_rootWindow;
    Qt::CursorShape m_mouseAreaCurrsor = Qt::ArrowCursor;
};

#endif // _QEXTQML_P_H
