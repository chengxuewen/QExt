/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#ifndef CTKLOGSERVICE_H
#define CTKLOGSERVICE_H

#include <qextOsgiServiceReference.h>
#include <qextOsgiLogStream.h>

#include <QString>
#include <stdexcept>


/**
 * \ingroup LogService
 * Provides methods for plugins to write messages to the log.
 *
 * <p>
 * <code>QExtOsgiLogService</code> methods are provided to log messages; optionally with a
 * <code>QExtOsgiServiceReference</code> object or an exception.
 *
 * <p>
 * Plugins must log messages in the Plugin Framework with a severity level
 * according to the following hierarchy:
 * <ol>
 * <li>#LOG_ERROR
 * <li>#LOG_WARNING
 * <li>#LOG_INFO
 * <li>#LOG_DEBUG
 * </ol>
 *
 * \remarks This class is thread safe.
 */
struct QEXT_OSGI_API QExtOsgiLogService
{

    virtual ~QExtOsgiLogService() {}


    /**
   * An error message (Value 1).
   *
   * <p>
   * This log entry indicates the plugin or service may not be functional.
   */
    static const int LOG_ERROR; // = 1;

    /**
   * A warning message (Value 2).
   *
   * <p>
   * This log entry indicates a plugin or service is still functioning but may
   * experience problems in the future because of the warning condition.
   */
    static const int LOG_WARNING; // = 2;

    /**
   * An informational message (Value 3).
   *
   * <p>
   * This log entry may be the result of any change in the plugin or service
   * and does not indicate a problem.
   */
    static const int LOG_INFO; // = 3;

    /**
   * A debugging message (Value 4).
   *
   * <p>
   * This log entry is used for problem determination and may be irrelevant to
   * anyone but the plugin developer.
   */
    static const int LOG_DEBUG; // = 4;

    /**
   * Logs a message.
   *
   * <p>
   * The <code>QExtOsgiServiceReference</code> field and the <code>Exception</code> field
   * of the <code>QExtOsgiLogEntry</code> object will be set to <code>null</code>.
   *
   * \param level The severity of the message. This should be one of the
   *        defined log levels but may be any integer that is interpreted in a
   *        user defined way.
   * \param message Human readable string describing the condition.
   * \param exception The exception that reflects the condition or <code>null</code>.
   * \param file The current file name.
   * \param function The current function name.
   * \param line The current line number.
   *
   * \see #LOG_ERROR
   * \see #LOG_WARNING
   * \see #LOG_INFO
   * \see #LOG_DEBUG
   */
    virtual void log(int level, const QString &message, const std::exception* exception = 0,
                     const char *file = 0, const char *function = 0, int line = -1) = 0;

    /**
   * Logs a message associated with a specific <code>QExtOsgiServiceReference</code>
   * object.
   *
   * <p>
   * The <code>Exception</code> field of the <code>QExtOsgiLogEntry</code> will be set to
   * <code>null</code>.
   *
   * \param sr The <code>QExtOsgiServiceReference</code> object of the service that this
   *        message is associated with.
   * \param level The severity of the message. This should be one of the
   *        defined log levels but may be any integer that is interpreted in a
   *        user defined way.
   * \param message Human readable string describing the condition.
   * \param exception The exception that reflects the condition or
   *        <code>null</code>.
   * \param file The current file name.
   * \param function The current function name.
   * \param line The current line number.
   *
   * \see #LOG_ERROR
   * \see #LOG_WARNING
   * \see #LOG_INFO
   * \see #LOG_DEBUG
   */
    virtual void log(const QExtOsgiServiceReference &sr, int level, const QString &message,
                     const std::exception* exception = 0,
                     const char *file = 0, const char *function = 0, int line = -1) = 0;

    /**
   * Get the current log level. The log service discards log entries with a
   * level that is less severe than the current level. E.g. if the current
   * log level is LOG_WARNING then the log service will discard all log entries with
   * level LOG_INFO and LOG_DEBUG.
   *
   * \return The lowest severity level that is accepted into the log.
   */
    virtual int getLogLevel() const = 0;

};

Q_DECLARE_INTERFACE(QExtOsgiLogService, "org.qext.service.log.LogService")

/**
 * \ingroup LogService
 */
class QEXT_OSGI_API QExtOsgiLogStreamWithServiceRef : public QExtOsgiLogStream
{
public:

    QExtOsgiLogStreamWithServiceRef(QExtOsgiLogService *logService, const QExtOsgiServiceReference &sr,
                                    int level, const std::exception* exc = 0,
                                    const char *file = 0, const char *function = 0, int line = -1);
    QExtOsgiLogStreamWithServiceRef(const QExtOsgiLogStreamWithServiceRef& logStreamWithRef);

    ~QExtOsgiLogStreamWithServiceRef();

protected:

    QExtOsgiServiceReference sr;
};

/**
 * \ingroup LogService
 */
class QEXT_OSGI_API QExtOsgiNullLogStream : public QExtOsgiLogStream
{
public:

    QExtOsgiNullLogStream();
    ~QExtOsgiNullLogStream();

};

/**
 * \ingroup LogService
 * @{
 */

#define QEXT_OSGI_DEBUG(logService) \
((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_DEBUG) ? \
     QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_DEBUG, 0, __FILE__, __FUNCTION__, __LINE__) : \
     QExtOsgiNullLogStream())

#define QEXT_OSGI_DEBUG_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_DEBUG) ? \
         QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_DEBUG, exc, __FILE__, __FUNCTION__, __LINE__) : \
         QExtOsgiNullLogStream())

#define QEXT_OSGI_DEBUG_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_DEBUG) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_DEBUG, 0, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

#define QEXT_OSGI_DEBUG_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_DEBUG) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_DEBUG, exc, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

#define QEXT_OSGI_INFO(logService) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_INFO) ? \
         QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_INFO, 0, __FILE__, __FUNCTION__, __LINE__) : \
         QExtOsgiNullLogStream())

#define QEXT_OSGI_INFO_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_INFO) ? \
         QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_INFO, exc, __FILE__, __FUNCTION__, __LINE__) : \
         QExtOsgiNullLogStream())

#define QEXT_OSGI_INFO_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_INFO) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_INFO, 0, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

#define QEXT_OSGI_INFO_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_INFO) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_INFO, exc, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

#define QEXT_OSGI_WARN(logService) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_WARNING) ? \
         QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_WARNING, 0, __FILE__, __FUNCTION__, __LINE__) : \
         QExtOsgiNullLogStream())

#define QEXT_OSGI_WARN_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_WARNING) ? \
         QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_WARNING, exc, __FILE__, __FUNCTION__, __LINE__) : \
         QExtOsgiNullLogStream())

#define QEXT_OSGI_WARN_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_WARNING) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_WARNING, 0, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

#define QEXT_OSGI_WARN_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_WARNING) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_WARNING, exc, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

#define QEXT_OSGI_ERROR(logService) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_ERROR) ? \
         QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_ERROR, 0, __FILE__, __FUNCTION__, __LINE__) : \
         QExtOsgiNullLogStream())

#define QEXT_OSGI_ERROR_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_ERROR) ? \
         QExtOsgiLogStream(logService, QExtOsgiLogService::LOG_ERROR, exc, __FILE__, __FUNCTION__, __LINE__) : \
         QExtOsgiNullLogStream())

#define QEXT_OSGI_ERROR_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_ERRO) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_ERROR, 0, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

#define QEXT_OSGI_ERROR_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QExtOsgiLogService::LOG_ERROR) ? \
         static_cast<QExtOsgiLogStream>(QExtOsgiLogStreamWithServiceRef(logService, serviceRef, QExtOsgiLogService::LOG_ERROR, exc, __FILE__, __FUNCTION__, __LINE__)) : \
         static_cast<QExtOsgiLogStream>(QExtOsgiNullLogStream()))

/** @}*/

#endif // CTKLOGSERVICE_H
