/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
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

#ifndef _QEXTLOGGING_H
#define _QEXTLOGGING_H

#include <qextLogPropertyConfigurator.h>
#include <qextLogConsoleAppender.h>
#include <qextLoggerRepository.h>
#include <qextLogFileAppender.h>
#include <qextLogTTCCLayout.h>
#include <qextLogManager.h>
#include <qextLogger.h>

/*!
 * \page Log4Qt/Log4j
 *
 * %Log4Qt is a C++ port of the Apache Software Foundation Log4j package
 * using the Qt Framework.
 *
 * The documentation describes classes and methods that have been added or
 * changed compared to Log4j.
 *
 * The following sections are describing the implementation in more detail:
 * - \ref Changes "Differences to Log4j"
 * - \ref Ownership "Object ownership"
 * - \ref LogLog "Logging within the package"
 * - \ref Init "Initialization procedure"
 * - \ref Env "Environment Variables"
 * - \ref Undocumented "Undocumented functions"
 * - \ref Assumptions "Assumptions"
 *
 */

/*!
 * \page Changes Differences to Log4j
 *
 * The following fundamental differences exist between %Log4Qt and Log4j:
 *
 * - As a JAVA package Log4j does not have to manage object ownership and
 *   lifetime in the same way then it is required in C++. For details on
 *   how object ownership is handled see \ref Ownership "Object ownership".
 * - The package uses itself for its internal logging similar to Log4j 1.3.
 *   For details see \ref LogLog "Logging within the package".
 * - The configuration using system properties was replaced with a combination
 *   of environment variables and application settings. For details see
 *   \ref Env "Environment Variables".
 * - Custom levels are not supported.
 * - Multiple QExtLogger Repositories are not supported
 *
 * The following classes have been changed:
 *
 * - \ref QExtLogAppenderSkeleton "QExtLogAppenderSkeleton"
 *   - The procedure of checking, if logging is possible, originally used by
 *     \ref QExtLogWriterAppender "QExtLogWriterAppender" was generalised and is used
 *     in \ref QExtLogAppenderSkeleton "QExtLogAppenderSkeleton" and derived classes
 *     (\ref QExtLogAppenderSkeleton::checkEntryConditions() "checkEntryConditions()").
 *   - The \ref QExtLogAppenderSkeleton::doAppend() "doAppend()" member function will
 *     check the entry conditions by calling the sub-class specific
 *     \ref QExtLogAppenderSkeleton::checkEntryConditions() "checkEntryConditions()".
 *     If successful the sub-class specific
 *     \ref QExtLogAppenderSkeleton::append() "append()" function is called.
 *
 * - Configurator
 *   - Configure functions return a boolean indicating, if the configuration
 *     was successful.
 *   - Configure errors are accessible over
 *     \ref QExtLogConfiguratorHelper::configureError()
 *     "QExtLogConfiguratorHelper::configureError()".
 *   - Watching for configuration file changes is a function performed
 *     centrally by the \ref QExtLogConfiguratorHelper "QExtLogConfiguratorHelper".
 *     The class provides Q_SIGNALS to notify on configuration change and errors.
 *   - The class \ref QExtLogPropertyConfigurator "QExtLogPropertyConfigurator" was
 *     extended to be able to read configuration data from a QSettings object.
 *
 * - \ref QExtLogLevel "QExtLogLevel"
 *   - A new value \ref QExtLogLevel::Null "QExtLogLevel::Null" was
 *     introduced to indicate there is no level set.
 *
 * - \ref QExtLogger "QExtLogger"
 *   - The method \ref QExtLogger::isEnabledFor() "isEnabledFor()"
 *     does also take the repository threshold into account.
 *   - Several overloaded convenience member function are available to log
 *     messages with arguments of different types.
 *   - Two macros, \ref QEXT_DECLARE_STATIC_LOGGER "QEXT_DECLARE_STATIC_LOGGER"
 *     and \ref QEXT_DECLARE_QCLASS_LOGGER "QEXT_DECLARE_QCLASS_LOGGER",
 *     allows retrieving and caching of a pointer to a logger object.
 *
 * - \ref QExtLogManager "QExtLogManager"
 *   - A QtMessage handler can be installed via
 *     \ref QExtLogManager::setHandleQtMessages() "setHandleQtMessages()",
 *     to redirect all messages created by calls to qDebug(), qWarning(),
 *     qCritical() and qFatal() to a logger. The logger is named Qt and can be
 *     accessed using \ref QExtLogManager::qtLogger() "qtLogger()".
 *   - The initialisation procedure is available over a public method
 *     (\ref QExtLogManager::startup() "startup()").
 *   - The QExtLogManager provides access to the logger used internally by the
 *     package (\ref QExtLogManager::logLogger() "logLogger()") and to
 *     its default initialisation procedure
 *     (\ref QExtLogManager::configureLogLogger() "configureLogLogger()").
 *
 * - \ref QExtLogWriterAppender "QExtLogWriterAppender"
 *   - The class will call  \ref QExtLogWriterAppender::handleIoErrors()
 *     "handleIoErrors()" after all I/O operations. Sub-classes should
 *     re-implement the function to handle errors.
 *
 * - \ref QExtLogRollingFileAppender "QExtLogRollingFileAppender"*
 *   - The class behaves different to the log4/log4cpp implementation
 *     on application restart the existing log files are rolled if
 *     appendFile is set to false to avoid data loss.
 *
 * The following classes have been added:
 *
 * - An additional appender class, \ref QExtLogDebugAppender "QExtLogDebugAppender",
 *   was added. The class appends logging events to the platform specific debug
 *   output.
 * - Various helper class have been introduced:
 *   - \ref QExtClassLogger "QExtClassLogger": The class QExtClassLogger provides
 *     logging for a QObject derived class.
 *   - \ref QExtLogConfiguratorHelper "QExtLogConfiguratorHelper": The class
 *     QExtLogConfiguratorHelper provides a configuration file watch and last error
 *     for configurator classes.
 *   - \ref QExtLogDateTime "QExtLogDateTime": The class QExtLogDateTime provides extended
 *     functionality for QDateTime.
 *   - \ref QExtLogError "QExtLogError": The class QExtLogError represents an error.
 *   - \ref QExtLogFactory "QExtLogFactory": The class QExtLogFactory provides factories
 *     for QExtLogAppender, QExtLogFilter and QExtLogLayout objects.
 *   - \ref QExtLogInitialisationHelper "QExtLogInitialisationHelper": The class
 *     QExtLogInitialisationHelper performs static initialisation tasks.
 *   - \ref QExtLogPatternFormatter "QExtLogPatternFormatter": The class
 *     QExtLogPatternFormatter formats a logging event based on a pattern string.
 *   - \ref QExtLogProperties "QExtLogProperties": The class QExtLogProperties implements a
 *     JAVA property hash.
 */

/*!
 * \page Ownership Object ownership
 *
 * In difference to the JAVA Log4j package %Log4Qt must manage ownership and
 * lifetime of the objects used. This is non trivial as objects are created
 * and used in different ways.
 *
 * In general an object can be created explicitly for example an application
 * may create Loggers, Appenders and Layouts during creation of a QApplication
 * object. But they can also be automatically created by the package on
 * startup using a \ref QExtLogPropertyConfigurator "QExtLogPropertyConfigurator"
 * configuration file. Objects may also be created the one way and then used
 * the other. Object may be used by multiple other objects. A QExtLogLayout for example
 * may be used by multiple Appenders. Objects are also created from multiple
 * threads. The creation may happen during static initialisation and the
 * deletion during static de-initialization.
 *
 * The parent child model used by QObject cannot be used to handle this. It
 * cannot automatically delete an object that is used by multiple others as
 * for example an QExtLogAppender used by multiple Loggers. In addition to this
 * QObjects and their children must reside in the same thread. This would
 * either mean to impose restriction on how objects can be created or to move
 * objects to a specific thread.
 *
 * To allow an automatic deletion of not required objects as  Appenders,
 * Layouts and Filters QSharedPointer is used
 *
 * The following example configures a logger and uses reference counting to
 * manage the ownership of objects.
 *
 * \code
 * // Create layout
 * QExtLogTTCCLayout *p_layout = new QExtLogTTCCLayout();
 *
 * // Create appender
 * QExtLogConsoleAppender *p_appender = new QExtLogConsoleAppender(p_layout, QExtLogConsoleAppender::STDOUT_TARGET);
 * p_appender->activateOptions();
 *
 * // Get logger
 * QExtLogger *p_logger = QExtLogger::logger("MyClass");
 * p_logger->addAppender(p_appender);
 *
 * // ...
 *
 * // Remove appender from QExtLogger
 * p_logger->removeAllAppenders(); // p_appender and p_layout are deleted here
 * \endcode
 *
 * The following example configures a logger and uses QObject ownership of
 * objects.
 *
 * \code
 * QObject *p_parent = new MyObject;
 *
 * // Create objects
 * QExtLogConsoleAppender *p_appender = new QExtLogConsoleAppender(p_parent);
 * QExtLogTTCCLayout *p_layout = new QExtLogTTCCLayout(p_appender);
 *
 * // Configure appender
 * p_appender->setTarget(QExtLogConsoleAppender::STDOUT_TARGET);
 * p_appender->setLayout(QExtLogLayoutSharedPtr(p_layout));
 * p_appender->activateOptions();
 *
 * // Get logger
 * QExtLogger *p_logger = QExtLogger::logger("MyClass");
 * p_logger->addAppender(QExtLogAppenderSharedPtr(p_appender));
 *
 * // ...
 *
 * // Remove appender from QExtLogger
 * p_logger->removeAllAppenders();
 *
 * delete p_parent; // p_appender and p_layout are deleted here
 * \endcode
 *
 */

/*!
 * \page LogLog Logging within the package
 *
 * The package uses itself for logging similar to Log4j 1.3. This brings much
 * more flexibility over logging to stdout, stderr like in Log4j 1.2 using
 * logLog. It also enables the program to capture and handle errors raised by
 * the package.
 *
 * Using this approach introduces the issue of recursion. The following example
 * explains a situation where this happens. Let's say all logger are configured
 * to be additive and only the root logger has an appender set. The appender
 * is a \ref QExtLogFileAppender "QExtLogFileAppender". During the logging of an
 * event an I/O error occurs. The \ref QExtLogFileAppender "QExtLogFileAppender" logs
 * an event by itself using the logger %QExtLogFileAppender. The event is
 * passed to the root logger, which calls then the \ref QExtLogFileAppender
 * "QExtLogFileAppender". This causes another I/O error, which is logged by
 * the \ref QExtLogFileAppender "QExtLogFileAppender".
 *
 * To avoid an endless loop the appender will drop the event on a recursive
 * invocation. This check is done by \ref QExtLogAppenderSkeleton
 * "QExtLogAppenderSkeleton" in \ref QExtLogAppenderSkeleton::doAppend()
 * "doAppend()".
 *
 * The problem only occurs, if a logger, appender, layout or filter log an
 * event while an event is appended. Neither the logger class nor any of the
 * layout or filter classes log events during appending of an event. Most of
 * the appender classes may log errors during appending. Only the
 * \ref QExtLogListAppender "QExtLogListAppender" and
 * \ref QExtLogListAppender "QExtLogConsoleAppender" are not logging events.
 *
 * The default configuration uses two \ref QExtLogListAppender
 * "QExtLogConsoleAppender", one for stderr and one for stdout. No event will be
 * dropped, because no recursive invocations can occur.
 */

/*!
 * \page Init Initialization procedure
 *
 * The package is initialised in two stages. The first stage takes place during
 * static initialization. The second stage takes place when the
 * \ref QExtLogManager "QExtLogManager" singleton is created.
 *
 * During static initialisation the \ref QExtLogInitialisationHelper
 * "QExtLogInitialisationHelper" singleton is created . On construction it captures
 * the program startup time, reads the required values from the system
 * environment and registers the package types with the Qt type system.
 *
 * The \ref QExtLogManager "QExtLogManager" singleton is created on first use.
 * The creation is usually triggered by the request for a \ref QExtLogger
 * "QExtLogger" object. The call to \ref QExtLogger::logger()
 * "QExtLogger::logger()" is passed through to \ref QExtLogManager::logger()
 * "QExtLogManager::logger()". On creation the \ref QExtLogManager "QExtLogManager"
 * creates a \ref QExtLogHierarchy "QExtLogHierarchy" object as logger repository.
 *
 * After the singleton is created the logging of the package is configured to
 * its default by a call to \ref QExtLogManager::configureLogLogger()
 * "QExtLogManager::configureLogLogger()". The logger
 * \ref QExtLogManager::logLogger() "logLogger()" is configured to be not
 * additive. Messages with the level \ref QExtLogLevel::Error
 * "QExtLogLevel::Error" and \ref QExtLogLevel::Fatal "QExtLogLevel::Fatal" are
 * written to \c stderr using a QExtLogConsoleAppender. The remaining messages are
 * written to \c stdout using a second QExtLogConsoleAppender. The level is read from
 * the system environment or application settings using
 * \ref QExtLogInitialisationHelper::setting()
 * "QExtLogInitialisationHelper::setting()" with the key \c Debug. If a level value
 * is found, but it is not a valid QExtLogLevel string,
 * \ref QExtLogLevel::Debug "QExtLogLevel::Debug" is used. If no level string
 * is found \ref QExtLogLevel::Error "QExtLogLevel::Error" is used.
 *
 * Once the logging is configured the package is initialised by a call to
 * \ref QExtLogManager::startup() "QExtLogManager::startup()". The function
 * will test for the setting \c DefaultInitOverride in the system environment
 * and application settings using \ref QExtLogInitialisationHelper::setting()
 * "QExtLogInitialisationHelper::setting()". If the value is present and set to
 * anything else then \c false, the initialisation is aborted.<br>
 * The system environment and application settings are tested for the setting
 * \c Configuration. If it is found and it is a valid path to a file, the
 * package is configured with the file using
 * \ref QExtLogPropertyConfigurator::doConfigure(const QString &, QExtLoggerRepository *)
 * "QExtLogPropertyConfigurator::doConfigure()". If the setting \c Configuration is
 * not available and a QCoreApplication object is present, the application
 * settings are tested for a group \c QExtLogProperties. If the group exists,
 * the package is configured with the setting using the
 * \ref QExtLogPropertyConfigurator::doConfigure(const QSettings &properties, QExtLoggerRepository *)
 * "PropertyConfiguratordoConfigure()". If neither a configuration file nor
 * configuration settings could be found, the current working directory is
 * searched for the file \c "log4qt.properties". If it is found, the package
 * is configured with the file using
 * \ref QExtLogPropertyConfigurator::doConfigure(const QString &, QExtLoggerRepository *)
 * "QExtLogPropertyConfigurator::doConfigure()".
 *
 * The following example shows how to use application settings to initialise the
 * package.
 *
 * \code
 * # file: myapplication.h
 *
 * #include qapplication.h
 *
 * class MyApplication : public QApplication
 * {
 *     Q_OBJECT
 *
 * public:
 *     MyApplication();
 *     ~MyApplication();
 *     void setupLog4Qt();
 * }
 * \endcode
 * \code
 * # file: myapplication.cpp
 *
 * #include myapplication.h
 *
 * MyApplication::MyApplication(
 * {
 *     // Set Application data to allow Log4Qt initialisation to read the
 *     // correct values
 *     setApplicationName("MyApplication");
 *     setOrganisationName("MyOrganisation");
 *     setOrganizationDomain("www.myorganisation.com");
 *
 *     // Log first message, which initialises Log4Qt
 *     QExtLogger::logger("MyApplication")->info("Hello World");
 * }
 *
 * MyApplication::~MyApplication()
 * {
 * }
 *
 * void MyApplication::setupLog4Qt()
 * {
 *     QSettings s;
 *
 *     // Set logging level for Log4Qt to TRACE
 *     s.beginGroup("Log4Qt");
 *     s.setValue("Debug", "TRACE");
 *
 *     // Configure logging to log to the file C:/myapp.log using the level TRACE
 *     s.beginGroup("QExtLogProperties");
 *     s.setValue("QExtLogging.Appender.A1", "org.QExt.LogFileAppender");
 *     s.setValue("QExtLogging.Appender.A1.file", "C:/myapp.log");
 *     s.setValue("QExtLogging.Appender.A1.layout", "org.QExt.LogTTCCLayout");
 *     s.setValue("QExtLogging.Appender.A1.layout.DateFormat", "ISO8601");
 *     s.setValue("QExtLogging.RootLogger", "TRACE, A1");
 *
 *     // Settings will become active on next application startup
 * }
 * \endcode
 */

/*!
 * \page Env Environment Variables
 *
 * The package uses environment variables to control the initialization
 * procedure. The environment variables replace the system property entries
 * used by Log4j.
 *
 * For compability reasons the Log4j entry is recognised. Alternatively a
 * environment variable style Log4Qt form can be used. The following entries
 * are used:
 *
 * - QEXT_DEBUG<br>
 *   The variable controls the \ref QExtLogLevel "QExtLogLevel" value for the
 *   logger \ref QExtLogManager::logLogger() "QExtLogManager::logLogger()".
 *   If the value is a valid \ref QExtLogLevel "QExtLogLevel" string, the level for
 *   the is set to the level. If the value is not a valid
 *   \ref QExtLogLevel "QExtLogLevel" string, \ref QExtLogLevel::Debug
 *   "Debug" is used. Otherwise \ref QExtLogLevel::Error "Error"
 *   is used.
 *   - \ref QExtLogManager::configureLogLogger()
 *     "QExtLogManager::configureLogLogger()"
 *
 * - QEXT_DEFAULTINITOVERRIDE<br>
 *   The variable controls the \ref Init "initialization procedure" performed
 *   by the \ref QExtLogManager "QExtLogManager" on startup. If it is set to
 *   any other value then \c false the \ref Init "initialization procedure"
 *   is skipped.
 *   - \ref QExtLogManager::startup() "QExtLogManager::startup()"
 *
 * - QEXT_CONFIGURATION<br>
 *   The variable specifies the configuration file used for initialising the
 *   package.
 *   - \ref QExtLogManager::startup() "QExtLogManager::startup()"
 *
 *
 * Environment variables are read during static initialisation on creation of
 * the \ref QExtLogInitialisationHelper "QExtLogInitialisationHelper". They can be
 * accessed by calling \ref QExtLogInitialisationHelper::environmentSettings()
 * "QExtLogInitialisationHelper::environmentSettings()".
 *
 * All settings can also be made in the application settings under the group
 * \c %Log4Qt. For example the environment variable \c QEXT_DEBUG is
 * equivalent to the setting \c Debug. If an environment variable is
 * set it takes precedence over the application setting. Settings are only
 * used, if an QApplication object is available, when the
 * \ref QExtLogManager "QExtLogManager" is
 * initialised (see \ref QExtLogInitialisationHelper::setting()
 * "QExtLogInitialisationHelper::setting()" for details).
 */

/*!
 * \page Undocumented Undocumented functions
 *
 * In general it was tried to avoid the usage of undocumented features of Qt.
 * Nice to have features like for example Q_DECLARE_PRIVATE are not used. Only
 * features that would have been resulted in re-coding the same functionality
 * are used.
 *
 * - QT_WA: The macro is used to call Windows A/W functions
 *    - \ref QExtLogDebugAppender "QExtLogDebugAppender"
 */

/*!
 * \page Assumptions Assumptions
 *
 * The following assumptions are used throughout the package:
 *
 * - Reading / writing of bool or int is thread-safe, if declared volatile
 *   - \ref QExtLogListAppender "QExtLogListAppender"
 *   - \ref QExtLogAppenderSkeleton "QExtLogAppenderSkeleton"
 *   - \ref QExtLogConsoleAppender "QExtLogConsoleAppender"
 *   - \ref QExtLogFileAppender "QExtLogFileAppender"
 *   - \ref QExtLogHierarchy "QExtLogHierarchy"
 *   - \ref QExtLogLevel "QExtLogLevel"
 *   - \ref QExtLogger "QExtLogger"
 *   - \ref QExtLogWriterAppender "QExtLogWriterAppender"
 * - \ref QExtLogLayout::format() "QExtLogLayout::format()" is implemented reentrant
 *   in all sub-classes.
 *   - \ref QExtLogAppenderSkeleton "QExtLogAppenderSkeleton"
 * - Being able to use singleton objects during static de-initialization without
 *   order issues is more valuable then their destruction.
 *   - \ref QExtLogManager "QExtLogManager"
 *   - \ref QEXT_IMPLEMENT_INSTANCE "QEXT_IMPLEMENT_INSTANCE"
 */


#endif //_QEXTLOGGING_H
