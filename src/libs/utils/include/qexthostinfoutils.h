#ifndef QEXTHOSTINFOUTILS_H
#define QEXTHOSTINFOUTILS_H

#include <qextglobal.h>

#include <qextutilsglobal.h>
#include <qextdiskinfoutils.h>

#include <QObject>

class QEXTHostInfoUtilsPrivate;
class QEXT_UTILS_API QEXTHostInfoUtils : public QObject
{
    Q_OBJECT

public:
    enum HostArchitecture {
        HostArchitecture_X86,
        HostArchitecture_AMD64,
        HostArchitecture_Itanium,
        HostArchitecture_Arm,
        HostArchitecture_Unknown
    };
    enum OsType {
        OsTypeWindows = 0,
        OsTypeLinux,
        OsTypeMac,
        OsTypeOtherUnix,
        OsTypeOther
    };

    explicit QEXTHostInfoUtils(QObject *parent = QEXT_NULLPTR);
    ~QEXTHostInfoUtils();

    static QString getCPUID();
    static OsType hostOs();
    static HostArchitecture hostArchitecture();

    static bool isWindowsHost();
    static bool isLinuxHost();
    static bool isMacHost();
    static bool isAnyUnixHost();

    static QString withExecutableSuffix(const QString &executable);
    static Qt::CaseSensitivity fileNameCaseSensitivity();
    static QChar pathListSeparator();
    static Qt::KeyboardModifier controlModifier();

    quint64 getCPUPercent() const;
    quint64 getMemoryAll() const;
    quint64 getMemoryFree() const;
    quint64 getMemoryUse() const;
    quint64 getMemoryPercent() const;

public Q_SLOTS:
    void startQueryCPU(const int &iInterval);
    void stopQueryCPU();
    void queryCPUInfo();
    void readCPUProcessData();

    void startQueryMemory(const int &iInterval);
    void stopQueryMemory();
    void queryMemoryInfo();
    void readMemoryProcessData();

    void startQueryDisk(const int &iInterval);
    void stopQueryDisk();
    void queryDiskInfo();
    void readDiskProcessData();

Q_SIGNALS:
    void cpuChanged(const quint64 &ulPercent);
    void memoryChanged(const quint64 &ulPercent);
    void memoryChanged(const quint64 &ulFree, const quint64 &ulAll);
    void memoryChanged(const quint64 &ulFree, const quint64 &ulAll, const quint64 &ulPercent);
    void diskChanged(const QList<QEXTDiskInfoUtils> &listDiskInfo);

private:
    friend class QEXTHostInfoUtilsPrivate;
    QEXTHostInfoUtilsPrivate *d_ptr;
    Q_DISABLE_COPY(QEXTHostInfoUtils)
};

#endif // QEXTHOSTINFOUTILS_H
