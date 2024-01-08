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


#ifndef _QEXTOSGISERVICEEXCEPTION_H
#define _QEXTOSGISERVICEEXCEPTION_H

#include <qextOsgiGlobal.h>
#include <qextException.h>

/**
 * \ingroup PluginFramework
 *
 * A service exception used to indicate that a service problem occurred.
 *
 * <p>
 * A <code>QExtOsgiServiceException</code> object is created by the Framework or
 * to denote an exception condition in the service. An enum
 * type is used to identify the exception type for future extendibility.
 *
 * <p>
 * This exception conforms to the general purpose exception chaining mechanism.
 */
class QEXT_OSGI_API QExtOsgiServiceException : public QExtRuntimeException
{
public:

    enum Type {
        /**
     * No exception type is unspecified.
     */
        UNSPECIFIED = 0,
        /**
     * The service has been unregistered.
     */
        UNREGISTERED = 1,
        /**
     * The service factory produced an invalid service object.
     */
        FACTORY_ERROR = 2,
        /**
     * The service factory threw an exception.
     */
        FACTORY_EXCEPTION = 3,
        /**
     * An error occurred invoking a remote service.
     */
        REMOTE = 5,
        /**
     * The service factory resulted in a recursive call to itself for the
     * requesting plugin.
     */
        FACTORY_RECURSION = 6
    };

    /**
   * Creates a <code>QExtOsgiServiceException</code> with the specified message and
   * type.
   *
   * @param msg The associated message.
   * @param type The type for this exception.
   */
    QExtOsgiServiceException(const QString &msg, const Type& type = UNSPECIFIED);

    /**
   * Creates a <code>QExtOsgiServiceException</code> with the specified message,
   * type and exception cause.
   *
   * @param msg The associated message.
   * @param type The type for this exception.
   * @param cause The cause of this exception.
   */
    QExtOsgiServiceException(const QString &msg, const Type& type, const QExtException& cause);

    /**
   * Creates a <code>QExtOsgiServiceException</code> with the specified message and
   * exception cause.
   *
   * @param msg The associated message.
   * @param cause The cause of this exception.
   */
    QExtOsgiServiceException(const QString &msg, const QExtException& cause);

    QExtOsgiServiceException(const QExtOsgiServiceException& o);
    QExtOsgiServiceException& operator=(const QExtOsgiServiceException& o);

    ~QExtOsgiServiceException() throw();

    /**
   * @see QExtException::name()
   */
    const char *name() const throw();

    /**
   * @see QExtException::clone()
   */
    QExtOsgiServiceException* clone() const;

    /**
   * @see QExtException::rethrow()
   */
    void rethrow() const;

    /**
   * Returns the type for this exception or <code>UNSPECIFIED</code> if the
   * type was unspecified or unknown.
   *
   * @return The type of this exception.
   */
    Type getType() const;

private:

    /**
   * Type of service exception.
   */
    Type type;

};

#endif // _QEXTOSGISERVICEEXCEPTION_H
