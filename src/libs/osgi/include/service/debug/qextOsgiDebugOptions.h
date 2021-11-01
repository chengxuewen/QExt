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

#ifndef QTKDEBUGOPTIONS_H
#define QTKDEBUGOPTIONS_H

#include "../../qtkpluginframework_global.h"

#include <QString>
#include <QHash>
#include <QVariant>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKDebugOptions class
 * Used to get debug options settings.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKDebugOptions
{
public:
    virtual ~QTKDebugOptions() {}

    /**
     * @brief getBooleanOption
     * Returns the identified option as a boolean value. The specified
     * defaultValue is returned if no such option is found or if debug is not enabled.
     *
     * <p>
     * Options are specified in the general form <i>&lt;Plugin-SymbolicName&gt;/&lt;option-path&gt;</i>.
     * For example, <code>org.commontk.configadmin/debug</code>
     * </p>
     *
     * @param option the name of the option to lookup
     * @param defaultValue the value to return if no such option is found
     * @return the value of the requested debug option or the
     * defaultValue if no such option is found.
     */
    virtual bool getBooleanOption(const QString &strOption, bool bDefaultValue) const = 0;

    /**
     * @brief getOption
     * Returns the identified option.  A null value
     * is returned if no such option is found or if debug is not enabled.
     *
     * <p>
     * Options are specified
     * in the general form <i>&lt;Plugin-SymbolicName&gt;/&lt;option-path&gt;</i>.
     * For example, <code>org.commontk.configadmin/debug</code>
     * </p>
     *
     * @param strOption the name of the option to lookup
     * @return the value of the requested debug option or <code>null</code>
     */
    virtual QVariant getOption(const QString &strOption) const = 0;

    /**
     * @brief getOption
     * Returns the identified option. The specified defaultValue is
     * returned if no such option is found or if debug is not enabled.
     *
     * <p>
     * Options are specified
     * in the general form <i>&lt;Plugin-SymbolicName&gt;/&lt;option-path&gt;</i>.
     * For example, <code>org.commontk.configadmin/debug</code>
     * </p>
     *
     * @param strOption the name of the option to lookup
     * @param defaultValue the value to return if no such option is found
     * @return the value of the requested debug option or the
     * defaultValue if no such option is found.
     */
    virtual QVariant getOption(const QString &strOption, const QVariant &defaultValue) const = 0;

    /**
     * @brief getIntegerOption
     * Returns the identified option as an int value. The specified
     * defaultValue is returned if no such option is found or if an
     * error occurs while converting the option value
     * to an integer or if debug is not enabled.
     *
     * <p>
     * Options are specified
     * in the general form <i>&lt;Plugin-SymbolicName&gt;/&lt;option-path&gt;</i>.
     * For example, <code>org.commontk.configadmin/debug</code>
     * </p>
     *
     * @param strOption the name of the option to lookup
     * @param iDefaultValue the value to return if no such option is found
     * @return the value of the requested debug option or the
     * defaultValue if no such option is found.
     */
    virtual int getIntegerOption(const QString &strOption, int iDefaultValue) const = 0;

    /**
     * @brief getOptions
     * Returns a snapshot of the current options.  If no
     * options are set then an empty map is returned.
     * <p>
     * If debug is not enabled then the snapshot of the current disabled
     * values is returned. See setDebugEnabled(bool).
     * </p>
     * @return a snapshot of the current options.
     */
    virtual QHash<QString, QVariant> getOptions() const = 0;

    /**
     * @brief setOption
     * Sets the identified option to the identified value. If debug is
     * not enabled then the specified option is not changed.
     * @param strOption the name of the option to set
     * @param value the value of the option to set
     */
    virtual void setOption(const QString &strOption, const QVariant &value) = 0;

    /**
     * @brief setOptions
     * Sets the current option key/value pairs to the specified options.
     * The specified map replaces all keys and values of the current debug options.
     * <p>
     * If debug is not enabled then the specified options are saved as
     * the disabled values and no notifications will be sent.
     * See setDebugEnabled(bool).
     * If debug is enabled then notifications will be sent to the
     * listeners which have options that have been changed, added or removed.
     * </p>
     *
     * @param options the new set of options
     */
    virtual void setOptions(const QHash<QString, QVariant> &options) = 0;

    /**
     * @brief removeOption
     * Removes the identified option.  If debug is not enabled then
     * the specified option is not removed.
     * @param strOption the name of the option to remove
     */
    virtual void removeOption(const QString &strOption) = 0;

    /**
     * @brief isDebugEnabled
     * Returns true if debugging/tracing is currently enabled.
     * @return true if debugging/tracing is currently enabled;  Otherwise false is returned.
     */
    virtual bool isDebugEnabled() const = 0;

    /**
     * @brief setDebugEnabled
     * Enables or disables debugging/tracing.
     * <p>
     * When debug is disabled all debug options are unset.
     * When disabling debug the current debug option values are
     * stored in memory as disabled values. If debug is re-enabled the
     * disabled values will be set back and enabled.  The disabled values
     * are only stored in memory and if the framework is restarted then
     * the disabled option values will be lost.
     * </p>
     * @param bEnabled If <code>true</code>, debug is enabled, otherwise
     * debug is disabled.
     */
    virtual void setDebugEnabled(bool bEnabled) = 0;

    /**
     * @brief LISTENER_SYMBOLICNAME
     * The service property (named &quot;listener.symbolic.name&quot;) which specifies
     * the bundle symbolic name of a {@link DebugOptionsListener} service.
     */
    static const char *LISTENER_SYMBOLICNAME; // = "listener.symbolic.name";
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKDebugOptions,
                    "org.qtk.service.debug.DebugOptions")

#endif // QTKDEBUGOPTIONS_H
