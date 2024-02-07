#include <qextHostInfoUtils.h>
#include <private/qextHostInfoUtils_p.h>

#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QFileInfoList>

#if defined(Q_CC_GNU) && !defined(Q_WS_QWS)

#include <cpuid.h>

#endif

#ifdef Q_OS_WIN
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501 /* WinXP, needed for GetNativeSystemInfo() */
#include <qt_windows.h>
#endif


#define QEXT_GB (1024 * 1024 * 1024)
#define QEXT_MB (1024 * 1024)
#define QEXT_KB (1024)

#define QEXT_WIN_EXE_SUFFIX ".exe"

QExtHostInfoUtilsPrivate::QExtHostInfoUtilsPrivate(QExtHostInfoUtils *q) : q_ptr(q) {}

QExtHostInfoUtilsPrivate::~QExtHostInfoUtilsPrivate()
{
    if (m_cpuTimer->isActive())
    {
        m_cpuTimer->stop();
    }
    if (m_cpuProcess->isOpen())
    {
        m_cpuProcess->close();
    }
    if (m_memoryTimer->isActive())
    {
        m_memoryTimer->stop();
    }
    if (m_memoryProcess->isOpen())
    {
        m_memoryProcess->close();
    }
}

QExtDiskInfo QExtHostInfoUtilsPrivate::checkDiskSize(const QString &result, const QString &name)
{
    QString dev, use, fee, all;
    double percent = 0;
    QStringList list = result.split(" ");
    int index = 0;
    for (int i = 0; i < list.count(); i++)
    {
        QString item = list.at(i).trimmed();
        if ("" == item)
        {
            continue;
        }
        index++;
        if (1 == index)
        {
            dev = item;
        }
        else if (2 == index)
        {
            all = item;
        }
        else if (3 == index)
        {
            use = item;
        }
        else if (4 == index)
        {
            fee = item;
        }
        else if (5 == index)
        {
            percent = item.left(item.length() - 1).toInt();
            break;
        }
    }
    if (name.length() > 0)
    {
        dev = name;
    }
    QExtDiskInfo diskInfo;
    diskInfo.setName(dev);
    diskInfo.setUsedSize(use);
    diskInfo.setFreeSize(fee);
    diskInfo.setAllSize(all);
    diskInfo.setUsedPercent(percent);
    return diskInfo;
}

QExtHostInfoUtils::QExtHostInfoUtils(QObject *parent)
        : QObject(parent), dd_ptr(new QExtHostInfoUtilsPrivate(this))
{
    Q_D(QExtHostInfoUtils);
    d->m_cpuTimer.reset(new QTimer);
    connect(d->m_cpuTimer.data(), SIGNAL(timeout()), this, SLOT(queryCPUInfo()));
    d->m_cpuProcess.reset(new QProcess);
    connect(d->m_cpuProcess.data(), SIGNAL(readyRead()), this, SLOT(readCPUProcessData()));

    d->m_memoryTimer.reset(new QTimer);
    connect(d->m_memoryTimer.data(), SIGNAL(timeout()), this, SLOT(queryMemoryInfo()));
    d->m_memoryProcess.reset(new QProcess);
    connect(d->m_memoryProcess.data(), SIGNAL(readyRead()), this, SLOT(readMemoryProcessData()));

    d->m_diskTimer.reset(new QTimer);
    connect(d->m_diskTimer.data(), SIGNAL(timeout()), this, SLOT(queryDiskInfo()));
    d->m_diskProcess.reset(new QProcess);
    connect(d->m_diskProcess.data(), SIGNAL(readyRead()), this, SLOT(readDiskProcessData()));

    qRegisterMetaType<QExtDiskInfo>("QExtDiskInfo");
}

QExtHostInfoUtils::~QExtHostInfoUtils()
{

}

QString QExtHostInfoUtils::cpuID()
{
    QString cpu_id = "";
    unsigned int dwBuf[4] = {0};
    unsigned long long ret = 0;

#if defined(Q_CC_GNU) && !defined(Q_WS_QWS) // GCC
    __cpuid(1, dwBuf[0], dwBuf[1], dwBuf[2], dwBuf[3]);
#elif defined(_MSC_VER)// MSVC
#   if _MSC_VER >= 1400 // VC2005 __cpuid
    __cpuid((int*)(void*)dwBuf, (int)(1));
#   else //getcpuidex
#       if defined(_MSC_VER) // MSVC
#           if defined(_WIN64) // Inline assembly is not supported under 64 bit. 1600: VS2010, which is said to be supported after vc2008 Sp1__ cpuidex.
    __cpuidex((int*)(void*)dwBuf, (int)1, (int)0);
#       else
    if (NULL==dwBuf)  return;
    _asm{
        // load.
        mov edi, dwBuf;
        mov eax, 1;
        mov ecx, 0;
        // CPUID
        cpuid;
        // save. CPUInfo
        mov [edi], eax;
        mov [edi+4], ebx;
        mov [edi+8], ecx;
        mov [edi+12], edx;
    }
#           endif
#       endif
#   endif
#endif

    ret = dwBuf[3];
    ret = ret << 32;

    QString string0 = QString::number(dwBuf[3], 16).toUpper();
    QString string0_1 = string0.rightJustified(8,
                                               '0'); //This sentence means to fill 0 in front of me, but the situation I encountered was that it was filled up here
    QString string1 = QString::number(dwBuf[0], 16).toUpper();
    QString string1_1 = string1.rightJustified(8,
                                               '0'); //Here you must fill in 0 before, otherwise the data will not be filled
    //cpu_id = cpu_id + QString::number(dwBuf[0], 16).toUpper();
    cpu_id = string0_1 + string1_1;
    return cpu_id;
}

QExtHostInfoUtils::HostOSType QExtHostInfoUtils::hostOSType()
{
#if defined(Q_OS_WIN)
    return HostOS_Win;
#elif defined(Q_OS_LINUX)
    return HostOS_Linux;
#elif defined(Q_OS_MAC)
    return HostOS_Mac;
#elif defined(Q_OS_UNIX)
    return HostOS_Unix;
#else
    return HostOS_Unknown;
#endif
}

QExtHostInfoUtils::HostArchType QExtHostInfoUtils::hostArchType()
{
#ifdef Q_OS_WIN
    SYSTEM_INFO info;
    GetNativeSystemInfo(&info);
    switch (info.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        return QExtHostInfoUtils::HostArch_AMD64;
    case PROCESSOR_ARCHITECTURE_INTEL:
        return QExtHostInfoUtils::HostArch_X86;
    case PROCESSOR_ARCHITECTURE_IA64:
        return QExtHostInfoUtils::HostArch_Itanium;
    case PROCESSOR_ARCHITECTURE_ARM:
        return QExtHostInfoUtils::HostArch_ARM;
    default:
        return QExtHostInfoUtils::HostArch_Unknown;
    }
#else
    return QExtHostInfoUtils::HostArch_Unknown;
#endif
}

bool QExtHostInfoUtils::isWinSystem()
{
    return QExtHostInfoUtils::hostOSType() == HostOS_Win;
}

bool QExtHostInfoUtils::isLinuxSystem()
{
    return QExtHostInfoUtils::hostOSType() == HostOS_Linux;
}

bool QExtHostInfoUtils::isMacSystem()
{
    return QExtHostInfoUtils::hostOSType() == HostOS_Mac;
}

bool QExtHostInfoUtils::isAnyUnixSystem()
{
#ifdef Q_OS_UNIX
    return true;
#else
    return false;
#endif
}

QString QExtHostInfoUtils::withExecutableSuffix(const QString &executable)
{
    QString finalName = executable;
    if (HostOS_Win == QExtHostInfoUtils::hostOSType())
    {
        finalName += QLatin1String(QEXT_WIN_EXE_SUFFIX);
    }
    return finalName;
}

Qt::CaseSensitivity QExtHostInfoUtils::fileNameCaseSensitivity()
{
    return QExtHostInfoUtils::hostOSType() == HostOS_Win ? Qt::CaseInsensitive : Qt::CaseSensitive;
}

QChar QExtHostInfoUtils::pathListSeparator()
{
    return QLatin1Char(QExtHostInfoUtils::hostOSType() == HostOS_Win ? ';' : ':');
}

Qt::KeyboardModifier QExtHostInfoUtils::controlModifier()
{
    return QExtHostInfoUtils::hostOSType() == HostOS_Mac ? Qt::MetaModifier : Qt::ControlModifier;
}

quint64 QExtHostInfoUtils::cpuPercent() const
{
    Q_D(const QExtHostInfoUtils);
    return d->m_cpuPercent;
}

quint64 QExtHostInfoUtils::memoryAll() const
{
    Q_D(const QExtHostInfoUtils);
    return d->m_memoryAll;
}

quint64 QExtHostInfoUtils::memoryFree() const
{
    Q_D(const QExtHostInfoUtils);
    return d->m_memoryFree;
}

quint64 QExtHostInfoUtils::memoryUsed() const
{
    Q_D(const QExtHostInfoUtils);
    return d->m_memoryUse;
}

quint64 QExtHostInfoUtils::memoryPercent() const
{
    Q_D(const QExtHostInfoUtils);
    return d->m_memoryPercent;
}

void QExtHostInfoUtils::startQueryCPU(int interval)
{
    Q_D(QExtHostInfoUtils);
    if (interval <= 0)
    {
        qWarning() << "QExtHostInfoUtils::startQueryCPU():iInterval must be greate than zero!";
        return;
    }
    this->queryCPUInfo();
    d->m_cpuTimer->start(interval);
}

void QExtHostInfoUtils::stopQueryCPU()
{
    Q_D(QExtHostInfoUtils);
    d->m_cpuTimer->stop();
}

void QExtHostInfoUtils::queryCPUInfo()
{
    Q_D(QExtHostInfoUtils);
#ifdef Q_OS_WIN
    static FILETIME preidleTime;
    static FILETIME prekernelTime;
    static FILETIME preuserTime;

    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    quint64 a, b;
    quint64 idle, kernel, user;

    a = (preidleTime.dwHighDateTime << 31) | preidleTime.dwLowDateTime;
    b = (idleTime.dwHighDateTime << 31) | idleTime.dwLowDateTime;
    idle = b - a;

    a = (prekernelTime.dwHighDateTime << 31) | prekernelTime.dwLowDateTime;
    b = (kernelTime.dwHighDateTime << 31) | kernelTime.dwLowDateTime;
    kernel = b - a;

    a = (preuserTime.dwHighDateTime << 31) | preuserTime.dwLowDateTime;
    b = (userTime.dwHighDateTime << 31) | userTime.dwLowDateTime;
    user = b - a;

    d->m_cpuIdleNew = idle;
    d->m_cpuTotalNew = kernel + user;
    d->m_cpuPercent = (kernel + user - idle) * 100 / (kernel + user);

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime ;
    emit this->cpuChanged(d->m_cpuPercent);
#else
    if (QProcess::NotRunning == d->m_cpuProcess->state())
    {
        d->m_cpuIdleNew = 0;
        d->m_cpuTotalNew = 0;
        d->m_cpuProcess->start("cat /proc/stat");
    }
#endif
}

void QExtHostInfoUtils::readCPUProcessData()
{
    Q_D(QExtHostInfoUtils);
    if (d->m_cpuProcess->isReadable())
    {
        QString info = QLatin1String(d->m_cpuProcess->readLine());
        QStringList infoList = info.split(" ");
        d->m_cpuIdleNew = infoList.at(5).toUInt();
        d->m_cpuTotalNew = 0;
                foreach (QString value, infoList)
            {
                d->m_cpuTotalNew += value.toUInt();
            }

        d->m_cpuTotalCurrent = d->m_cpuTotalNew - d->m_cpuTotalOld;
        d->m_cpuIdleCurrent = d->m_cpuIdleNew - d->m_cpuIdleOld;
        d->m_cpuPercent = 100 * (d->m_cpuTotalCurrent - d->m_cpuIdleCurrent) / d->m_cpuTotalCurrent;
        d->m_cpuTotalOld = d->m_cpuTotalNew;
        d->m_cpuIdleOld = d->m_cpuIdleNew;
        if (d->m_cpuPercent <= 100)
        {
            emit this->cpuChanged(d->m_cpuPercent);
        }
    }
}

void QExtHostInfoUtils::startQueryMemory(int interval)
{
    Q_D(QExtHostInfoUtils);
    if (interval <= 0)
    {
        qWarning() << "QExtHostInfoUtils::startQueryMemory():iInterval must be greate than zero!";
        return;
    }
    this->queryMemoryInfo();
    d->m_memoryTimer->start(interval);
}

void QExtHostInfoUtils::stopQueryMemory()
{
    Q_D(QExtHostInfoUtils);
    d->m_memoryTimer->stop();
}

void QExtHostInfoUtils::queryMemoryInfo()
{
    Q_D(QExtHostInfoUtils);
#ifdef Q_OS_WIN
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    d->m_memoryPercent = statex.dwMemoryLoad;
    d->m_memoryAll = statex.ullTotalPhys / QEXT_MB;
    d->m_memoryFree = statex.ullAvailPhys / QEXT_MB;
    d->m_memoryUse = d->m_memoryAll - d->m_memoryFree;
    emit this->memoryChanged(d->m_memoryPercent);
    emit this->memoryChanged(d->m_memoryFree, d->m_memoryAll);
    emit this->memoryChanged(d->m_memoryFree, d->m_memoryAll, d->m_memoryPercent);
#else
    if (QProcess::NotRunning == d->m_memoryProcess->state())
    {
        d->m_memoryPercent = 0;
        d->m_memoryAll = 0;
        d->m_memoryUse = 0;
        d->m_memoryFree = 0;
        d->m_memoryProcess->start("cat /proc/meminfo");
    }
#endif
}

void QExtHostInfoUtils::readMemoryProcessData()
{
    Q_D(QExtHostInfoUtils);
    if (d->m_memoryProcess->isReadable())
    {
        while (!d->m_memoryProcess->atEnd())
        {
            QString info = QLatin1String(d->m_memoryProcess->readLine());
            if (info.startsWith("MemTotal"))
            {
                info = info.replace(" ", "");
                info = info.split(":").at(1);
                d->m_memoryAll = info.left(info.length() - 3).toUInt() / QEXT_KB;
            }
            else if (info.startsWith("MemFree"))
            {
                info = info.replace(" ", "");
                info = info.split(":").at(1);
                d->m_memoryFree = info.left(info.length() - 3).toUInt() / QEXT_KB;
            }
            else if (info.startsWith("Buffers"))
            {
                info = info.replace(" ", "");
                info = info.split(":").at(1);
                d->m_memoryFree += info.left(info.length() - 3).toUInt() / QEXT_KB;
            }
            else if (info.startsWith("Cached"))
            {
                info = info.replace(" ", "");
                info = info.split(":").at(1);
                d->m_memoryFree += info.left(info.length() - 3).toUInt() / QEXT_KB;
                d->m_memoryUse = d->m_memoryAll - d->m_memoryFree;
                d->m_memoryPercent = 100 * d->m_memoryUse / d->m_memoryAll;
                break;
            }
        }
        emit this->memoryChanged(d->m_memoryPercent);
        emit this->memoryChanged(d->m_memoryFree, d->m_memoryAll);
        emit this->memoryChanged(d->m_memoryFree, d->m_memoryAll, d->m_memoryPercent);
    }
}

void QExtHostInfoUtils::startQueryDisk(int interval)
{
    Q_D(QExtHostInfoUtils);
    if (interval <= 0)
    {
        qWarning() << "QExtHostInfoUtils::startQueryDisk():interval must be greate than zero!";
        return;
    }
    this->queryDiskInfo();
    d->m_diskTimer->start(interval);
}

void QExtHostInfoUtils::stopQueryDisk()
{
    Q_D(QExtHostInfoUtils);
    d->m_diskTimer->stop();
}

void QExtHostInfoUtils::queryDiskInfo()
{
    Q_D(QExtHostInfoUtils);
#ifdef Q_OS_WIN
    QFileInfoList listInfo = QDir::drives();
    QList<QExtDiskInfo> listDiskInfo;
    foreach (QFileInfo dir, listInfo) {
        QString strDirName = dir.absolutePath();
        LPCSTR lpcwstrDriver = (LPCSTR)strDirName.utf16();
        ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
        if (GetDiskFreeSpaceEx(lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes)) {
            QString strUsedSize = QString::number((double)(liTotalBytes.QuadPart - liTotalFreeBytes.QuadPart) / QEXT_GB, 'f', 1);
            strUsedSize += "G";
            QString strFreeSize = QString::number((double) liTotalFreeBytes.QuadPart / QEXT_GB, 'f', 1);
            strFreeSize += "G";
            QString strAllSize = QString::number((double) liTotalBytes.QuadPart / QEXT_GB, 'f', 1);
            strAllSize += "G";
            double dPercent = 100 - ((double)liTotalFreeBytes.QuadPart / liTotalBytes.QuadPart) * 100;
            QExtDiskInfo diskInfo;
            diskInfo.setName(strDirName);
            diskInfo.setUsedSize(strUsedSize);
            diskInfo.setFreeSize(strFreeSize);
            diskInfo.setAllSize(strAllSize);
            diskInfo.setUsedPercent(dPercent);
            listDiskInfo.append(diskInfo);
        }
    }
    emit this->diskChanged(listDiskInfo);
#else
    if (QProcess::NotRunning == d->m_diskProcess->state())
    {
        d->m_diskProcess->start("df -h");
    }
#endif
}

void QExtHostInfoUtils::readDiskProcessData()
{
    Q_D(QExtHostInfoUtils);
    if (d->m_diskProcess->isReadable())
    {
        QList<QExtDiskInfo> diskInfoList;
        while (!d->m_diskProcess->atEnd())
        {
            QString result = QLatin1String(d->m_diskProcess->readLine());
#ifdef __arm__
            if (result.startsWith("/dev/root")) {
                diskInfoList.append(d->checkDiskSize(result, tr("Local Disk")));
            } else if (result.startsWith("/dev/mmcblk")) {
                diskInfoList.append(d->checkDiskSize(result, tr("Local Disk")));
            } else if (result.startsWith("/dev/mmcblk1p")) {
                diskInfoList.append(d->checkDiskSize(result, tr("SD Disk")));
            } else if (result.startsWith("/dev/sd")) {
                diskInfoList.append(d->checkDiskSize(result, tr("U-Disk")));
            }
#else
            if (result.startsWith("/dev/sd"))
            {
                diskInfoList.append(d->checkDiskSize(result, QObject::tr("")));
            }
#endif
        }
        emit this->diskChanged(diskInfoList);
    }
}
