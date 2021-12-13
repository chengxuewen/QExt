#ifndef _QEXTHOSTINFOUTILS_H
#define _QEXTHOSTINFOUTILS_H

#include <qextUtilsGlobal.h>
#include <qextDiskInfo.h>

#include <QObject>

class QEXTHostInfoUtilsPrivate;
class QEXT_UTILS_API QEXTHostInfoUtils : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTHostInfoUtils)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTHostInfoUtils)
public:
    enum HostArchType {
        HostArch_X86,
        HostArch_AMD64,
        HostArch_Itanium,
        HostArch_ARM,
        HostArch_Unknown
    };
    Q_ENUMS(HostArchType)

    enum HostOSType {
        HostOS_Win = 0,
        HostOS_Linux,
        HostOS_Mac,
        HostOS_Unix,
        HostOS_Unknown
    };
    Q_ENUMS(HostOSType)

    explicit QEXTHostInfoUtils(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTHostInfoUtils();

    static QString cpuID();
    static HostOSType hostOSType();
    static HostArchType hostArchType();

    static bool isWinSystem();
    static bool isLinuxSystem();
    static bool isMacSystem();
    static bool isAnyUnixSystem();

    static QString withExecutableSuffix(const QString &executable);
    static Qt::CaseSensitivity fileNameCaseSensitivity();
    static QChar pathListSeparator();
    static Qt::KeyboardModifier controlModifier();

    quint64 cpuPercent() const;
    quint64 memoryAll() const;
    quint64 memoryFree() const;
    quint64 memoryUsed() const;
    quint64 memoryPercent() const;

public Q_SLOTS:
    void startQueryCPU(int interval);
    void stopQueryCPU();
    void queryCPUInfo();
    void readCPUProcessData();

    void startQueryMemory(int interval);
    void stopQueryMemory();
    void queryMemoryInfo();
    void readMemoryProcessData();

    void startQueryDisk(int interval);
    void stopQueryDisk();
    void queryDiskInfo();
    void readDiskProcessData();

Q_SIGNALS:
    void cpuChanged(quint64 percent);
    void memoryChanged(quint64 percent);
    void memoryChanged(quint64 free, quint64 all);
    void memoryChanged(quint64 free, quint64 all, quint64 percent);
    void diskChanged(const QList<QEXTDiskInfo> &diskInfoList);

protected:
    QScopedPointer<QEXTHostInfoUtilsPrivate> dd_ptr;
};

#endif // _QEXTHOSTINFOUTILS_H
