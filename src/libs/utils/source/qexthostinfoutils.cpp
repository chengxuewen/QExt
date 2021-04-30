#include "qexthostinfoutils.h"
// Add qt includes here
#include <QProcess>
#include <QFileInfoList>
#include <QDir>
#include <QTimer>
#include <QDebug>

#ifdef Q_CC_GNU
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

#define QEXT_WIN_EXE_SUFFIX    ".exe"

class QEXTHostInfoUtilsPrivate
{
    friend class HHostOsInfo;
public:
    QEXTHostInfoUtilsPrivate();
    ~QEXTHostInfoUtilsPrivate();
    QEXTDiskInfoUtils checkDiskSize(const QString &strResult, const QString &strName);

    QEXTHostInfoUtils *q_ptr;

    QTimer *m_pCPUTimer;
    QProcess *m_pCPUProcess;
    quint64 m_ulCPUTotalNew;
    quint64 m_ulCPUTotalOld;
    quint64 m_ulCPUTotalCurrent;
    quint64 m_ulCPUIdleNew;
    quint64 m_ulCPUIdleOld;
    quint64 m_ulCPUIdleCurrent;
    quint64 m_ulCPUPercent;

    QTimer *m_pMemoryTimer;
    QProcess *m_pMemoryProcess;
    quint64 m_ulMemoryPercent;
    quint64 m_ulMemoryAll;
    quint64 m_ulMemoryUse;
    quint64 m_ulMemoryFree;

    QTimer *m_pDiskTimer;
    QProcess *m_pDiskProcess;
};


QEXTHostInfoUtilsPrivate::QEXTHostInfoUtilsPrivate()
{
    m_pCPUTimer = QEXT_NULLPTR;
    m_pCPUProcess = QEXT_NULLPTR;

    m_pMemoryTimer = QEXT_NULLPTR;
    m_pMemoryProcess = QEXT_NULLPTR;
}

QEXTHostInfoUtilsPrivate::~QEXTHostInfoUtilsPrivate()
{
    if (m_pCPUTimer) {
        if (m_pCPUTimer->isActive()) {
            m_pCPUTimer->stop();
        }
        delete m_pCPUTimer;
        m_pCPUTimer = QEXT_NULLPTR;
    }
    if (m_pMemoryTimer) {
        if (m_pMemoryTimer->isActive()) {
            m_pMemoryTimer->stop();
        }
        delete m_pMemoryTimer;
        m_pMemoryTimer = QEXT_NULLPTR;
    }
}

QEXTDiskInfoUtils QEXTHostInfoUtilsPrivate::checkDiskSize(const QString &strResult, const QString &strName)
{
    QString strDev, strUse, strFee, strAll;
    double dPercent = 0;
    QStringList list = strResult.split(" ");
    int iIndex = 0;
    for (int i = 0; i < list.count(); i++) {
        QString strItem = list.at(i).trimmed();
        if ("" == strItem) {
            continue;
        }
        iIndex++;
        if (1 == iIndex) {
            strDev = strItem;
        } else if (2 == iIndex) {
            strAll = strItem;
        } else if (3 == iIndex) {
            strUse = strItem;
        } else if (4 == iIndex) {
            strFee = strItem;
        } else if (5 == iIndex) {
            dPercent = strItem.left(strItem.length() - 1).toInt();
            break;
        }
    }
    if (strName.length() > 0) {
        strDev = strName;
    }
    QEXTDiskInfoUtils diskInfo;
    diskInfo.setName(strDev);
    diskInfo.setUsedSize(strUse);
    diskInfo.setFreeSize(strFee);
    diskInfo.setAllSize(strAll);
    diskInfo.setUsedPercent(dPercent);
    return diskInfo;
}

QEXTHostInfoUtils::QEXTHostInfoUtils(QObject *parent) : QObject(parent)
{
    d_ptr = new QEXTHostInfoUtilsPrivate();
    d_ptr->q_ptr = this;
    d_ptr->m_pCPUTimer = new QTimer(this);
    connect(d_ptr->m_pCPUTimer, SIGNAL(timeout()), this, SLOT(queryCPUInfo()));
    d_ptr->m_pCPUProcess = new QProcess(this);
    connect(d_ptr->m_pCPUProcess, SIGNAL(readyRead()), this, SLOT(readCPUProcessData()));

    d_ptr->m_pMemoryTimer = new QTimer(this);
    connect(d_ptr->m_pMemoryTimer, SIGNAL(timeout()), this, SLOT(queryMemoryInfo()));
    d_ptr->m_pMemoryProcess = new QProcess(this);
    connect(d_ptr->m_pMemoryProcess, SIGNAL(readyRead()), this, SLOT(readMemoryProcessData()));

    d_ptr->m_pDiskTimer = new QTimer(this);
    connect(d_ptr->m_pDiskTimer, SIGNAL(timeout()), this, SLOT(queryDiskInfo()));
    d_ptr->m_pDiskProcess = new QProcess(this);
    connect(d_ptr->m_pDiskProcess, SIGNAL(readyRead()), this, SLOT(readDiskProcessData()));

    qRegisterMetaType<QEXTDiskInfoUtils>("QEXTDiskInfo");
}

QEXTHostInfoUtils::~QEXTHostInfoUtils()
{
    delete d_ptr;
    d_ptr = QEXT_NULLPTR;
}

QString QEXTHostInfoUtils::getCPUID()
{
    QString cpu_id = "";
    unsigned int dwBuf[4]={0};
    unsigned long long ret = 0;

#if defined(__GNUC__)// GCC
    __cpuid(1, dwBuf[0], dwBuf[1], dwBuf[2], dwBuf[3]);
#elif defined(_MSC_VER)// MSVC
#if _MSC_VER >= 1400 // VC2005 __cpuid
    __cpuid((int*)(void*)dwBuf, (int)(1));
#else //getcpuidex
#if defined(_MSC_VER) // MSVC
#if defined(_WIN64) // Inline assembly is not supported under 64 bit. 1600: VS2010, which is said to be supported after vc2008 Sp1__ cpuidex.
    __cpuidex((int*)(void*)dwBuf, (int)1, (int)0);
#else
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
#endif
#endif
#endif
#endif

    ret = dwBuf[3];
    ret = ret << 32;

    QString str0 = QString::number(dwBuf[3], 16).toUpper();
    QString str0_1 = str0.rightJustified(8,'0'); //This sentence means to fill 0 in front of me, but the situation I encountered was that it was filled up here
    QString str1 = QString::number(dwBuf[0], 16).toUpper();
    QString str1_1 = str1.rightJustified(8,'0'); //Here you must fill in 0 before, otherwise the data will not be filled
    //cpu_id = cpu_id + QString::number(dwBuf[0], 16).toUpper();
    cpu_id = str0_1 + str1_1;
    return cpu_id;
}

QEXTHostInfoUtils::OsType QEXTHostInfoUtils::hostOs()
{
#if defined(Q_OS_WIN)
    return OsTypeWindows;
#elif defined(Q_OS_LINUX)
    return OsTypeLinux;
#elif defined(Q_OS_MAC)
    return OsTypeMac;
#elif defined(Q_OS_UNIX)
    return OsTypeOtherUnix;
#else
    return OsTypeOther;
#endif
}

QEXTHostInfoUtils::HostArchitecture QEXTHostInfoUtils::hostArchitecture()
{
#ifdef Q_OS_WIN
    SYSTEM_INFO info;
    GetNativeSystemInfo(&info);
    switch (info.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        return QEXTHostInfoUtils::HostArchitecture_AMD64;
    case PROCESSOR_ARCHITECTURE_INTEL:
        return QEXTHostInfoUtils::HostArchitecture_X86;
    case PROCESSOR_ARCHITECTURE_IA64:
        return QEXTHostInfoUtils::HostArchitecture_Itanium;
    case PROCESSOR_ARCHITECTURE_ARM:
        return QEXTHostInfoUtils::HostArchitecture_Arm;
    default:
        return QEXTHostInfoUtils::HostArchitecture_Unknown;
    }
#else
    return QEXTHostInfoUtils::HostArchitecture_Unknown;
#endif
}

bool QEXTHostInfoUtils::isWindowsHost()
{
    return QEXTHostInfoUtils::hostOs() == OsTypeWindows;
}

bool QEXTHostInfoUtils::isLinuxHost()
{
    return QEXTHostInfoUtils::hostOs() == OsTypeLinux;
}

bool QEXTHostInfoUtils::isMacHost()
{
    return QEXTHostInfoUtils::hostOs() == OsTypeMac;
}

bool QEXTHostInfoUtils::isAnyUnixHost()
{
#ifdef Q_OS_UNIX
    return true;
#else
    return false;
#endif
}

QString QEXTHostInfoUtils::withExecutableSuffix(const QString &executable)
{
    QString strFinalName = executable;
    if (OsTypeWindows == QEXTHostInfoUtils::hostOs()) {
        strFinalName += QLatin1String(QEXT_WIN_EXE_SUFFIX);
    }
    return strFinalName;
}

Qt::CaseSensitivity QEXTHostInfoUtils::fileNameCaseSensitivity()
{
    return QEXTHostInfoUtils::hostOs() == OsTypeWindows ? Qt::CaseInsensitive : Qt::CaseSensitive;
}

QChar QEXTHostInfoUtils::pathListSeparator()
{
    return QLatin1Char(QEXTHostInfoUtils::hostOs() == OsTypeWindows ? ';' : ':');
}

Qt::KeyboardModifier QEXTHostInfoUtils::controlModifier()
{
    return QEXTHostInfoUtils::hostOs() == OsTypeMac ? Qt::MetaModifier : Qt::ControlModifier;
}

quint64 QEXTHostInfoUtils::getCPUPercent() const
{
    return d_ptr->m_ulCPUPercent;
}

quint64 QEXTHostInfoUtils::getMemoryAll() const
{
    return d_ptr->m_ulMemoryAll;
}

quint64 QEXTHostInfoUtils::getMemoryFree() const
{
    return d_ptr->m_ulMemoryFree;
}

quint64 QEXTHostInfoUtils::getMemoryUse() const
{
    return d_ptr->m_ulMemoryUse;
}

quint64 QEXTHostInfoUtils::getMemoryPercent() const
{
    return d_ptr->m_ulMemoryPercent;
}

void QEXTHostInfoUtils::startQueryCPU(const int &iInterval)
{
    if (iInterval <= 0) {
        qWarning() << "QEXTSystemInfo::startQueryCPU():iInterval must be greate than zero!";
        return;
    }
    this->queryCPUInfo();
    d_ptr->m_pCPUTimer->start(iInterval);
}

void QEXTHostInfoUtils::stopQueryCPU()
{
    d_ptr->m_pCPUTimer->stop();
}

void QEXTHostInfoUtils::queryCPUInfo()
{
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

    d_ptr->m_ulCPUIdleNew = idle;
    d_ptr->m_ulCPUTotalNew = kernel + user;
    d_ptr->m_ulCPUPercent = (kernel + user - idle) * 100 / (kernel + user);

    preidleTime = idleTime;
    prekernelTime = kernelTime;
    preuserTime = userTime ;
    emit this->cpuChanged(d_ptr->m_ulCPUPercent);
#else
    if (QProcess::NotRunning == d_ptr->m_pCPUProcess->state()) {
        d_ptr->m_ulCPUIdleNew = 0;
        d_ptr->m_ulCPUTotalNew = 0;
        d_ptr->m_pCPUProcess->start("cat /proc/stat");
    }
#endif
}

void QEXTHostInfoUtils::readCPUProcessData()
{
    if (d_ptr->m_pCPUProcess->isReadable()) {
        QString strInfo = QLatin1String(d_ptr->m_pCPUProcess->readLine());
        QStringList listInfo = strInfo.split(" ");
        d_ptr->m_ulCPUIdleNew = listInfo.at(5).toUInt();
        d_ptr->m_ulCPUTotalNew = 0;
        foreach (QString strValue, listInfo) {
            d_ptr->m_ulCPUTotalNew += strValue.toUInt();
        }

        d_ptr->m_ulCPUTotalCurrent = d_ptr->m_ulCPUTotalNew - d_ptr->m_ulCPUTotalOld;
        d_ptr->m_ulCPUIdleCurrent = d_ptr->m_ulCPUIdleNew - d_ptr->m_ulCPUIdleOld;
        d_ptr->m_ulCPUPercent = 100 * (d_ptr->m_ulCPUTotalCurrent - d_ptr->m_ulCPUIdleCurrent) / d_ptr->m_ulCPUTotalCurrent;
        d_ptr->m_ulCPUTotalOld = d_ptr->m_ulCPUTotalNew;
        d_ptr->m_ulCPUIdleOld = d_ptr->m_ulCPUIdleNew;
        if (d_ptr->m_ulCPUPercent <= 100) {
            emit this->cpuChanged(d_ptr->m_ulCPUPercent);
        }
    }
}

void QEXTHostInfoUtils::startQueryMemory(const int &iInterval)
{
    if (iInterval <= 0) {
        qWarning() << "QEXTSystemInfo::startQueryMemory():iInterval must be greate than zero!";
        return;
    }
    this->queryMemoryInfo();
    d_ptr->m_pMemoryTimer->start(iInterval);
}

void QEXTHostInfoUtils::stopQueryMemory()
{
    d_ptr->m_pMemoryTimer->stop();
}

void QEXTHostInfoUtils::queryMemoryInfo()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    d_ptr->m_ulMemoryPercent = statex.dwMemoryLoad;
    d_ptr->m_ulMemoryAll = statex.ullTotalPhys / QEXT_MB;
    d_ptr->m_ulMemoryFree = statex.ullAvailPhys / QEXT_MB;
    d_ptr->m_ulMemoryUse = d_ptr->m_ulMemoryAll - d_ptr->m_ulMemoryFree;
    emit this->memoryChanged(d_ptr->m_ulMemoryPercent);
    emit this->memoryChanged(d_ptr->m_ulMemoryFree, d_ptr->m_ulMemoryAll);
    emit this->memoryChanged(d_ptr->m_ulMemoryFree, d_ptr->m_ulMemoryAll, d_ptr->m_ulMemoryPercent);
#else
    if (QProcess::NotRunning == d_ptr->m_pMemoryProcess->state()) {
        d_ptr->m_ulMemoryPercent = 0;
        d_ptr->m_ulMemoryAll = 0;
        d_ptr->m_ulMemoryUse = 0;
        d_ptr->m_ulMemoryFree = 0;
        d_ptr->m_pMemoryProcess->start("cat /proc/meminfo");
    }
#endif
}

void QEXTHostInfoUtils::readMemoryProcessData()
{
    if (d_ptr->m_pMemoryProcess->isReadable()) {
        while (!d_ptr->m_pMemoryProcess->atEnd()) {
            QString strInfo = QLatin1String(d_ptr->m_pMemoryProcess->readLine());
            if (strInfo.startsWith("MemTotal")) {
                strInfo = strInfo.replace(" ", "");
                strInfo = strInfo.split(":").at(1);
                d_ptr->m_ulMemoryAll = strInfo.left(strInfo.length() - 3).toUInt() / QEXT_KB;
            } else if (strInfo.startsWith("MemFree")) {
                strInfo = strInfo.replace(" ", "");
                strInfo = strInfo.split(":").at(1);
                d_ptr->m_ulMemoryFree = strInfo.left(strInfo.length() - 3).toUInt() / QEXT_KB;
            } else if (strInfo.startsWith("Buffers")) {
                strInfo = strInfo.replace(" ", "");
                strInfo = strInfo.split(":").at(1);
                d_ptr->m_ulMemoryFree += strInfo.left(strInfo.length() - 3).toUInt() / QEXT_KB;
            } else if (strInfo.startsWith("Cached")) {
                strInfo = strInfo.replace(" ", "");
                strInfo = strInfo.split(":").at(1);
                d_ptr->m_ulMemoryFree += strInfo.left(strInfo.length() - 3).toUInt() / QEXT_KB;
                d_ptr->m_ulMemoryUse = d_ptr->m_ulMemoryAll - d_ptr->m_ulMemoryFree;
                d_ptr->m_ulMemoryPercent = 100 * d_ptr->m_ulMemoryUse / d_ptr->m_ulMemoryAll;
                break;
            }
        }
        emit this->memoryChanged(d_ptr->m_ulMemoryPercent);
        emit this->memoryChanged(d_ptr->m_ulMemoryFree, d_ptr->m_ulMemoryAll);
        emit this->memoryChanged(d_ptr->m_ulMemoryFree, d_ptr->m_ulMemoryAll, d_ptr->m_ulMemoryPercent);
    }
}

void QEXTHostInfoUtils::startQueryDisk(const int &iInterval)
{
    if (iInterval <= 0) {
        qWarning() << "QEXTSystemInfo::startQueryDisk():iInterval must be greate than zero!";
        return;
    }
    this->queryDiskInfo();
    d_ptr->m_pDiskTimer->start(iInterval);
}

void QEXTHostInfoUtils::stopQueryDisk()
{
    d_ptr->m_pDiskTimer->stop();
}

void QEXTHostInfoUtils::queryDiskInfo()
{
#ifdef Q_OS_WIN
    QFileInfoList listInfo = QDir::drives();
    QList<QEXTDiskInfoUtils> listDiskInfo;
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
            QEXTDiskInfoUtils diskInfo;
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
    if (QProcess::NotRunning == d_ptr->m_pDiskProcess->state()) {
        d_ptr->m_pDiskProcess->start("df -h");
    }
#endif
}

void QEXTHostInfoUtils::readDiskProcessData()
{
    if (d_ptr->m_pDiskProcess->isReadable()) {
        QList<QEXTDiskInfoUtils> listDiskInfo;
        while (!d_ptr->m_pDiskProcess->atEnd()) {
            QString strResult = QLatin1String(d_ptr->m_pDiskProcess->readLine());
#ifdef __arm__
            if (strResult.startsWith("/dev/root")) {
                listDiskInfo.append(d_ptr->checkDiskSize(strResult, tr("Local Disk")));
            } else if (strResult.startsWith("/dev/mmcblk")) {
                listDiskInfo.append(d_ptr->checkDiskSize(strResult, tr("Local Disk")));
            } else if (strResult.startsWith("/dev/mmcblk1p")) {
                listDiskInfo.append(d_ptr->checkDiskSize(strResult, tr("SD Disk")));
            } else if (strResult.startsWith("/dev/sd")) {
                listDiskInfo.append(d_ptr->checkDiskSize(strResult, tr("U-Disk")));
            }
#else
            if (strResult.startsWith("/dev/sd")) {
                listDiskInfo.append(d_ptr->checkDiskSize(strResult, QObject::tr("")));
            }
#endif
        }
        emit this->diskChanged(listDiskInfo);
    }
}
