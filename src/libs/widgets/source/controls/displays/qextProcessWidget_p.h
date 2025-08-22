#ifndef _QEXTPROCESSWIDGET_P_H
#define _QEXTPROCESSWIDGET_P_H

#include <qextProcessWidget.h>

#include <QProcess>
#include <QTimer>

class QEXT_WIDGETS_API QExtProcessWidgetPrivate
{
public:
    explicit QExtProcessWidgetPrivate(QExtProcessWidget *q);
    virtual ~QExtProcessWidgetPrivate();

    QTimer *timer();
    QProcess *process();

    QExtProcessWidget * const q_ptr;

    QString m_processPath;
    QString m_workingPath;
    QStringList m_processArgs;
    QScopedPointer<QTimer> m_timer;
    QScopedPointer<QProcess> m_process;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtProcessWidgetPrivate)
    QEXT_DECLARE_PUBLIC(QExtProcessWidget)
};

#endif // _QEXTPROCESSWIDGET_P_H
