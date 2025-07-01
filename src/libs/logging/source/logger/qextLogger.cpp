/******************************************************************************
 *
 * This file is part of Log4Qt library.
 *
 * Copyright (C) 2007 - 2020 Log4Qt contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

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
#include <utility>
#endif

namespace Log4Qt
{

Logger::Logger(LoggerRepository *loggerRepository, QExtLogLevel level,
               const QString &name, Logger *parent) :
    QObject(nullptr),
    mName(name), mLoggerRepository(loggerRepository), mAdditivity(true),
    mLevel(level), mParentLogger(parent)
{
    Q_ASSERT_X(loggerRepository, "Logger::Logger()",
               "Construction of Logger with null LoggerRepository");

    setObjectName( mName);
}

Logger::~Logger()
{
    logger()->warn(QStringLiteral("Unexpected destruction of Logger"));
}

void Logger::setLevel(QExtLogLevel level)
{
    if ((parentLogger() == nullptr) && (level == QExtLogLevel::NULL_INT))
    {
        logger()->warn(
            QStringLiteral("Invalid root logger level NULL_INT. Using DEBUG_INT instead"));
        level = QExtLogLevel::DEBUG_INT;
    }
    mLevel = level;
}

// Note: use MainThreadAppender if you want write the log from non-main threads
// within the main trhead
void Logger::callAppenders(const LoggingEvent &event) const
{
    QReadLocker locker(&mAppenderGuard);

#if (__cplusplus >= 201703L)
    for (auto &&appender : std::as_const(mAppenders))
#else
    for (auto &&appender : qAsConst(mAppenders))
#endif
        appender->doAppend(event);
    if (additivity() && (parentLogger() != nullptr))
        parentLogger()->callAppenders(event);
}

QExtLogLevel Logger::effectiveLevel() const
{
    Q_ASSERT_X(LogManager::rootLogger()->level() != QExtLogLevel::NULL_INT,
               "Logger::effectiveLevel()", "Root logger level must not be NULL_INT");

    QReadLocker locker(&mAppenderGuard);

    const Logger *logger = this;
    while (logger->level() == QExtLogLevel::NULL_INT)
        logger = logger->parentLogger();
    return logger->level();
}

bool Logger::isEnabledFor(QExtLogLevel level) const
{
    if (mLoggerRepository->isDisabled(level))
        return false;
    return (effectiveLevel() <= level);
}

Logger *Logger::logger(const QString &name)
{
    return LogManager::logger(name);
}

Logger *Logger::logger(const char *name)
{
    return LogManager::logger(QLatin1String(name));
}

Logger *Logger::rootLogger()
{
    return LogManager::rootLogger();
}

void Logger::forcedLog(QExtLogLevel level, const QString &message) const
{
    LoggingEvent event(this, level, message);
    forcedLog(event);
}

void Logger::forcedLog(const LoggingEvent &logEvent) const
{
    callAppenders(logEvent);
}

bool Logger::additivity() const
{
    return mAdditivity;
}

QExtLogLevel Logger::level() const
{
    return mLevel;
}

LoggerRepository *Logger::loggerRepository() const
{
    return mLoggerRepository;
}

QString Logger::name() const
{
    return mName;
}

Logger *Logger::parentLogger() const
{
    return mParentLogger;
}

void Logger::setAdditivity(bool additivity)
{
    mAdditivity = additivity;
}

// QExtLogLevel operations

bool Logger::isDebugEnabled() const
{
    return isEnabledFor(QExtLogLevel::DEBUG_INT);
}

bool Logger::isErrorEnabled() const
{
    return isEnabledFor(QExtLogLevel::ERROR_INT);
}

bool Logger::isFatalEnabled() const
{
    return isEnabledFor(QExtLogLevel::FATAL_INT);
}

bool Logger::isInfoEnabled() const
{
    return isEnabledFor(QExtLogLevel::INFO_INT);
}

bool Logger::isTraceEnabled() const
{
    return isEnabledFor(QExtLogLevel::TRACE_INT);
}

bool Logger::isWarnEnabled() const
{
    return isEnabledFor(QExtLogLevel::WARN_INT);
}

// Log operations: debug

LogStream Logger::debug() const
{
    return LogStream(*this, QExtLogLevel::DEBUG_INT);
}

void Logger::debug(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::DEBUG_INT))
        forcedLog(QExtLogLevel::DEBUG_INT, logError.toString());
}

void Logger::debug(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::DEBUG_INT))
        forcedLog(QExtLogLevel::DEBUG_INT, message);
}

// Log operations: error

LogStream Logger::error() const
{
    return LogStream(*this, QExtLogLevel::ERROR_INT);
}

void Logger::error(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::ERROR_INT))
        forcedLog(QExtLogLevel::ERROR_INT, message);
}

void Logger::error(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::ERROR_INT))
        forcedLog(QExtLogLevel::ERROR_INT, logError.toString());
}

// Log operations: fatal

LogStream Logger::fatal() const
{
    return LogStream(*this, QExtLogLevel::FATAL_INT);
}

void Logger::fatal(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::FATAL_INT))
        forcedLog(QExtLogLevel::FATAL_INT, message);
}

void Logger::fatal(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::FATAL_INT))
        forcedLog(QExtLogLevel::FATAL_INT, logError.toString());
}

// Log operations: info

LogStream Logger::info() const
{
    return LogStream(*this, QExtLogLevel::INFO_INT);
}

void Logger::info(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::INFO_INT))
        forcedLog(QExtLogLevel::INFO_INT, message);
}

void Logger::info(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::INFO_INT))
        forcedLog(QExtLogLevel::INFO_INT, logError.toString());
}

// Log operations: log

LogStream Logger::log(QExtLogLevel level) const
{
    return LogStream(*this, level);
}

void Logger::log(QExtLogLevel level,
                 const QString &message) const
{
    if (isEnabledFor(level))
        forcedLog(level, message);
}

void Logger::log(const LoggingEvent &logEvent) const
{
    if (isEnabledFor(logEvent.level()))
        forcedLog(logEvent);
}

void Logger::logWithLocation(QExtLogLevel level, const char *file, int line, const char *function, const QString &message) const
{
    LoggingEvent loggingEvent = LoggingEvent(this,
                                             level,
                                             message,
                                             MessageContext(file, line, function),
                                             QString());
    forcedLog(loggingEvent);
}

void Logger::log(QExtLogLevel level,
                 const QExtLogError &logError) const
{
    if (isEnabledFor(level))
        forcedLog(level, logError.toString());
}

// Log operations: trace

LogStream Logger::trace() const
{
    return LogStream(*this, QExtLogLevel::TRACE_INT);
}

void Logger::trace(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::TRACE_INT))
        forcedLog(QExtLogLevel::TRACE_INT, message);
}

void Logger::trace(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::TRACE_INT))
        forcedLog(QExtLogLevel::TRACE_INT, logError.toString());
}

// Log operations: warn

LogStream Logger::warn() const
{
    return LogStream(*this, QExtLogLevel::WARN_INT);
}

void Logger::warn(const QString &message) const
{
    if (isEnabledFor(QExtLogLevel::WARN_INT))
        forcedLog(QExtLogLevel::WARN_INT, message);
}

void Logger::warn(const QExtLogError &logError) const
{
    if (isEnabledFor(QExtLogLevel::WARN_INT))
        forcedLog(QExtLogLevel::WARN_INT, logError.toString());
}

void MessageLogger::log(const QString &message) const
{
    mLogger->logWithLocation(mLevel, mContext.file, mContext.line, mContext.function, message);
}

LogStream MessageLogger::log() const
{
    return LogStream(*mLogger.data(), mLevel);
}

} // namespace Log4Qt

// #include "moc_logger.cpp"

