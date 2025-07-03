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

#ifndef _QEXTLOGMANAGER_H
#define _QEXTLOGMANAGER_H

#include <qextLogLevel.h>
#include <qextLogger.h>

#include <QList>
#include <QMutex>
#include <QString>
#include <QVersionNumber>

class QExtLoggerRepository;

/*!
 * \brief The class QExtLogManager manages QExtLogger in the default
 *        QExtLoggerRepository.
 *
 * The QExtLogManager manages logger in a single QExtLogHierarchy instance. It
 * provides access to special logger over the logLogger(), qtLogger()
 * and rootLogger() member functions.
 *
 * The QExtLogManager is handling the initialisation on startup. The
 * initialisation procedure will first attempt to configure the package
 * based on environment variables. If the attempt fails it will check for
 * the existence of configuration files in several location. For detailed
 * description of the initialisation procedure see \ref Init
 * "Initialization procedure".
 *
 * Messages created by qDebug(), qWarning(), qCritical() and qFatal() can
 * be can be handled by the QExtLogManager. By default the message handling
 * is disabled. It can be enabled by calling setHandleQtMessages(). Once
 * enabled all messages are logged using the logger qtLogger().
 *
 * The Log4Qt runtime version is accessible over version(). The macros
     * \ref QEXT_LOGGING_VERSION "QEXT_LOGGING_VERSION" and
     * \ref QEXT_LOGGING_VERSION_STRING "QEXT_LOGGING_VERSION_STRING" provide the
     * compile time version.
     *
 * \note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API QExtLogManager
{
private:
    QExtLogManager();
    ~QExtLogManager();
    QEXT_DISABLE_COPY_MOVE(QExtLogManager)

public:
    /*!
     * Returns if the handling of messages created by calls to qDebug(),
     * qWarning(), qCritical() and qFatal() is activated.
     *
     * \sa setHandleQtMessages()
     */
    static bool handleQtMessages();

    /*!
     * Returns true, if the current properties file is watched with a QFileWatcher
     *
     * \sa setWatchThisFile()
     */
    static bool watchThisFile();

    /*!
     * Returns the filter rules for qc[Info|Debug|Warning|Critical]
     *
     * \sa setFilterRules()
     */
    static QString filterRules();

    /*!
     * Returns the message pattern for qc[Info|Debug|Warning|Critical]
     *
     * \sa setMessagePattern()
     */
    static QString messagePattern();

    static QExtLoggerRepository *loggerRepository();

    /*!
     * Returns the logger used for logging internal messages. See
     * \ref LogLog "Logging within the package" for more details.
     *
     * Calling this function is equivalent to calling logger("Log4Qt").
     */
    static QExtLogger *logLogger();

    /*!
     * Returns a pointer to the logger used for logging messages created by
     * calls to qDebug(), qWarning(), qCritical() and qFatal().
     *
     * Calling this function is equivalent to calling logger("Qt").
     *
     * \sa setHandleQtMessages()
     */
    static QExtLogger *qtLogger();

    static QExtLogger *rootLogger();
    static QList<QExtLogger *> loggers();
    static QExtLogLevel threshold();
    static void setThreshold(QExtLogLevel level);

    /*!
     * Activates or deactivates the handling of messages created by calls
     * to qDebug(), qWarning(), qCritical() and qFatal() is activated.
     *
     * If activated, a Qt message handler is installed. Messages are logged
     * using the logger returned by qtLogger(). For fatal messages the same
     * exit procedure is implemented as for qFatal().
     *
     * The following mappping is used from QtMsgType to QExtLogLevel:
     *
         * <table align="center" border="1" cellpadding="2" cellspacing="0" bordercolor="#84b0c7">
         * <tr bgcolor="#d5e1e8">
         * <th> &nbsp;&nbsp;&nbsp; QtMsgType &nbsp;&nbsp;&nbsp;</th>
         * <th> %QExtLogLevel </th>
         * </tr><tr>
         * <td> QtDebugMsg </td>
         * <td> QExtLogLevel::Debug </td>
         * </tr><tr bgcolor="#ffffff">
         * <td> QtWarningMsg </td>
         * <td> QExtLogLevel::Warn </td>
         * </tr><tr>
         * <td> QtCriticalMsg </td>
         * <td> QExtLogLevel::Error </td>
         * </tr><tr bgcolor="#ffffff">
         * <td> QtFatalMsg </td>
         * <td> QExtLogLevel::Fatal </td>
         * </tr><tr>
         * <td> QtSystemMsg </td>
         * <td> QExtLogLevel::Trace </td>
         * </tr>
         * </table>
     *
     * The default value is false for not handling Qt messages.
     *
     * \sa handleQtMessages(), qInstallMsgHandler(), qFatal()
     */
    static void setHandleQtMessages(bool handleQtMessages);

    /*!
     * Enables/disables watching of the current properties file
     *
     * The default value is false for not watching the properties file.
     *
     * \sa watchThisFile()
     */
    static void setWatchThisFile(bool watchThisFile);

    /*!
     * Set a message pattern for qc[Debug|Info|Warn|Critical]
     *
     * \sa messagePattern()
     */
    static void setMessagePattern(const QString &pattern);

    /*!
     * Set the filter rules for qc[Debug|Info|Warn|Critical]
     *
     * \sa filterRules()
     */
    static void setFilterRules(const QString &rules);

    /*!
     * Configures the logging for the package to its default behaviour.
     *
     * The logger logLogger() is configured to be not additive. Messages
     * with the level QExtLogLevel::Error and QExtLogLevel::Fatal are written
     * to \c stderr using a QExtLogConsoleAppender. The remaining messages are
     * written to \c stdout using a second QExtLogConsoleAppender. The level is
     * read from the system environment or application settings using
     * QExtLogInitialisationHelper::setting() with the key \c Debug. If a level
     * value is found, but it is not a valid QExtLogLevel string,
     * QExtLogLevel::Debug is used. If no level string is found
     * QExtLogLevel::Error is used.
     *
     * The function does not remove any appender from the logger
     * logLogger().
     *
     * \sa \ref LogLog "Logging within the package",
     *     \ref Env "Environment Variables",
     *     resetConfiguration(), QExtLogInitialisationHelper::setting()
     */
    static void configureLogLogger();

    static bool exists(const char *pName);

    /*!
     * Returns the QExtLogManager instance.
     */
    static QExtLogManager *instance();

    static QExtLogger *logger(const QString &name);

    /*!
     * Reset all values contained in logger repository to their default.
     *
     * All appenders are removed from all loggers. The loggers are handled
     * in no particular order. The last loggers to be reset are qtLogger(),
     * logLogger() and rootLogger() in that order.
     *
     * The handling of messages created by calls to qDebug(), qWarning(),
     * qCritical() and qFatal() is deactivated.
     *
     * The internal logging is initialised to its default bahaviour
     * using configureLogLogger().
    *
    * \sa QExtLoggerRepository::resetConfiguration(), setHandleQtMessages(),
    *     configureLogLogger()
     */
    static void resetConfiguration();

    static void shutdown();

    /*!
     * Executes the default initialisation procedure of the package.
     *
     * The function will test for the setting \c DefaultInitOverride in
     * the system environment and application settings using
     * \ref QExtLogInitialisationHelper::setting(). If the value is present and
     * set to anything else then \c false, the initialisation is aborted.
     * <br>
     * The system environment and application settings are tested for the
     * setting \c Configuration. If it is found and it is a valid path to
     * a file, the package is configured with the file using
     * \ref QExtLogPropertyConfigurator::doConfigure(const QString &, QExtLoggerRepository *)
     * "QExtLogPropertyConfigurator::doConfigure()". If the setting
     * \c Configuration is not available and a QCoreApplication object is
     * present, the application settings are tested for a group
     * \c QExtLogProperties. If the group exists, the package is configured
     * with the setting using the
     * \ref QExtLogPropertyConfigurator::doConfigure(const QSettings &properties, QExtLoggerRepository *)
     * "PropertyConfiguratordoConfigure()". If neither a configuration
     * file nor configuration settings could be found, the current working
     * directory is searched for the file \c "log4qt.properties". If it is
     * found, the package is configured with the file using
     * \ref QExtLogPropertyConfigurator::doConfigure(const QString &, QExtLoggerRepository *)
     * "QExtLogPropertyConfigurator::doConfigure()".
     *
     * \sa \ref Init "Initialization procedure",
     *     \ref Env "Environment Variables",
     *     QExtLogInitialisationHelper::setting()
     */
    static void startup();

    /*!
     * Returns the version number of Log4Qt at run-time. This may be a
     * different version than the version the application was compiled
     * against.
     *
     * \sa \ref QEXT_LOGGING_VERSION "QEXT_LOGGING_VERSION",
     *     \ref QEXT_LOGGING_VERSION_STRING "QEXT_LOGGING_VERSION_STRING"

     */
    static const char *version();
    static QVersionNumber versionNumber();

private:
    void doSetHandleQtMessages(bool handleQtMessages);
    void doSetWatchThisFile(bool watchThisFile);
    void doSetFilterRules(const QString &filterRules);
    void doSetMessagePattern(const QString &messagePattern);
    void doConfigureLogLogger();
    void doStartup();
    void welcome();

    static void qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);

private:
#if QT_VERSION < 0x050E00
    mutable QMutex mObjectGuard;
#else
    mutable QRecursiveMutex mObjectGuard;
#endif

    QExtLoggerRepository *mLoggerRepository;
    bool mHandleQtMessages, mWatchThisFile;
    QString mFilterRules, mMessagePattern;
    QtMessageHandler mQtMsgHandler;
    static QExtLogManager *mInstance;
};

inline QExtLoggerRepository *QExtLogManager::loggerRepository()
{
    return instance()->mLoggerRepository;
}

inline bool QExtLogManager::handleQtMessages()
{
    return instance()->mHandleQtMessages;
}

inline bool QExtLogManager::watchThisFile()
{
    return instance()->mWatchThisFile;
}

inline QString QExtLogManager::filterRules()
{
    return instance()->mFilterRules;
}

inline QString QExtLogManager::messagePattern()
{
    return instance()->mMessagePattern;
}

inline QExtLogger *QExtLogManager::logLogger()
{
    return logger(QStringLiteral("Log4Qt"));
}

inline QExtLogger *QExtLogManager::qtLogger()
{
    return logger(QStringLiteral("Qt"));
}

inline void QExtLogManager::setHandleQtMessages(bool handleQtMessages)
{
    instance()->doSetHandleQtMessages(handleQtMessages);
}

inline void QExtLogManager::setWatchThisFile(bool watchThisFile)
{
    instance()->doSetWatchThisFile(watchThisFile);
}

inline void QExtLogManager::setFilterRules(const QString &rules)
{
    instance()->doSetFilterRules(rules);
}

inline void QExtLogManager::setMessagePattern(const QString &pattern)
{
    instance()->doSetMessagePattern(pattern);
}

inline void QExtLogManager::configureLogLogger()
{
    instance()->doConfigureLogLogger();
}

inline void QExtLogManager::startup()
{
    instance()->doStartup();
}

#endif // _QEXTLOGMANAGER_H
