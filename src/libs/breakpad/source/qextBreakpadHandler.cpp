#include <qextBreakpadHandler.h>
#include <qextBreakpadHttpUploader.h>

#include <qextMessageBox.h>
#include <qextCommonUtils.h>

#include <QDir>
#include <QProcess>
#include <QCoreApplication>

#define QBREAKPAD_VERSION  0x000400

#if defined(Q_OS_MAC)
#   include <client/mac/handler/exception_handler.h>
#elif defined(Q_OS_LINUX)
#   include <client/linux/handler/exception_handler.h>
#elif defined(Q_OS_WIN32)
#   include <client/windows/handler/exception_handler.h>
#endif

class QExtBreakpadHandlerPrivate
{
    QExtBreakpadHandler * const q_ptr;
    QEXT_DECL_PUBLIC(QExtBreakpadHandler)
    QEXT_DISABLE_COPY_MOVE(QExtBreakpadHandlerPrivate)
public:
    explicit QExtBreakpadHandlerPrivate(QExtBreakpadHandler *q);
    virtual ~QExtBreakpadHandlerPrivate();

    google_breakpad::ExceptionHandler* mExceptionHandler;
    QString mReporterStyleTheme;
    int mReporterAutoCloseTime;
    bool mReporterEnable;
    QString mDumpPath;
    QUrl mUploadUrl;
};

QExtBreakpadHandlerPrivate::QExtBreakpadHandlerPrivate(QExtBreakpadHandler *q)
    : q_ptr(q)
{
    mReporterAutoCloseTime = 0;
    mReporterEnable = true;
}

QExtBreakpadHandlerPrivate::~QExtBreakpadHandlerPrivate()
{
}

QExtBreakpadHandler::QExtBreakpadHandler(QObject *parent)
    : QObject(parent), dd_ptr(new QExtBreakpadHandlerPrivate(this))
{
}

QExtBreakpadHandler::~QExtBreakpadHandler()
{
}

QString QExtBreakpadHandler::dumpPath() const
{
    Q_D(const QExtBreakpadHandler);
    return d->mDumpPath;
}

#if defined(Q_OS_WIN32)
bool DumpCallback(const wchar_t *dump_dir,
                  const wchar_t *minidump_id,
                  void *context,
                  EXCEPTION_POINTERS *exinfo,
                  MDRawAssertionInfo *assertion,
                  bool succeeded)
#elif defined(Q_OS_MAC)
bool DumpCallback(const char *dump_dir,
                  const char *minidump_id,
                  void *context, bool succeeded)
#else
bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded)
#endif
{
    QString execSuffix;
#ifdef Q_OS_LINUX
    Q_UNUSED(descriptor);
#endif
#if defined(Q_OS_WIN32)
    execSuffix = ".exe";
    Q_UNUSED(assertion);
    Q_UNUSED(exinfo);
#endif

    /*
        NO STACK USE, NO HEAP USE THERE !!!
        Creating QString's, using qDebug, etc. - everything is crash-unfriendly.
    */
#if defined(Q_OS_WIN32)
    QString path = QString::fromWCharArray(dump_dir) + QLatin1String("/") + QString::fromWCharArray(minidump_id) + ".dmp";
    qDebug("%s, dump path: %s\n", succeeded ? "Succeed to write minidump" : "Failed to write minidump", qPrintable(path));
#elif defined(Q_OS_MAC)
    QString path = QString::fromUtf8(dump_dir) + QLatin1String("/") + QString::fromUtf8(minidump_id) + ".dmp";
    qDebug("%s, dump path: %s\n", succeeded ? "Succeed to write minidump" : "Failed to write minidump", qPrintable(path));
#else

    qDebug("%s, dump path: %s\n", succeeded ? "Succeed to write minidump" : "Failed to write minidump", descriptor.path());
#endif

    QStringList reporterPathList;
    reporterPathList.append(QCoreApplication::applicationDirPath() + "/" + QEXT_BREAKPAD_REPORTER_NAME + execSuffix);
    reporterPathList.append(QCoreApplication::applicationDirPath() + "/../bin/" + QEXT_BREAKPAD_REPORTER_NAME + execSuffix);
    QString reporterPath;
    foreach (const QString &path, reporterPathList)
    {
        const QString cleanedPath = QDir::cleanPath(path);
        if (QFile::exists(cleanedPath))
        {
            reporterPath = cleanedPath;
            break;
        }
    }
    if (!reporterPath.isEmpty())
    {
        QExtBreakpadHandlerPrivate *data = static_cast<QExtBreakpadHandlerPrivate *>(context);
        fprintf(stderr, "Start run %s!\n", reporterPath.toLatin1().data());
        QProcess process;
        process.setProgram(reporterPath);
        QStringList arguments;
        arguments.append(QString("--title=%1").arg(QCoreApplication::applicationName() + " crash reporter"));
        arguments.append(QString("--app=%1").arg(QCoreApplication::applicationName()));
        arguments.append(QString("--styletheme=%1").arg(data->mReporterStyleTheme));
        arguments.append(QString("--time=%1").arg(data->mReporterAutoCloseTime));
        arguments.append(QString("--path=%1").arg(path));
        process.setArguments(arguments);
        process.startDetached();
    }
    else
    {
        fprintf(stderr, "%s file not exist!\n", QEXT_BREAKPAD_REPORTER_NAME);
    }
    return succeeded;
}
void QExtBreakpadHandler::setDumpPath(const QString &path)
{
    Q_D(QExtBreakpadHandler);
    QString absPath = path;
    if(!QDir::isAbsolutePath(absPath))
    {
        absPath = QDir::cleanPath(QExtCommonUtils::defaultDataLocation() + "/" + path);
    }
    Q_ASSERT(QDir::isAbsolutePath(absPath));

    QDir dir;
    dir.mkpath(absPath);
    if (!dir.exists(absPath))
    {
        qWarning("Failed to set dump path which not exists: %s", qPrintable(absPath));
        return;
    }

    d->mDumpPath = absPath;

// NOTE: ExceptionHandler initialization
#if defined(Q_OS_WIN32)
    d->mExceptionHandler = new google_breakpad::ExceptionHandler(absPath.toStdWString(), /*FilterCallback*/ 0,
                                                                 DumpCallback, /*context*/ d,
                                                                 google_breakpad::ExceptionHandler::HANDLER_ALL);
#elif defined(Q_OS_MAC)
    d->mExceptionHandler = new google_breakpad::ExceptionHandler(absPath.toStdString(),
                                                                 /*FilterCallback*/ 0,
                                                                 DumpCallback, /*context*/ d, true, NULL);
#else
    d->mExceptionHandler = new google_breakpad::ExceptionHandler(google_breakpad::MinidumpDescriptor(absPath.toStdString()),
                                                                 /*FilterCallback*/ 0,
                                                                 DumpCallback,
                                                                 /*context*/ d,
                                                                 true,
                                                                 -1);
#endif
}

bool QExtBreakpadHandler::isReporterEnable() const
{
    Q_D(const QExtBreakpadHandler);
    return d->mReporterEnable;
}

void QExtBreakpadHandler::setReporterEnable(bool enable)
{
    Q_D(QExtBreakpadHandler);
    d->mReporterEnable = enable;
}

int QExtBreakpadHandler::reporterAutoCloseTime() const
{
    Q_D(const QExtBreakpadHandler);
    return d->mReporterAutoCloseTime;
}

void QExtBreakpadHandler::setReporterAutoCloseTime(int time)
{
    Q_D(QExtBreakpadHandler);
    d->mReporterAutoCloseTime = time;
}

QString QExtBreakpadHandler::reporterStyleTheme() const
{
    Q_D(const QExtBreakpadHandler);
    return d->mReporterStyleTheme;
}

void QExtBreakpadHandler::setReporterStyleTheme(const QString &name)
{
    Q_D(QExtBreakpadHandler);
    d->mReporterStyleTheme = name;
    d->mReporterStyleTheme.replace(" ", "/");
}

QString QExtBreakpadHandler::uploadUrl() const
{
    Q_D(const QExtBreakpadHandler);
    return d->mUploadUrl.toString();
}

QStringList QExtBreakpadHandler::dumpFileList() const
{
    Q_D(const QExtBreakpadHandler);
    if(!d->mDumpPath.isNull() && !d->mDumpPath.isEmpty())
    {
        QDir dumpDir(d->mDumpPath);
        dumpDir.setNameFilters(QStringList()<<"*.dmp");
        return dumpDir.entryList();
    }

    return QStringList();
}

void QExtBreakpadHandler::setUploadUrl(const QUrl &url)
{
    Q_D(QExtBreakpadHandler);
    if(!url.isValid() || url.isEmpty())
    {
        return;
    }
    d->mUploadUrl = url;
}

void QExtBreakpadHandler::sendDumps()
{
    Q_D(QExtBreakpadHandler);
    if(!d->mDumpPath.isNull() && !d->mDumpPath.isEmpty())
    {
        QDir dumpDir(d->mDumpPath);
        dumpDir.setNameFilters(QStringList()<<"*.dmp");
        QStringList dumpFiles = dumpDir.entryList();

        foreach(QString itDmpFileName, dumpFiles)
        {
            qDebug() << "Sending " << QString(itDmpFileName);
            QExtBreakpadHttpUploader *sender = new QExtBreakpadHttpUploader(d->mUploadUrl);
            sender->uploadDump(d->mDumpPath + "/" + itDmpFileName);
        }
    }
}

QString QExtBreakpadHandler::version()
{
    return QString("%1.%2.%3").arg(QString::number((QBREAKPAD_VERSION >> 16) & 0xff),
                                   QString::number((QBREAKPAD_VERSION >> 8) & 0xff),
                                   QString::number(QBREAKPAD_VERSION & 0xff));
}

