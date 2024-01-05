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


#ifndef _QEXTOSGICONFIGURATIONEXCEPTION_H
#define _QEXTOSGICONFIGURATIONEXCEPTION_H

#include <qextException.h>
#include <qextOsgiPluginFrameworkEvent.h>

/**
 * \ingroup ConfigAdmin
 *
 * An exception class to inform the Configuration Admin service
 * of problems with configuration data.
 */
class QEXT_OSGI_API QExtOsgiConfigurationException : public QExtRuntimeException
{

public:

    /**
   * Create a <code>QExtOsgiConfigurationException</code> object.
   *
   * @param property name of the property that caused the problem,
   *        <code>null</code> if no specific property was the cause
   * @param reason reason for failure
   */
    QExtOsgiConfigurationException(const QString& property, const QString& reason);

    /**
   * Create a <code>QExtOsgiConfigurationException</code> object.
   *
   * @param property name of the property that caused the problem,
   *        <code>null</code> if no specific property was the cause
   * @param reason reason for failure
   * @param cause The cause of this exception.
   */
    QExtOsgiConfigurationException(const QString& property, const QString& reason,
                              const QExtException& cause);

    QExtOsgiConfigurationException(const QExtOsgiConfigurationException& o);
    QExtOsgiConfigurationException& operator=(const QExtOsgiConfigurationException& o);

    ~QExtOsgiConfigurationException() throw();

    /**
   * @see QExtException::name()
   */
    const char* name() const throw();

    /**
   * @see QExtException::clone()
   */
    QExtOsgiConfigurationException* clone() const;

    /**
   * @see QExtException::rethrow()
   */
    void rethrow() const;

    /**
   * Return the property name that caused the failure or a null QString.
   *
   * @return name of property or null if no specific property caused the
   *         problem
   */
    QString getProperty() const;

    /**
   * Return the reason for this exception.
   *
   * @return reason of the failure
   */
    QString getReason() const;

private:

    QString property;
    QString reason;
};

/**
 * \ingroup ConfigAdmin
 */

QEXT_OSGI_API QDebug operator<<(QDebug dbg, const QExtOsgiConfigurationException& exc);

/** @}*/

#endif // _QEXTOSGICONFIGURATIONEXCEPTION_H
