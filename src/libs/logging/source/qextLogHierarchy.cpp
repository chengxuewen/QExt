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

#include <qextLogHierarchy.h>
#include <qextLogOptionConverter.h>
#include <qextLogBinaryLogger.h>
#include <qextLogger.h>

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

QEXT_DECLARE_STATIC_LOGGER(static_logger, ::QExtLoggerRepository)

QExtLogHierarchy::QExtLogHierarchy() :
    mObjectGuard(QReadWriteLock::Recursive),
    mThreshold(QExtLogLevel::Null),
    mRootLogger(logger(QString()))
{
}

QExtLogHierarchy::~QExtLogHierarchy()
{
    static_logger()->warn(QStringLiteral("Unexpected destruction of QExtLogHierarchy"));
}

bool QExtLogHierarchy::exists(const QString &name) const
{
    QReadLocker locker(&mObjectGuard);

    return mLoggers.contains(name);
}

QExtLogger *QExtLogHierarchy::logger(const QString &name)
{
    QWriteLocker locker(&mObjectGuard);

    return createLogger(name);
}

QList<QExtLogger *> QExtLogHierarchy::loggers() const
{
    QReadLocker locker(&mObjectGuard);

    return mLoggers.values();
}

void QExtLogHierarchy::setThreshold(const QString &threshold)
{
    setThreshold(QExtLogLevel::fromString(threshold));
}

void QExtLogHierarchy::resetConfiguration()
{
    QWriteLocker locker(&mObjectGuard);

    // Reset all loggers.
    // Leave log, qt and root logger to the last to allow debugging of shutdown.

    QExtLogger *p_logging_logger = logger(QLatin1String(""));
    QExtLogger *p_qt_logger = logger(QStringLiteral("Qt"));
    QExtLogger *p_root_logger = rootLogger();

#if (__cplusplus >= 201703L)
    for (auto &&p_logger : std::as_const(mLoggers))
#else
    for (auto &&p_logger : qAsConst(mLoggers))
#endif
    {
        if ((p_logger == p_logging_logger) || (p_logger == p_qt_logger) || (p_logger == p_root_logger))
            continue;
        resetLogger(p_logger, QExtLogLevel::Null);
    }
    resetLogger(p_qt_logger, QExtLogLevel::Null);
    resetLogger(p_logging_logger, QExtLogLevel::Null);
    resetLogger(p_root_logger, QExtLogLevel::Debug);
}

void QExtLogHierarchy::shutdown()
{
    static_logger()->debug(QStringLiteral("Shutting down QExtLogHierarchy"));
    resetConfiguration();
}

QExtLogger *QExtLogHierarchy::createLogger(const QString &orgName)
{
    static const QLatin1String binaryIndicator = QLatin1String("@@binary@@");
    static const QLatin1String name_separator = QLatin1String("::");

    QString name(QExtLogOptionConverter::classNameJavaToCpp(orgName));
    bool needBinaryLogger = orgName.contains(binaryIndicator);

    if (needBinaryLogger)
        name.remove(binaryIndicator);

    QExtLogger *logger = mLoggers.value(name, nullptr);
    if (logger != nullptr)
        return logger;

    if (name.isEmpty())
    {
        logger = new QExtLogger(this, QExtLogLevel::Debug, QStringLiteral("root"), nullptr);
        mLoggers.insert(QString(), logger);
        return logger;
    }
    QString parent_name;
    int index = name.lastIndexOf(name_separator);
    if (index >= 0)
        parent_name = name.left(index);

    if (needBinaryLogger)
        logger = new QExtBinaryLogger(this, QExtLogLevel::Null, name, createLogger(parent_name));
    else
        logger = new QExtLogger(this, QExtLogLevel::Null, name, createLogger(parent_name));
    mLoggers.insert(name, logger);
    return logger;
}

void QExtLogHierarchy::resetLogger(QExtLogger *logger, QExtLogLevel level) const
{
    logger->removeAllAppenders();
    logger->setAdditivity(true);
    logger->setLevel(level);
}
