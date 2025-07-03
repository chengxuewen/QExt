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

#ifndef _QEXTLOGGER_H
#define _QEXTLOGGER_H

#include <QObject>

#include <qextLogError.h>
#include <qextLogClassLogger.h>
#include <qextLogAppenderAttachable.h>
#include <qextLogLevel.h>
#include <qextLogStream.h>
#include <qextLoggingEvent.h>

/*!
 * QEXT_DECLARE_STATIC_LOGGER declares a static function \a FUNCTION that
 * returns a pointer to a \ref QExtLogger "QExtLogger" named after \a CLASS.
 *
 * On the first invocation the \ref QExtLogger "QExtLogger" is requested
 * by calling \ref QExtLogger::logger(const char *pName)
 * "QExtLogger::logger( #CLASS )". The pointer is stored to be returned on
 * subsequent invocations.
 *
 * The following example shows how to use the macro to define a logger to be
 * used within a class not derived from QObject.
 *
 * \code
 * #file: counter.h
 *
 * #include logger.h
 *
 * class Counter
 * {
 * public:
 *     Counter();
 *     Counter(int preset);
 * private:
 *     int mCount;
 * }
 * \endcode
 * \code
 * #file: counter.cpp
 *
 * #include counter.h
 *
 * QEXT_DECLARE_STATIC_LOGGER(logger, Counter)
 *
 * Counter::Counter() :
 *     mCount(0)
 * {}
 *
 * void Counter::Counter(int preset) :
 *     mCount(preset)
 * {
 *     if (preset < 0)
 *     {
 *         logger()->warn("Invalid negative counter preset %1. Using 0 instead.", preset);
 *         mCount = 0;
 *     }
 * }
 * \endcode
 *
 * \note The function created by the macro is thread-safe.
 *
 * \sa \ref QExtLogger::logger(const char *pName) "QExtLogger::logger(const char *pName)"
 */
#define QEXT_DECLARE_STATIC_LOGGER(FUNCTION, CLASS) \
        static QExtLogger *FUNCTION() \
        { \
            static QExtLogger *logger(QExtLogger::logger(#CLASS)); \
            return logger; \
        }

/*!
 * QEXT_DECLARE_QCLASS_LOGGER declares member functions to retrieve
 * \ref QExtLogger "QExtLogger" for the class it is used in.
 *
 * On the first invocation the \ref QExtLogger "QExtLogger" is requested
 * by a call to \ref QExtLogger::logger(const char *pName)
 * "QExtLogger::logger(const char *pName)". The pointer is stored to be
 * returned on subsequent invocations.
 *
 * The following example shows how to use the macro to define a logger to be
 * used within a class derived from QObject.
 *
 * \code
 * #file: counter.h
 *
 * #include qobject.h
 * #include logger.h
 *
 * class Counter : public QObject
 * {
 *     Q_OBJECT
 *     QEXT_DECLARE_QCLASS_LOGGER
 * public:
 *     Counter();
 *     Counter(int preset);
 * private:
 *     int mCount;
 * }
 * \endcode
 * \code
 * #file: counter.cpp
 *
 * #include counter.h
 *
 * Counter::Counter() :
 *     mCount(0)
 * {}
 *
 * void Counter::Counter(int preset)
 *     mCount(preset)
 * {
 *     if (preset < 0)
 *     {
 *         logger()->warn("Invalid negative counter preset %1. Using 0 instead.", preset);
 *         mCount = 0;
 *     }
 * }
 * \endcode
 *
 * \note The function created by the macro is thread-safe.
 *
 * \sa \ref QExtLogger::logger(const char *pName) "QExtLogger::logger(const char *pName)",
 *     \ref QExtClassLogger "QExtClassLogger"
 */
#define QEXT_DECLARE_QCLASS_LOGGER \
        private: \
            mutable QExtClassLogger mClassLogger; \
        public: \
            inline QExtLogger *logger() const { return mClassLogger.logger(this); } \
        private:


class QEXT_LOGGING_API QExtMessageLogger
{
    QEXT_DISABLE_COPY_MOVE(QExtMessageLogger)

public:
    explicit QExtMessageLogger(QExtLogger *logger, QExtLogLevel level) : mLogger(logger), mLevel(level) {}
    explicit QExtMessageLogger(QExtLogger *logger, QExtLogLevel level, const char *file, int line, const char *function)
        : mLogger(logger), mLevel(level), mContext(file, line, function) {}

    void log(const QString &message) const;
    template <typename T, typename ...Ts>
    void log(const QString &message, T &&t, Ts &&...ts) const
    {
        log(message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }
    QExtLogStream log() const;

private:
    QPointer<const QExtLogger> mLogger;
    QExtLogLevel mLevel;
    QExtLogMessageContext mContext;
};

// Macros to log with location information, teh logger must have the name
#define l4qFatal(...) \
    for (bool enabled = logger()->isEnabledFor(QExtLogLevel::Fatal); enabled; enabled = false) \
        QExtMessageLogger(logger(), QExtLogLevel::Fatal, __FILE__, __LINE__, Q_FUNC_INFO).log(__VA_ARGS__)
#define l4qError(...) \
    for (bool enabled = logger()->isEnabledFor(QExtLogLevel::Error); enabled; enabled = false) \
        QExtMessageLogger(logger(), QExtLogLevel::Error, __FILE__, __LINE__, Q_FUNC_INFO).log(__VA_ARGS__)
#define l4qWarn(...) \
    for (bool enabled = logger()->isEnabledFor(QExtLogLevel::Warn); enabled; enabled = false) \
        QExtMessageLogger(logger(), QExtLogLevel::Warn, __FILE__, __LINE__, Q_FUNC_INFO).log(__VA_ARGS__)
#define l4qInfo(...) \
    for (bool enabled = logger()->isEnabledFor(QExtLogLevel::Info); enabled; enabled = false) \
        QExtMessageLogger(logger(), QExtLogLevel::Info, __FILE__, __LINE__, Q_FUNC_INFO).log(__VA_ARGS__)
#define l4qDebug(...) \
    for (bool enabled = logger()->isEnabledFor(QExtLogLevel::Debug); enabled; enabled = false) \
        QExtMessageLogger(logger(), QExtLogLevel::Debug, __FILE__, __LINE__, Q_FUNC_INFO).log(__VA_ARGS__)
#define l4qTrace(...) \
    for (bool enabled = logger()->isEnabledFor(QExtLogLevel::Trace); enabled; enabled = false) \
        QExtMessageLogger(logger(), QExtLogLevel::Trace, __FILE__, __LINE__, Q_FUNC_INFO).log(__VA_ARGS__)

class QExtLogAppender;
class QExtLoggerRepository;

/*!
 * \brief The class QExtLogger provides logging services.
 *
 * A pointer to a logger can be retrieved by calling QExtLogger::logger() or
 * QExtLogManager::logger() with the class name as argument. Because a logger
 * is never destroyed it is possible to store the pointer to the logger.
 * This way the lookup of the pointer in the repository is only required
 * on the first logging operation. The macros \ref
 * QEXT_DECLARE_STATIC_LOGGER "QEXT_DECLARE_STATIC_LOGGER" and
 * \ref QEXT_DECLARE_QCLASS_LOGGER "QEXT_DECLARE_QCLASS_LOGGER"
 * provide a thread-safe implementation to store the logger pointer.
 *
 * \note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API QExtLogger : public QObject, public QExtLogAppenderAttachable
{
    Q_OBJECT

    /*!
     * The property holds, if the logger is additive.
     *
     * The default is true for being additive.
     *
     * \sa additive(), setAdditive()
     */
    Q_PROPERTY(bool additivity READ additivity WRITE setAdditivity)

    /*!
     * The property holds the level used by the logger.
     *
     * The default is QExtLogLevel::Null.
     * \sa level(), setLevel()
     */
    Q_PROPERTY(QExtLogLevel level READ level WRITE setLevel)

    /*!
     * The property holds the QExtLoggerRepository of the logger.
     *
     * \sa loggerRepository()
     */
    Q_PROPERTY(QExtLoggerRepository *loggerRepository READ loggerRepository)

    /*!
     * The property holds the name of the logger.
     *
     * \sa name()
     */
    Q_PROPERTY(QString name READ name)

    /*!
     * The property holds the parent logger of the logger.
     *
     * \sa parentLogger()
     */
    Q_PROPERTY(QExtLogger *parentLogger READ parentLogger)

    QEXT_DECLARE_QCLASS_LOGGER

protected:
    QExtLogger(QExtLoggerRepository *loggerRepository, QExtLogLevel level, const QString &name, QExtLogger *parent = nullptr);
    ~QExtLogger() override;

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogger)

public:
    bool additivity() const;
    QExtLogLevel level() const;
    QExtLoggerRepository *loggerRepository() const;
    QString name() const;
    QExtLogger *parentLogger() const;

    void setAdditivity(bool additivity);
    virtual void setLevel(QExtLogLevel level);

    void callAppenders(const QExtLoggingEvent &event) const;

    QExtLogLevel effectiveLevel() const;
    bool isDebugEnabled() const;

    /*!
     * Checks if this logger is enabled for a given QExtLogLevel \a level. If the
     * logger is enabled the function returns true. Otherwise it returns
     * false.
     *
     * A logger is enabled for a level, if the level is greater or equal
     * then the repository threshold and greater and equal then the loggers
     * effective level.
     *
     * \sa QExtLoggerRepository::isDisabled(), effectiveLevel()
     */
    bool isEnabledFor(QExtLogLevel level) const;

    bool isErrorEnabled() const;
    bool isFatalEnabled() const;
    bool isInfoEnabled() const;
    bool isTraceEnabled() const;
    bool isWarnEnabled() const;

    QExtLogStream debug() const;
    void debug(const QExtLogError &logError) const;
    void debug(const QString &message) const;

    template<typename T, typename ...Ts>
    void debug(const QString &message, T &&t, Ts &&...ts)
    {
        debug(message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }


    QExtLogStream error() const;
    void error(const QExtLogError &logError) const;
    void error(const QString &message) const;

    template<typename T, typename ...Ts>
    void error(const QString &message, T &&t, Ts &&...ts)
    {
        error(message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }

    QExtLogStream fatal() const;
    void fatal(const QExtLogError &logError) const;
    void fatal(const QString &message) const;

    template<typename T, typename ...Ts>
    void fatal(const QString &message, T &&t, Ts &&...ts)
    {
        fatal(message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }

    QExtLogStream info() const;
    void info(const QExtLogError &logError) const;
    void info(const QString &message) const;

    template<typename T, typename ...Ts>
    void info(const QString &message, T &&t, Ts &&...ts)
    {
        info(message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }

    QExtLogStream log(QExtLogLevel level) const;
    void log(QExtLogLevel level, const QExtLogError &logError) const;
    void log(const QExtLoggingEvent &logEvent) const;

    void log(QExtLogLevel level, const QString &message) const;
    template<typename T, typename ...Ts>
    void log(QExtLogLevel level, const QString &message, T &&t, Ts &&...ts)
    {
        log(level, message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }

    void logWithLocation(QExtLogLevel level, const char *file, int line, const char *function, const QString &message) const;
    template<typename T, typename ...Ts>
    void logWithLocation(QExtLogLevel level, const char *file, int line, const char *function, const QString &message, T &&t, Ts &&...ts)
    {
        logWithLocation(level, file, line, function, message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }

    QExtLogStream trace() const;
    void trace(const QExtLogError &logError) const;
    void trace(const QString &message) const;

    template<typename T, typename ...Ts>
    void trace(const QString &message, T &&t, Ts &&...ts)
    {
        trace(message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }

    QExtLogStream warn() const;
    void warn(const QExtLogError &logError) const;
    void warn(const QString &message) const;

    template<typename T, typename ...Ts>
    void warn(const QString &message, T &&t, Ts &&...ts)
    {
        warn(message.arg(std::forward<T>(t)), std::forward<Ts>(ts)...);
    }

    // QExtLogManager operations
    static QExtLogger *logger(const QString &name);
    static QExtLogger *logger(const char *name);
    static QExtLogger *rootLogger();

protected:
    void forcedLog(QExtLogLevel level, const QString &message) const;
    void forcedLog(const QExtLoggingEvent &logEvent) const;

private:
    const QString mName;
    QExtLoggerRepository *mLoggerRepository;
    volatile bool mAdditivity;
    QExtLogLevel mLevel;
    QExtLogger *mParentLogger;

    // Needs to be friend to create QExtLogger objects
    friend class QExtLogHierarchy;
};

#endif // _QEXTLOGGER_H
