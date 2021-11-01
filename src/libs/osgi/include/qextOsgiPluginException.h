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

#ifndef QTKPLUGINEXCEPTION_H
#define QTKPLUGINEXCEPTION_H

#include "qtkpluginframework_global.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginException class
 * A Plugin Framework exception used to indicate that a plugin lifecycle
 * problem occurred.
 *
 * <p>
 * A <code>QTKPluginException</code> object is created by the Framework to denote
 * an exception condition in the lifecycle of a plugin.
 * <code>QTKPluginException</code>s should not be created by plugin developers.
 * An enum type is used to identify the exception type for future extendability.
 *
 * <p>
 * This exception conforms to the general purpose exception chaining mechanism.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginException : public QTKRuntimeException
{
public:
    enum Type {
        /**
         * No exception type is unspecified.
         */
        Type_Unspecified,
        /**
         * The operation was unsupported.
         */
        Type_UnsupportedOperation,
        /**
         * The operation was invalid.
         */
        Type_InvalidOperation,
        /**
         * The plugin manifest contains errors.
         */
        Type_ManifestError,
        /**
         * The plugin was not resolved.
         */
        Type_ResolveError,
        /**
         * The plugin activator was in error.
         */
        Type_ActivatorError,
        /**
         * The operation failed due to insufficient permissions.
         */
        Type_SecurityError,
        /**
         * The operation failed to complete the requested lifecycle state change.
         */
        Type_StateChangeError,
        /**
         * The install or update operation failed because another
         * already installed plugin has the same symbolic name and version.
         */
        Type_DuplicatePluginError,
        /**
         * The framework received an error while reading the input stream for a plugin.
         */
        Type_ReadError,
        /**
         * The start transient operation failed because the start level of the
         * plugin is greater than the current framework start level
         */
        Type_StartTransientError
    };

    /**
     * @brief QTKPluginException
     * Creates a <code>QTKPluginException</code> with the specified message and type.
     *
     * @param strMsg The associated message.
     * @param eType The type for this exception.
     */
    QTKPluginException(const QString &strMsg, const Type &eType = Type_Unspecified);

    /**
     * @brief QTKPluginException
     * Creates a <code>QTKPluginException</code> with the specified message, type
     * and exception cause.
     *
     * @param strMsg The associated message.
     * @param eType The type for this exception.
     * @param cause The cause of this exception.
     */
    QTKPluginException(const QString &strMsg, const Type &eType, const QTKException &cause);

    /**
     * @brief QTKPluginException
     * Creates a <code>QTKPluginException</code> with the specified message and
     * exception cause.
     *
     * @param strMsg The associated message.
     * @param cause The cause of this exception.
     */
    QTKPluginException(const QString &strMsg, const QTKException &cause);
    QTKPluginException(const QTKPluginException &other);
    ~QTKPluginException() throw();

    QTKPluginException& operator=(const QTKPluginException &other);

    /**
     * @brief name
     * @return
     * @see QTKException::name()
     */
    const char* name() const throw();

    /**
     * @brief clone
     * @return
     * @see QTKException::clone()
     */
    QTKPluginException* clone() const;

    /**
     * @brief rethrow
     * @see QTKException::rethrow()
     */
    void rethrow() const;

    /**
     * @brief getType
     * @return
     * Returns the type for this exception or <code>Type_Unspecified</code> if the
     * type was unspecified or unknown.
     *
     * @return The type of this exception.
     */
    Type getType() const;

private:
    /**
     * @brief m_eType
     * Type of plugin exception.
     */
    Type m_eType;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINEXCEPTION_H
