#ifndef _QEXTSYSTEMLIBRARY_H
#define _QEXTSYSTEMLIBRARY_H

#include <qextGlobal.h>

#include <QtGlobal>
#include <QString>

#ifdef Q_OS_WIN
#include <qt_windows.h>

/**
 * @internal
 * @brief The purpose of this class is to load only libraries that are located in well-known and trusted locations on
 * the filesystem. It does not suffer from the security problem that QLibrary has, therefore it will never search in
 * the current directory.
 *
 * The search order is the same as the order in DLL Safe search mode Windows, except that we don't search:
 *  * The current directory
 *  * The 16-bit system directory. (normally \c{c:\windows\system})
 *  * The Windows directory.  (normally \c{c:\windows})
 *
 *  This means that the effective search order is:
 *  1. Application path.
 *  2. System libraries path.
 *  3. Trying all paths inside the PATH environment variable.
 *
 *  Note, when onlySystemDirectory is true it will skip 1) and 3).
 *
 *  DLL Safe search mode is documented in the "Dynamic-Link Library Search Order" document on MSDN.
 *
 *  Since library loading code is sometimes shared between Windows and WinCE, this class can also be used on WinCE.
 *  However, its implementation just calls the LoadLibrary() function. This is ok since it is documented as not loading
 *  from the current directory on WinCE. This behaviour is documented in the documentation for LoadLibrary for Windows
 *  CE at MSDN. (http://msdn.microsoft.com/en-us/library/ms886736.aspx)
 */
class QEXT_CORE_API QExtWinSystemLibrary
{
public:
    explicit QExtWinSystemLibrary(const QString &libraryName)
    {
        m_libraryName = libraryName;
        m_handle = 0;
        m_didLoad = false;
    }

    explicit QExtWinSystemLibrary(const wchar_t *libraryName)
    {
        m_libraryName = QString::fromWCharArray(libraryName);
        m_handle = 0;
        m_didLoad = false;
    }

    bool load(bool onlySystemDirectory = true)
    {
        m_handle = load((const wchar_t *)m_libraryName.utf16(), onlySystemDirectory);
        m_didLoad = true;
        return (m_handle != 0);
    }

    bool isLoaded()
    {
        return (m_handle != 0);
    }

    QFunctionPointer resolve(const char *symbol)
    {
        if (!m_didLoad)
            load();
        if (!m_handle)
            return 0;
#ifdef Q_OS_WINCE
        return QFunctionPointer(GetProcAddress(m_handle, (const wchar_t*)QString::fromLatin1(symbol).utf16()));
#else
        return QFunctionPointer(GetProcAddress(m_handle, symbol));
#endif
    }

    static QFunctionPointer resolve(const QString &libraryName, const char *symbol)
    {
        return QExtWinSystemLibrary(libraryName).resolve(symbol);
    }

    static HINSTANCE load(const wchar_t *lpFileName, bool onlySystemDirectory = true);
private:
    HINSTANCE m_handle;
    QString m_libraryName;
    bool m_didLoad;
};

#endif // Q_OS_WIN

#endif // _QEXTSYSTEMLIBRARY_H
