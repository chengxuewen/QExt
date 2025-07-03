#include <qextCommonUtils.h>
#include <qextConcurrent.h>
#include <qextOnceFlag.h>

#include <QDir>
#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include <QCryptographicHash>

#ifdef QEXT_OS_WIN
#   include <process.h>
#   include <Shlwapi.h>
#   include <crtdbg.h>
#   include <direct.h>
#   include <stdint.h>
#   include <windows.h>
#else
#   include <dirent.h>
#   include <dlfcn.h>
#   include <cerrno>
#   include <cstring>
#   include <unistd.h> // getcwd
#endif
#if defined(QEXT_OS_APPLE)
#   include <mach-o/dyld.h>
#endif

#if QEXT_CC_STD_11
#   include <thread>
#endif

QExtCommonUtils::QExtCommonUtils()
{
}

qint64 QExtCommonUtils::applicationPid()
{
#ifdef QEXT_OS_WIN
    return _getpid();
#else
    return getpid();
#endif
}

qint64 QExtCommonUtils::applicationTid()
{
#if QEXT_CC_STD_11
    std::hash<std::thread::id> hasher;
    size_t intThreadID = hasher(std::this_thread::get_id());
    return (qint64)intThreadID;
#else
    return (qint64)QThread::currentThreadId();
#endif
}

QString QExtCommonUtils::executableDir()
{
    static QExtOnceFlag once;
    static QString dirString;
    if (once.enter())
    {
        dirString = executablePath();
        const int index = dirString.lastIndexOf('/');
        if (index >= 0)
        {
            dirString = dirString.left(index);
        }
        once.leave();
    }
    return dirString;
}

#ifdef QEXT_OS_WIN
namespace detail
{
std::string GetLastWin32ErrorStr()
{
    std::string errMsg;
    LPVOID lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  GetLastError(),			//Get MessageId
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR)&lpMsgBuf,
                  0,
                  NULL);

    errMsg = (char *)lpMsgBuf;
    // Free the buffer.
    LocalFree(lpMsgBuf);
    return errMsg;
}
}
#endif
QString QExtCommonUtils::executablePath()
{
    static constexpr uint32_t bufSize = 4096;
#if defined(QEXT_OS_WIN)
    std::vector<wchar_t> wbuf(bufSize + 1, '\0');
    if (GetModuleFileNameW(QEXT_NULLPTR, wbuf.data(), bufSize) == 0 || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        qCritical() << QString("GetModuleFileName failed, %1!").arg(detail::GetLastWin32ErrorStr().c_str());
    }
    const QString winPath = QString::fromWCharArray(wbuf.data(), (int)wbuf.size()).toLatin1();
    return QDir::fromNativeSeparators(winPath);
#elif defined(QEXT_OS_APPLE)
    std::vector<char> buf(bufSize + 1, '\0');
    int status = _NSGetExecutablePath(buf.data(), &bufSize);
    if (status == -1)
    {
        buf.assign(bufSize + 1, '\0');
        status = _NSGetExecutablePath(buf.data(), &bufSize);
    }
    if (status != 0)
    {
        throw std::runtime_error("_NSGetExecutablePath() failed");
    }
    // the returned path may not be an absolute path
    return buf.data();
#else
    std::vector<char> buf(bufSize + 1, '\0');
    ssize_t len = ::readlink("/proc/self/exe", buf.data(), bufSize);
    if (len == -1 || len == static_cast<ssize_t>(bufSize))
    {
        throw std::runtime_error("Could not read /proc/self/exe into buffer");
    }
    return buf.data();
#endif
}

namespace detail
{
QExtConcurrent<QString> &defaultDataLocationPath()
{
    static QExtConcurrent<QString> path = QExtCommonUtils::appUniqueDataLocation();
    return path;
}
QExtConcurrent<QString> &defaultConfigLocationPath()
{
    static QExtConcurrent<QString> path = QExtCommonUtils::appUniqueConfigLocation();
    return path;
}
}

QString QExtCommonUtils::defaultDataLocation()
{
    return detail::defaultDataLocationPath().get();
}

void QExtCommonUtils::setDefaultDataLocation(const QString &path)
{
    detail::defaultDataLocationPath().reset(path);
}

QString QExtCommonUtils::defaultConfigLocation()
{
    return detail::defaultConfigLocationPath().get();
}

void QExtCommonUtils::setDefaultConfigLocation(const QString &path)
{
    detail::defaultConfigLocationPath().reset(path);
}

QString QExtCommonUtils::writableLocation(QStandardPaths::StandardLocation location)
{
    return QStandardPaths::writableLocation(location);
}

QString QExtCommonUtils::writableUniqueLocation(QStandardPaths::StandardLocation location)
{
    QString locationPath;
    QString rootPath = QStandardPaths::writableLocation(location);
    QString execPath = QCoreApplication::applicationDirPath();
    // get MD5 code
    QString md5String = QCryptographicHash::hash(execPath.toUtf8(), QCryptographicHash::Md5).toHex();
    locationPath = rootPath + "/" + md5String;
    // fprintf(stderr, "%s\n", locationPath.toLatin1().data());
    QDir dir(locationPath);
    if (!dir.exists())
    {
        if (!dir.mkpath(locationPath))
        {
            qFatal("mkdir %s failed!", locationPath.toLatin1().data());
        }
    }
    QFile noteFile(locationPath + "/note.txt");
    if (noteFile.open(QFile::WriteOnly))
    {
        QTextStream stream(&noteFile);
        stream << execPath;
        noteFile.close();
    }
    return locationPath;
}
