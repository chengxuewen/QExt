#ifndef _QEXTHOSTINFOUTILS_P_H
#define _QEXTHOSTINFOUTILS_P_H

#include <qextUtilsGlobal.h>
#include <qextDiskInfo.h>

#include <QProcess>
#include <QTimer>

class QEXTHostInfoUtils;
class QEXT_UTILS_API QEXTHostInfoUtilsPrivate
{
public:
    explicit QEXTHostInfoUtilsPrivate(QEXTHostInfoUtils *q);
    virtual ~QEXTHostInfoUtilsPrivate();

    QEXTHostInfoUtils * const q_ptr;

    QEXTDiskInfo checkDiskSize(const QString &result, const QString &name);

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
    QEXT_DECL_DISABLE_COPY(QEXTHostInfoUtilsPrivate)
    Q_DECLARE_PUBLIC(QEXTHostInfoUtils)
};


#endif // _QEXTHOSTINFOUTILS_P_H
