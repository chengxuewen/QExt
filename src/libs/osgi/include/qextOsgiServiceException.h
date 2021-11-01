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

#ifndef QTKSERVICEEXCEPTION_H
#define QTKSERVICEEXCEPTION_H

#include "qtkpluginframework_global.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKServiceException class
 * A service exception used to indicate that a service problem occurred.
 *
 * <p>
 * A <code>QTKServiceException</code> object is created by the Framework or
 * to denote an exception condition in the service. An enum
 * type is used to identify the exception type for future extendability.
 *
 * <p>
 * This exception conforms to the general purpose exception chaining mechanism.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServiceException : public QTKRuntimeException
{
public:
    enum Type {
        /**
         * No exception type is unspecified.
         */
        Type_Unspecified = 0,
        /**
         * The service has been unregistered.
         */
        Type_Unregistered = 1,
        /**
         * The service factory produced an invalid service object.
         */
        Type_FactoryError = 2,
        /**
         * The service factory threw an exception.
         */
        Type_FactoryException = 3,
        /**
         * An error occurred invoking a remote service.
         */
        Type_Remote = 5,
        /**
         * The service factory resulted in a recursive call to itself for the
         * requesting plugin.
         */
        Type_FactoryRecursion = 6
    };

    /**
     * @brief QTKServiceException
     * Creates a <code>QTKServiceException</code> with the specified message and
     * type.
     *
     * @param strMsg The associated message.
     * @param eType The type for this exception.
     */
    QTKServiceException(const QString &strMsg, const Type &eType = Type_Unspecified);

    /**
     * @brief QTKServiceException
     * Creates a <code>QTKServiceException</code> with the specified message,
     * type and exception cause.
     *
     * @param strMsg The associated message.
     * @param eType The type for this exception.
     * @param cause The cause of this exception.
     */
    QTKServiceException(const QString &strMsg, const Type &eType, const QTKException &cause);

    /**
     * @brief QTKServiceException
     * Creates a <code>QTKServiceException</code> with the specified message and
     * exception cause.
     *
     * @param strMsg The associated message.
     * @param cause The cause of this exception.
     */
    QTKServiceException(const QString &strMsg, const QTKException &cause);
    QTKServiceException(const QTKServiceException &other);
    ~QTKServiceException() throw();

    QTKServiceException& operator=(const QTKServiceException &other);

    const char *name() const throw();

    /**
     * @brief clone
     * @see QTKException::clone()
     */
    QTKServiceException *clone() const;

    /**
     * @brief rethrow
     * @see QTKException::rethrow()
     */
    void rethrow() const;

    /**
     * @brief getType
     * Returns the type for this exception or <code>Type_Unspecified</code> if the
     * type was unspecified or unknown.
     *
     * @return The type of this exception.
     */
    Type getType() const;

private:
    /**
     * @brief m_eType
     * Type of service exception.
     */
    Type m_eType;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICEEXCEPTION_H
