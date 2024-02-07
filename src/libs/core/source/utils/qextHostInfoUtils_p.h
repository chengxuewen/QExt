#ifndef _QEXTHOSTINFOUTILS_P_H
#define _QEXTHOSTINFOUTILS_P_H

#include <qextDiskInfo.h>

#include <QProcess>
#include <QTimer>

class QExtHostInfoUtils;
class QEXT_CORE_API QExtHostInfoUtilsPrivate
{
public:
    explicit QExtHostInfoUtilsPrivate(QExtHostInfoUtils *q);
    virtual ~QExtHostInfoUtilsPrivate();

    QExtHostInfoUtils * const q_ptr;

    QExtDiskInfo checkDiskSize(const QString &result, const QString &name);

    QScopedPointer<QTimer> m_cpuTimer;
    QScopedPointer<QProcess> m_cpuProcess;
    quint64 m_cpuTotalNew;
    quint64 m_cpuTotalOld;
    quint64 m_cpuTotalCurrent;
    quint64 m_cpuIdleNew;
    quint64 m_cpuIdleOld;
    quint64 m_cpuIdleCurrent;
    quint64 m_cpuPercent;

    QScopedPointer<QTimer> m_memoryTimer;
    QScopedPointer<QProcess> m_memoryProcess;
    quint64 m_memoryPercent;
    quint64 m_memoryAll;
    quint64 m_memoryUse;
    quint64 m_memoryFree;

    QScopedPointer<QTimer> m_diskTimer;
    QScopedPointer<QProcess> m_diskProcess;

private:
    Q_DISABLE_COPY(QExtHostInfoUtilsPrivate)
    Q_DECLARE_PUBLIC(QExtHostInfoUtils)
};


#endif // _QEXTHOSTINFOUTILS_P_H
