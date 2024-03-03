#include <private/qextWinSystemLibrary_p.h>

#include <QVarLengthArray>
#include <QStringList>
#include <QFileInfo>

#ifdef Q_OS_WIN

#if defined(Q_OS_WINCE)
HINSTANCE QExtWinSystemLibrary::load(const wchar_t *libraryName, bool onlySystemDirectory /* = true */)
{
    return ::LoadLibrary(libraryName);
}
#elif defined(Q_OS_WINRT)
HINSTANCE QExtWinSystemLibrary::load(const wchar_t *libraryName, bool onlySystemDirectory /* = true */)
{
    Q_UNUSED(onlySystemDirectory);
    return ::LoadPackagedLibrary(libraryName, 0);
}
#else

#if !defined(QT_BOOTSTRAPPED)
extern QString qAppFileName();
#endif

static QString qSystemDirectory()
{
    QVarLengthArray<wchar_t, MAX_PATH> fullPath;

    UINT retLen = GetSystemDirectoryW(fullPath.data(), MAX_PATH);
    if (retLen > MAX_PATH)
    {
        fullPath.resize(retLen);
        retLen = GetSystemDirectoryW(fullPath.data(), retLen);
    }
    // in some rare cases retLen might be 0
    return QString::fromWCharArray(fullPath.constData(), int(retLen));
}

HINSTANCE QExtWinSystemLibrary::load(const wchar_t *libraryName, bool onlySystemDirectory /* = true */)
{
    QStringList searchOrder;

#if !defined(QT_BOOTSTRAPPED)
    if (!onlySystemDirectory)
    {
        searchOrder << QFileInfo(qAppFileName()).path();
    }
#endif
    searchOrder << qSystemDirectory();

    if (!onlySystemDirectory)
    {
        const QString PATH(QLatin1String(qgetenv("PATH").constData()));
        searchOrder << PATH.split(QLatin1Char(';'), QString::SkipEmptyParts);
    }
    QString fileName = QString::fromWCharArray(libraryName);
    fileName.append(QLatin1String(".dll"));

    // Start looking in the order specified
    for (int i = 0; i < searchOrder.count(); ++i)
    {
        QString fullPathAttempt = searchOrder.at(i);
        if (!fullPathAttempt.endsWith(QLatin1Char('\\')))
        {
            fullPathAttempt.append(QLatin1Char('\\'));
        }
        fullPathAttempt.append(fileName);
        HINSTANCE inst = LoadLibraryW((const wchar_t *)fullPathAttempt.utf16());
        if (inst != 0)
        {
            return inst;
        }
    }
    return 0;
}

#endif  // Q_OS_WINCE

#endif // Q_OS_WIN
