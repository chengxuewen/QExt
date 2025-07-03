/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
** Copyright (C) 2007 - 2020 Log4Qt contributors
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <qextLogManager.h>

#include <qextLogConsoleAppender.h>
#include <qextLogDatetime.h>
#include <qextLogInitialisationHelper.h>
#include <qextLogOptionConverter.h>
#include <qextLogHierarchy.h>
#include <qextLogPropertyConfigurator.h>
#include <qextLogTTCCLayout.h>
#include <qextLogDenyAllFilter.h>
#include <qextLogLevelRangeFilter.h>
#include <qextLogConfiguratorHelper.h>

#include <QCoreApplication>
#include <QFile>
#include <QMutex>
#include <QSettings>
#include <QStringList>
#include <QFileInfo>
#include <QLoggingCategory>
#include <QStringBuilder>

#include <cstdlib>

static void qt_message_fatal(QtMsgType, const QMessageLogContext &context, const QString &message);
static bool isFatal(QtMsgType msgType);

QEXT_DECLARE_STATIC_LOGGER(static_logger, QExtLogManager)
Q_GLOBAL_STATIC(QMutex, singleton_guard)

QExtLogManager::QExtLogManager() :
#if QT_VERSION < 0x050E00
    mObjectGuard(QMutex::Recursive), // Recursive for doStartup() to call doConfigureLogLogger()
#endif
    mLoggerRepository(new QExtLogHierarchy()),
    mHandleQtMessages(false),
    mWatchThisFile(false),
    mQtMsgHandler(nullptr)
{
}

QExtLogManager::~QExtLogManager()
{
    static_logger()->warn(QStringLiteral("Unexpected destruction of QExtLogManager"));
}


QExtLogger *QExtLogManager::rootLogger()
{
    return instance()->mLoggerRepository->rootLogger();
}


QList<QExtLogger *> QExtLogManager::loggers()
{
    return instance()->mLoggerRepository->loggers();
}


QExtLogLevel QExtLogManager::threshold()
{
    return instance()->mLoggerRepository->threshold();
}


void QExtLogManager::setThreshold(QExtLogLevel level)
{
    instance()->mLoggerRepository->setThreshold(level);
}


bool QExtLogManager::exists(const char *pName)
{
    return instance()->mLoggerRepository->exists(QLatin1String(pName));
}


QExtLogManager *QExtLogManager::instance()
{
    // Do not use Q_GLOBAL_STATIC. The QExtLogManager is rather expensive
    // to construct, an exit handler must be set and doStartup must be
    // called.

    if (!mInstance)
    {
        QMutexLocker locker(singleton_guard());
        if (!mInstance)
        {
            mInstance = new QExtLogManager;
            atexit(shutdown);
            mInstance->doConfigureLogLogger();
            mInstance->welcome();
            mInstance->doStartup();
        }
    }
    return mInstance;
}


QExtLogger *QExtLogManager::logger(const QString &name)
{
    return instance()->mLoggerRepository->logger(name);
}


void QExtLogManager::resetConfiguration()
{
    setHandleQtMessages(false);
    instance()->mLoggerRepository->resetConfiguration();
    configureLogLogger();
}


const char *QExtLogManager::version()
{
    return QEXT_LOGGING_VERSION_STRING;
}

QVersionNumber QExtLogManager::versionNumber()
{
    return QVersionNumber(QEXT_LOGGING_VERSION_MAJOR, QEXT_LOGGING_VERSION_MINOR, QEXT_LOGGING_VERSION_PATCH);
}

void QExtLogManager::shutdown()
{
    instance()->mLoggerRepository->shutdown();
}


void QExtLogManager::doSetHandleQtMessages(bool handleQtMessages)
{
    QMutexLocker locker(&mObjectGuard);

    if (instance()->mHandleQtMessages == handleQtMessages)
        return;

    instance()->mHandleQtMessages = handleQtMessages;
    if (instance()->mHandleQtMessages)
    {
        static_logger()->trace(QStringLiteral("Activate Qt message handling"));
        instance()->mQtMsgHandler = qInstallMessageHandler(qtMessageHandler);
    }
    else
    {
        static_logger()->trace(QStringLiteral("Deactivate Qt message handling"));
        qInstallMessageHandler(instance()->mQtMsgHandler);
    }
}

void QExtLogManager::doSetWatchThisFile(bool watchThisFile)
{
    QMutexLocker locker(&mObjectGuard);

    if (instance()->mWatchThisFile == watchThisFile)
        return;

    instance()->mWatchThisFile = watchThisFile;
    static_logger()->trace(QStringLiteral("%1able watching the current properties file"), watchThisFile ? "En" : "Dis");
}

void QExtLogManager::doSetFilterRules(const QString &filterRules)
{
    QMutexLocker locker(&mObjectGuard);

    if (instance()->mFilterRules == filterRules)
        return;

    instance()->mFilterRules = filterRules;
    QLoggingCategory::setFilterRules(filterRules);
    static_logger()->trace(QStringLiteral("Setting filter rules to: %1"), filterRules);
}

void QExtLogManager::doSetMessagePattern(const QString &messagePattern)
{
    QMutexLocker locker(&mObjectGuard);

    if (instance()->mMessagePattern == messagePattern)
        return;

    instance()->mMessagePattern = messagePattern;
    qSetMessagePattern(messagePattern);
    static_logger()->trace(QStringLiteral("Setting message pattern to: %1"), messagePattern);
}

void QExtLogManager::doConfigureLogLogger()
{
    QMutexLocker locker(&instance()->mObjectGuard);

    // QExtLogLevel
    QString value = QExtLogInitialisationHelper::setting(QStringLiteral("Debug"),
                    QStringLiteral("ERROR"));
    logLogger()->setLevel(QExtLogOptionConverter::toLevel(value, QExtLogLevel::Debug));

    // Common layout
    QExtLogLayoutSharedPtr p_layout(new QExtLogTTCCLayout());
    p_layout->setName(QStringLiteral("LogLog TTCC"));
    static_cast<QExtLogTTCCLayout *>(p_layout.data())->setContextPrinting(false);
    p_layout->activateOptions();

    // Common deny all filter
    QExtLogFilterSharedPtr p_denyall(new QExtLogDenyAllFilter());
    p_denyall->activateOptions();

    // QExtLogConsoleAppender on stdout for all events <= INFO
    QExtLogConsoleAppender *p_appender;
    p_appender = new QExtLogConsoleAppender(p_layout, QExtLogConsoleAppender::STDOUT_TARGET);
    auto *pFilterStdout = new QExtLogLevelRangeFilter();
    pFilterStdout->setNext(p_denyall);
    pFilterStdout->setLevelMin(QExtLogLevel::Null);
    pFilterStdout->setLevelMax(QExtLogLevel::Info);
    pFilterStdout->activateOptions();
    p_appender->setName(QStringLiteral("LogLog stdout"));
    p_appender->addFilter(QExtLogFilterSharedPtr(pFilterStdout));
    p_appender->activateOptions();
    logLogger()->addAppender(QExtLogAppenderSharedPtr(p_appender));

    // QExtLogConsoleAppender on stderr for all events >= WARN
    p_appender = new QExtLogConsoleAppender(p_layout, QExtLogConsoleAppender::STDERR_TARGET);
    auto *pFilterStderr = new QExtLogLevelRangeFilter();
    pFilterStderr->setNext(p_denyall);
    pFilterStderr->setLevelMin(QExtLogLevel::Warn);
    pFilterStderr->setLevelMax(QExtLogLevel::Off);
    pFilterStderr->activateOptions();
    p_appender->setName(QStringLiteral("LogLog stderr"));
    p_appender->addFilter(QExtLogFilterSharedPtr(pFilterStderr));
    p_appender->activateOptions();
    logLogger()->addAppender(QExtLogAppenderSharedPtr(p_appender));
}

/*!
 * \brief QExtLogManager::doStartup
 *
 * 1. If "DefaultInitOverride" or LOG4QT_DEFAULTINITOVERRIDE is not "false" then the initialization is skipped.
 * 2. If the file from "Configuration" or from LOG4QT_CONFIGURATION exists this file is used
 * 3. Check Settings from [Log4Qt/QExtLogProperties] exists the configdata from there is used
 * 4. Check if <application binaryname>.log4qt.properties exists this file is used
 * 5. Check if <application binaryname.exe.log4qt.properties exists this file is used
 * 6. Check if "log4qt.properties" exists in the executables path
 * 7. Check if "log4qt.properties" exists in the current working directory
 */
void QExtLogManager::doStartup()
{
    QMutexLocker locker(&instance()->mObjectGuard);

    // Override
    QString default_value = QStringLiteral("false");
    QString value = QExtLogInitialisationHelper::setting(QStringLiteral("DefaultInitOverride"),
                    default_value);
    if (value != default_value)
    {
        static_logger()->debug(QStringLiteral("DefaultInitOverride is set. Aborting default initialisation"));
        return;
    }

    // Configuration using setting Configuration
    value = QExtLogInitialisationHelper::setting(QStringLiteral("Configuration"));
    if (!value.isEmpty() && QFile::exists(value))
    {
        static_logger()->debug(QStringLiteral("Default initialisation configures from file '%1' specified by Configure"), value);
        QExtLogPropertyConfigurator::configure(value);
        return;
    }

    const QString default_file(QStringLiteral("log4qt.properties"));
    QStringList filesToCheck;

    // Configuration using setting
    if (auto app = QCoreApplication::instance())
    {
        Q_UNUSED(app)
        const QLatin1String log4qt_group("Log4Qt");
        const QLatin1String properties_group("QExtLogProperties");
        QSettings s;
        s.beginGroup(log4qt_group);
        if (s.childGroups().contains(properties_group))
        {
            static_logger()->debug(QStringLiteral("Default initialisation configures from setting '%1/%2'"), log4qt_group, properties_group);
            s.beginGroup(properties_group);
            QExtLogPropertyConfigurator::configure(s);
            return;
        }

        // Configuration using executable file name + .log4qt.properties
        QString binConfigFile = QCoreApplication::applicationFilePath() + QLatin1Char('.') + default_file;

        filesToCheck << binConfigFile;
        if (binConfigFile.contains(QLatin1String(".exe."), Qt::CaseInsensitive))
        {
            binConfigFile.replace(QLatin1String(".exe."), QLatin1String("."), Qt::CaseInsensitive);
            filesToCheck << binConfigFile;
        }

        filesToCheck << QFileInfo(QCoreApplication::applicationFilePath()).path() + QLatin1Char('/') + default_file;
    }

    filesToCheck << default_file;

#if (__cplusplus >= 201703L)
    for (const auto &configFileName: std::as_const(filesToCheck))
#else
    for (const auto &configFileName: qAsConst(filesToCheck))
#endif
    {
        // Configuration using default file
        if (QFile::exists(configFileName))
        {
            static_logger()->debug(QStringLiteral("Default initialisation configures from default file '%1'"), configFileName);
            QExtLogPropertyConfigurator::configure(configFileName);
            if (mWatchThisFile)
               QExtLogConfiguratorHelper::setConfigurationFile(configFileName, QExtLogPropertyConfigurator::configure);
            return;
        }
    }

    static_logger()->debug(QStringLiteral("Default initialisation leaves package unconfigured"));
}


void QExtLogManager::welcome()
{
    static_logger()->info(QStringLiteral("Initialising Log4Qt %1"),
                          QStringLiteral(QEXT_LOGGING_VERSION_STRING));

    // Debug: Info
    if (static_logger()->isDebugEnabled())
    {
        // Create a nice timestamp with UTC offset
        QExtLogDateTime start_time = QDateTime::fromMSecsSinceEpoch(QExtLogInitialisationHelper::startTime());
        QString offset;
        {
            QDateTime utc = start_time.toUTC();
            QDateTime local = start_time.toLocalTime();
            QDateTime local_as_utc = QDateTime(local.date(), local.time(), QTimeZone::utc());
            int min = utc.secsTo(local_as_utc) / 60;
            if (min < 0)
                offset += QLatin1Char('-');
            else
                offset += QLatin1Char('+');
            min = abs(min);
            offset += QString::number(min / 60).rightJustified(2, QLatin1Char('0'));
            offset += QLatin1Char(':');
            offset += QString::number(min % 60).rightJustified(2, QLatin1Char('0'));
        }
        static_logger()->debug(QStringLiteral("Program startup time is %1 (UTC%2)"),
                               start_time.toString(QStringLiteral("ISO8601")),
                               offset);
        static_logger()->debug(QStringLiteral("Internal logging uses the level %1"),
                               logLogger()->level().toString());
    }

    // Trace: Dump settings
    if (static_logger()->isTraceEnabled())
    {
        static_logger()->trace(QStringLiteral("Settings from the system environment:"));
        auto settings = QExtLogInitialisationHelper::environmentSettings();
        for (auto pos = std::begin(settings);pos != std::end(settings);++pos)
            static_logger()->trace(QStringLiteral("    %1: '%2'"), pos.key(), pos.value());

        static_logger()->trace(QStringLiteral("Settings from the application settings:"));
        if (QCoreApplication::instance())
        {
            const QLatin1String log4qt_group("Log4Qt");
            const QLatin1String properties_group("QExtLogProperties");
            static_logger()->trace(QStringLiteral("    %1:"), log4qt_group);
            QSettings s;
            s.beginGroup(log4qt_group);
            for (const auto &entry : s.childKeys())
                static_logger()->trace(QStringLiteral("        %1: '%2'"),
                                       entry,
                                       s.value(entry).toString());
            static_logger()->trace(QStringLiteral("    %1/%2:"), log4qt_group, properties_group);
            s.beginGroup(properties_group);
            for (const auto &entry : s.childKeys())
                static_logger()->trace(QStringLiteral("        %1: '%2'"),
                                       entry,
                                       s.value(entry).toString());
        }
        else
            static_logger()->trace(QStringLiteral("    QCoreApplication::instance() is not available"));
    }
}

void QExtLogManager::qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    QExtLogLevel level;
    switch (type)
    {
    case QtDebugMsg:
        level = QExtLogLevel::Debug;
        break;
    case QtWarningMsg:
        level = QExtLogLevel::Warn;
        break;
    case QtCriticalMsg:
        level = QExtLogLevel::Error;
        break;
    case QtFatalMsg:
        level = QExtLogLevel::Fatal;
        break;
    case QtInfoMsg:
        level = QExtLogLevel::Info;
        break;
    default:
        level = QExtLogLevel::Trace;
    }
    QExtLoggingEvent loggingEvent = QExtLoggingEvent(instance()->qtLogger(),
                                             level,
                                             message,
                                             QExtLogMessageContext(context.file, context.line, context.function),
                                             QStringLiteral("Qt ") % context.category);

    instance()->qtLogger()->log(loggingEvent);


    // Qt fatal behaviour copied from global.cpp qt_message_output()
    // begin {

    if (isFatal(type))
        qt_message_fatal(type, context, message);

    // } end
}

#ifdef Q_OS_WIN
static inline void convert_to_wchar_t_elided(wchar_t *d, size_t space, const char *s) Q_DECL_NOEXCEPT
{
    size_t len = qstrlen(s);
    if (len + 1 > space) {
        const size_t skip = len - space + 4; // 4 for "..." + '\0'
        s += skip;
        len -= skip;
        for (int i = 0; i < 3; ++i)
          *d++ = L'.';
    }
    while (len--)
        *d++ = *s++;
    *d++ = 0;
}
#endif

static void qt_message_fatal(QtMsgType, const QMessageLogContext &context, const QString &message)
{
#if defined(Q_CC_MSVC) && defined(QT_DEBUG) && defined(_DEBUG) && defined(_CRT_ERROR)
    wchar_t contextFileL[256];
    // we probably should let the compiler do this for us, by declaring QMessageLogContext::file to
    // be const wchar_t * in the first place, but the #ifdefery above is very complex  and we
    // wouldn't be able to change it later on...
    convert_to_wchar_t_elided(contextFileL, sizeof contextFileL / sizeof *contextFileL,
                              context.file);
    // get the current report mode
    int reportMode = _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
    _CrtSetReportMode(_CRT_ERROR, reportMode);

    int ret = _CrtDbgReportW(_CRT_ERROR, contextFileL, context.line, _CRT_WIDE(QT_VERSION_STR),
                             reinterpret_cast<const wchar_t *>(message.utf16()));
    if ((ret == 0) && (reportMode & _CRTDBG_MODE_WNDW))
        return; // ignore
    else if (ret == 1)
        _CrtDbgBreak();
#else
    Q_UNUSED(context);
    Q_UNUSED(message);
#endif

    std::abort();
}

static bool isFatal(QtMsgType msgType)
{
    if (msgType == QtFatalMsg)
        return true;

    if (msgType == QtCriticalMsg) {
        static bool fatalCriticals = !qEnvironmentVariableIsEmpty("QT_FATAL_CRITICALS");
        return fatalCriticals;
    }

    if (msgType == QtWarningMsg || msgType == QtCriticalMsg) {
        static bool fatalWarnings = !qEnvironmentVariableIsEmpty("QT_FATAL_WARNINGS");
        return fatalWarnings;
    }

    return false;
}

QExtLogManager *QExtLogManager::mInstance = nullptr;
