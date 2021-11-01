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

#ifndef QTKCONFIGURATIONEXCEPTION_H
#define QTKCONFIGURATIONEXCEPTION_H

#include "../../qtkpluginframeworkevent.h"
#include "../../qtkpluginframework_global.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKConfigurationException class
 * An exception class to inform the Configuration Admin service
 * of problems with configuration data.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKConfigurationException : public QTKRuntimeException
{
public:
    /**
     * @brief QTKConfigurationException
     * Create a <code>ctkConfigurationException</code> object.
     *
     * @param strProperty name of the property that caused the problem,
     *        <code>null</code> if no specific property was the cause
     * @param strReason reason for failure
     */
    QTKConfigurationException(const QString &strProperty, const QString &strReason);

    /**
     * @brief QTKConfigurationException
     * Create a <code>ctkConfigurationException</code> object.
     *
     * @param strProperty name of the property that caused the problem,
     *        <code>null</code> if no specific property was the cause
     * @param strReason reason for failure
     * @param cause The cause of this exception.
     */
    QTKConfigurationException(const QString &strProperty, const QString &strReason,
                              const QTKException &cause);
    QTKConfigurationException(const QTKConfigurationException& o);
    ~QTKConfigurationException() throw();

    /**
     * @brief name
     * @see ctkException::name()
     * @return
     */
    const char *name() const throw();

    /**
     * @brief clone
     * @see ctkException::clone()
     * @return
     */
    QTKConfigurationException *clone() const;

    /**
     * @brief rethrow
     * @see ctkException::rethrow()
     */
    void rethrow() const;

    /**
     * @brief getProperty
     * Return the property name that caused the failure or a null QString.
     *
     * @return name of property or null if no specific property caused the
     *         problem
     */
    QString getProperty() const;

    /**
     * @brief getReason
     * Return the reason for this exception.
     *
     * @return reason of the failure
     */
    QString getReason() const;

    QTKConfigurationException& operator=(const QTKConfigurationException& o);

private:
    QString property;
    QString reason;
};

/**
 * @ingroup QTKPluginFramework
 */
QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug dbg, const QTKConfigurationException& exc);
/** @}*/

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKCONFIGURATIONEXCEPTION_H
