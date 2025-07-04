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

#include <qextLogAppenderSkeleton.h>
#include <qextLoggerRepository.h>
#include <qextLogListAppender.h>
#include <qextLoggingEvent.h>
#include <qextLogManager.h>
#include <qextLogStream.h>
#include <qextLogger.h>

#include <QThread>
#include <QCoreApplication>

#if (__cplusplus >= 201703L) // C++17 or later
#   include <utility>
#endif

QExtLogger::QExtLogger(QExtLoggerRepository *loggerRepository, QExtLogLevel level,
                       const QString &name, QExtLogger *parent) :
    QObject(QEXT_NULLPTR),
    mName(name), mLoggerRepository(loggerRepository), mAdditivity(true),
    mLevel(level), mParentLogger(parent)
{
    Q_ASSERT_X(loggerRepository, "QExtLogger::QExtLogger()",
               "Construction of QExtLogger with null QExtLoggerRepository");

    setObjectName( mName);
}

QExtLogger::~QExtLogger()
{
    logger()->warn(QStringLiteral("Unexpected destruction of QExtLogger"));
}

void QExtLogger::setLevel(QExtLogLevel level)
{
    if ((parentLogger() == QEXT_NULLPTR) && (level == QExtLogLevel::Null))
    {
        logger()->warn(QStringLiteral("Invalid root logger level Null. Using Debug instead"));
        level = QExtLogLevel::Debug;
    }
    mLevel = level;
}

// Note: use QExtLogMainThreadAppender if you want write the log from non-main threads
// within the main trhead
void QExtLogger::callAppenders(const QExtLoggingEvent &event) const
{
    QReadLocker locker(&mAppenderGuard);

#if (__cplusplus >= 201703L)
    for (auto &&appender : std::as_const(mAppenders))
#else
    for (auto &&appender : qAsConst(mAppenders))
#endif
    {
        appender->doAppend(event);
    }
    if (additivity() && (parentLogger() != QEXT_NULLPTR))
    {
        parentLogger()->callAppenders(event);
    }
}

QExtLogLevel QExtLogger::effectiveLevel() const
{
    Q_ASSERT_X(QExtLogManager::rootLogger()->level() != QExtLogLevel::Null,
               "QExtLogger::effectiveLevel()", "Root logger level must not be Null");

    QReadLocker locker(&mAppenderGuard);

    const QExtLogger *logger = this;
    while (logger->level() == QExtLogLevel::Null)
    {
        logger = logger->parentLogger();
    }
    return logger->level();
}

bool QExtLogger::isEnabledFor(QExtLogLevel level) const
{
    if (mLoggerRepository->isDisabled(level))
    {
        return false;
    }
    return (effectiveLevel() <= level);
}

QExtLogger *QExtLogger::logger(const QString &name)
{
    return QExtLogManager::logger(name);
}

QExtLogger *QExtLogger::logger(const char *name)
{
    return QExtLogManager::logger(QLatin1String(name));
}

QExtLogger *QExtLogger::rootLogger()
{
    return QExtLogManager::rootLogger();
}

void QExtLogger::forcedLog(QExtLogLevel level, const QString &message) const
{
    QExtLoggingEvent event(this, level, message);
    forcedLog(event);
}

void QExtLogger::forcedLog(const QExtLoggingEvent &logEvent) const
{
    callAppenders(logEvent);
}

bool QExtLogger::additivity() const
{
    return mAdditivity;
}

QExtLogLevel QExtLogger::level() const
{
    return mLevel;
}

QExtLoggerRepository *QExtLogger::loggerRepository() const
{
    return mLoggerRepository;
}

QString QExtLogger::name() const
{
    return mName;
}

QExtLogger *QExtLogger::parentLogger() const
{
    return mParentLogger;
}

void QExtLogger::setAdditivity(bool additivity)
{
    mAdditivity = additivity;
}

// QExtLogLevel operations

bool QExtLogger::isDebugEnabled() const
{
    return isEnabledFor(QExtLogLevel::Debug);
}

bool QExtLogger::isErrorEnabled() const
{
    return isEnabledFor(QExtLogLevel::Error);
}

bool QExtLogger::isFatalEnabled() const
{
    return isEnabledFor(QExtLogLevel::Fatal);
}

bool QExtLogger::isInfoEnabled() const
{
    return isEnabledFor(QExtLogLevel::Info);
}

bool QExtLogger::isTraceEnabled() const
{
    return isEnabledFor(QExtLogLevel::Trace);
}

bool QExtLogger::isWarnEnabled() const
{
    return isEnabledFor(QExtLogLevel::Warn);
}

// Log operations: debug

QExtLogStream QExtLogger::debug() const
{
    return QExtLogStream(*this, QExtLogLevel::Debug);
}

void QExtLogger::debug(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::Debug))
    {
        forcedLog(QExtLogLevel::Debug, logError.toString());
    }
}

void QExtLogger::debug(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::Debug))
    {
        forcedLog(QExtLogLevel::Debug, message);
    }
}

// Log operations: error

QExtLogStream QExtLogger::error() const
{
    return QExtLogStream(*this, QExtLogLevel::Error);
}

void QExtLogger::error(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::Error))
    {
        forcedLog(QExtLogLevel::Error, message);
    }
}

void QExtLogger::error(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::Error))
    {
        forcedLog(QExtLogLevel::Error, logError.toString());
    }
}

// Log operations: fatal

QExtLogStream QExtLogger::fatal() const
{
    return QExtLogStream(*this, QExtLogLevel::Fatal);
}

void QExtLogger::fatal(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::Fatal))
    {
        forcedLog(QExtLogLevel::Fatal, message);
    }
}

void QExtLogger::fatal(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::Fatal))
    {
        forcedLog(QExtLogLevel::Fatal, logError.toString());
    }
}

// Log operations: info

QExtLogStream QExtLogger::info() const
{
    return QExtLogStream(*this, QExtLogLevel::Info);
}

void QExtLogger::info(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::Info))
    {
        forcedLog(QExtLogLevel::Info, message);
    }
}

void QExtLogger::info(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::Info))
    {
        forcedLog(QExtLogLevel::Info, logError.toString());
    }
}

// Log operations: log

QExtLogStream QExtLogger::log(QExtLogLevel level) const
{
    return QExtLogStream(*this, level);
}

void QExtLogger::log(QExtLogLevel level,
                     const QString &message) const
{
    if (isEnabledFor(level))
    {
        forcedLog(level, message);
    }
}

void QExtLogger::log(const QExtLoggingEvent &logEvent) const
{
    if (isEnabledFor(logEvent.level()))
    {
        forcedLog(logEvent);
    }
}

void QExtLogger::logWithLocation(QExtLogLevel level, const char *file, int line, const char *function, const QString &message) const
{
    QExtLoggingEvent loggingEvent = QExtLoggingEvent(this,
                                                     level,
                                                     message,
                                                     QExtLogMessageContext(file, line, function),
                                                     QString());
    forcedLog(loggingEvent);
}

void QExtLogger::log(QExtLogLevel level,
                     const QExtLogError &logError) const
{
    if (isEnabledFor(level))
    {
        forcedLog(level, logError.toString());
    }
}

// Log operations: trace

QExtLogStream QExtLogger::trace() const
{
    return QExtLogStream(*this, QExtLogLevel::Trace);
}

void QExtLogger::trace(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::Trace))
    {
        forcedLog(QExtLogLevel::Trace, message);
    }
}

void QExtLogger::trace(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::Trace))
    {
        forcedLog(QExtLogLevel::Trace, logError.toString());
    }
}

// Log operations: warn

QExtLogStream QExtLogger::warn() const
{
    return QExtLogStream(*this, QExtLogLevel::Warn);
}

void QExtLogger::warn(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::Warn))
    {
        forcedLog(QExtLogLevel::Warn, message);
    }
}

void QExtLogger::warn(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::Warn))
    {
        forcedLog(QExtLogLevel::Warn, logError.toString());
    }
}

void QExtMessageLogger::log(const QString &message) const
{
    mLogger->logWithLocation(mLevel, mContext.file, mContext.line, mContext.function, message);
}

QExtLogStream QExtMessageLogger::log() const
{
    return QExtLogStream(*mLogger.data(), mLevel);
}
