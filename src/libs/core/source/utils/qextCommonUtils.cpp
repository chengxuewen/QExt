#include <qextCommonUtils.h>
#include <qextOnceFlag.h>

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
    int intThreadID = hasher(std::this_thread::get_id());
    return intThreadID;
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

QString QExtCommonUtils::executablePath()
{
    static constexpr uint32_t bufSize = 4096;
#if defined(QEXT_OS_WIN)
    std::vector<wchar_t> wbuf(bufSize + 1, '\0');
    if (GetModuleFileNameW(nullptr, wbuf.data(), bufSize) == 0 || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        throw std::runtime_error("GetModuleFileName failed" + GetLastWin32ErrorStr());
    }
    return ToUTF8String(wbuf.data());
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
