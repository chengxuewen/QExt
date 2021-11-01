/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#ifndef QTKLOGSERVICE_H
#define QTKLOGSERVICE_H

#include "../../qtkpluginframework_global.h"
#include "../../qtkservicereference.h"
#include "qtklogstream.h"

#include <QString>

#include <stdexcept>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKLogService class
 * Provides methods for plugins to write messages to the log.
 *
 * <p>
 * <code>ctkLogService</code> methods are provided to log messages; optionally with a
 * <code>ctkServiceReference</code> object or an exception.
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
class QTK_PLUGINFRAMEWORK_EXPORT QTKLogService
{
public:
    virtual ~QTKLogService() {}

    /**
     * @brief LOG_ERROR
     * An error message (Value 1).
     *
     * <p>
     * This log entry indicates the plugin or service may not be functional.
     */
    static const int LOG_ERROR; // = 1;

    /**
     * @brief LOG_WARNING
     * A warning message (Value 2).
     *
     * <p>
     * This log entry indicates a plugin or service is still functioning but may
     * experience problems in the future because of the warning condition.
     */
    static const int LOG_WARNING; // = 2;

    /**
     * @brief LOG_INFO
     * An informational message (Value 3).
     *
     * <p>
     * This log entry may be the result of any change in the plugin or service
     * and does not indicate a problem.
     */
    static const int LOG_INFO; // = 3;

    /**
     * @brief LOG_DEBUG
     * A debugging message (Value 4).
     *
     * <p>
     * This log entry is used for problem determination and may be irrelevant to
     * anyone but the plugin developer.
     */
    static const int LOG_DEBUG; // = 4;

    /**
     * @brief log
     * Logs a message.
     *
     * <p>
     * The <code>ctkServiceReference</code> field and the <code>Exception</code> field
     * of the <code>ctkLogEntry</code> object will be set to <code>null</code>.
     *
     * \param iLevel The severity of the message. This should be one of the
     *        defined log levels but may be any integer that is interpreted in a
     *        user defined way.
     * \param strMessage Human readable string describing the condition.
     * \param pException The exception that reflects the condition or <code>null</code>.
     * \param pcFile The current file name.
     * \param pcFunction The current function name.
     * \param iLine The current line number.
     *
     * \see #LOG_ERROR
     * \see #LOG_WARNING
     * \see #LOG_INFO
     * \see #LOG_DEBUG
     */
    virtual void log(int iLevel, const QString &strMessage, const std::exception *pException = nullptr,
                     const char *pcFile = nullptr, const char *pcFunction = nullptr, int iLine = -1) = 0;

    /**
     * @brief log
     * Logs a message associated with a specific <code>ctkServiceReference</code>
     * object.
     *
     * <p>
     * The <code>Exception</code> field of the <code>ctkLogEntry</code> will be set to
     * <code>null</code>.
     *
     * \param serviceRef The <code>ctkServiceReference</code> object of the service that this
     *        message is associated with.
     * \param iLevel The severity of the message. This should be one of the
     *        defined log levels but may be any integer that is interpreted in a
     *        user defined way.
     * \param strMessage Human readable string describing the condition.
     * \param pException The exception that reflects the condition or
     *        <code>null</code>.
     * \param pcFile The current file name.
     * \param pcFunction The current function name.
     * \param iLine The current line number.
     *
     * \see #LOG_ERROR
     * \see #LOG_WARNING
     * \see #LOG_INFO
     * \see #LOG_DEBUG
     */
    virtual void log(const QTKServiceReference &serviceRef, int iLevel, const QString &strMessage,
                     const std::exception *pException = nullptr,
                     const char *pcFile = nullptr, const char *pcFunction = nullptr, int iLine = -1) = 0;

    /**
     * @brief getLogLevel
     * Get the current log level. The log service discards log entries with a
     * level that is less severe than the current level. E.g. if the current
     * log level is LOG_WARNING then the log service will discard all log entries with
     * level LOG_INFO and LOG_DEBUG.
     *
     * \return The lowest severity level that is accepted into the log.
     */
    virtual int getLogLevel() const = 0;

};

/**
 * @brief The QTKLogStreamWithServiceRef class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKLogStreamWithServiceRef : public QTKLogStream
{
public:
    QTKLogStreamWithServiceRef(QTKLogService *bLogService, const QTKServiceReference &serviceRef,
                               int iLevel, const std::exception *pExc = nullptr,
                               const char *pFile = nullptr, const char *pFunction = nullptr, int iLine = -1);
    QTKLogStreamWithServiceRef(const QTKLogStreamWithServiceRef &logStreamWithRef);

    ~QTKLogStreamWithServiceRef();

protected:
    QTKServiceReference m_serviceRef;
};

/**
 * @brief The QTKNullLogStream class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKNullLogStream : public QTKLogStream
{
public:
    QTKNullLogStream();
    ~QTKNullLogStream();
};

#define QTK_DEBUG(logService) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_DEBUG) ? \
    QTKLogStream(logService, QTKLogService::LOG_DEBUG, 0, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_DEBUG_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_DEBUG) ? \
    QTKLogStream(logService, QTKLogService::LOG_DEBUG, exc, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_DEBUG_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_DEBUG) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_DEBUG, 0, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

#define QTK_DEBUG_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_DEBUG) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_DEBUG, exc, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

#define QTK_INFO(logService) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_INFO) ? \
    QTKLogStream(logService, QTKLogService::LOG_INFO, 0, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_INFO_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_INFO) ? \
    QTKLogStream(logService, QTKLogService::LOG_INFO, exc, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_INFO_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_INFO) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_INFO, 0, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

#define QTK_INFO_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_INFO) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_INFO, exc, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

#define QTK_WARN(logService) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_WARNING) ? \
    QTKLogStream(logService, QTKLogService::LOG_WARNING, 0, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_WARN_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_WARNING) ? \
    QTKLogStream(logService, QTKLogService::LOG_WARNING, exc, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_WARN_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_WARNING) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_WARNING, 0, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

#define QTK_WARN_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_WARNING) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_WARNING, exc, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

#define QTK_ERROR(logService) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_ERROR) ? \
    QTKLogStream(logService, QTKLogService::LOG_ERROR, 0, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_ERROR_EXC(logService, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_ERROR) ? \
    QTKLogStream(logService, QTKLogService::LOG_ERROR, exc, __FILE__, __FUNCTION__, __LINE__) : \
    QTKNullLogStream())

#define QTK_ERROR_SR(logService, serviceRef) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_ERRO) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_ERROR, 0, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

#define QTK_ERROR_SR_EXC(logService, serviceRef, exc) \
    ((logService && logService->getLogLevel() >= QTKLogService::LOG_ERROR) ? \
    static_cast<QTKLogStream>(QTKLogStreamWithServiceRef(logService, serviceRef, QTKLogService::LOG_ERROR, exc, __FILE__, __FUNCTION__, __LINE__)) : \
    static_cast<QTKLogStream>(QTKNullLogStream()))

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogService,
                    "org.qtk.service.log.LogService")

#endif // QTKLOGSERVICE_H
