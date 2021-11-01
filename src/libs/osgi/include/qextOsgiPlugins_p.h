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

#ifndef QTKPLUGINS_P_H
#define QTKPLUGINS_P_H

#include "qtkpluginframework_global.h"

#include <QUrl>
#include <QHash>
#include <QReadWriteLock>
#include <QMutex>
#include <QIODevice>
#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
class QTKPluginFrameworkContext;
class QTKVersion;
class QTKVersionRange;

/**
 * @brief The QTKPlugins class
 * Here we handle all the plugins that are installed in the framework.
 * Also handles load and save of bundle states to a database, so that we
 * can restart the platform.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPlugins
{
public:
    /**
     * @brief QTKPlugins
     * Create a container for all plugins in this framework.
     *
     * @param pPFWContext
     */
    QTKPlugins(QTKPluginFrameworkContext *pPFWContext);
    ~QTKPlugins();

    /**
     * @brief install
     * Install a new plugin.
     *
     * @param location The location to be installed
     */
    QSharedPointer<QTKPlugin> install(const QUrl &location, QIODevice *pIn);

    /**
     * @brief remove
     * Remove plugin registration.
     *
     * @param location The location to be removed
     */
    void remove(const QUrl &location);

    /**
     * @brief getPlugin
     * Get the plugin that has the specified plugin identifier.
     *
     * @param iId The identifier of the plugin to get.
     * @return QTKPlugin or null, if the plugin was not found.
     */
    QSharedPointer<QTKPlugin> getPlugin(int iId) const;

    /**
     * @brief getPlugin
     * Get the plugin that has specified plugin location.
     *
     * @param strLocation The location of the plugin to get.
     * @return QTKPlugin or null, if the plugin was not found.
     */
    QSharedPointer<QTKPlugin> getPlugin(const QString &strLocation) const;

    /**
     * @brief getPlugin
     * Get the plugin that has specified plugin symbolic name and version.
     *
     * @param name The symbolic name of the plugin to get.
     * @param version The plugin version of the plugin to get.
     * @return QTKPlugin or null.
     */
    QSharedPointer<QTKPlugin> getPlugin(const QString &strName, const QTKVersion &version) const;

    /**
     * @brief getPlugins
     * Get all installed plugins.
     *
     * @return A QTKPlugin list with plugins.
     */
    QList<QSharedPointer<QTKPlugin> > getPlugins() const;

    /**
     * @brief getPlugins
     * Get all plugins that have specified plugin symbolic name.
     *
     * @param strName The symbolic name of plugins to get.
     * @return A list of QTKPlugins.
     */
    QList<QTKPlugin*> getPlugins(const QString &strName) const;

    /**
     * @brief getPlugins
     * Get all plugins that have specified plugin symbolic name and
     * version range. Result is sorted in decreasing version order.
     *
     * @param strName The symbolic name of plugins to get.
     * @param range QTKVersion range of plugins to get.
     * @return A List of QTKPlugins.
     */
    QList<QTKPlugin*> getPlugins(const QString &strName, const QTKVersionRange &range) const;

    /**
     * @brief getActivePlugins
     * Get all plugins currently in plugin state ACTIVE.
     *
     * @return A List of QTKPlugins.
     */
    QList<QSharedPointer<QTKPlugin> > getActivePlugins() const;

    /**
     * @brief load
     * Try to load any saved framework state.
     * This is done by installing all saved plugins and restoring
     * the saved state for each plugin. This is only
     * intended to be executed during the start of the framework.
     *
     */
    void load();

    /**
     * @brief startPlugins
     * Start a list of plugins in order
     *
     * @param listPlugins QTKPlugins to start.
     */
    void startPlugins(const QList<QTKPlugin*> &listPlugins) const;

private:
    void checkIllegalState() const;

    /**
     * @brief m_mapLocationToPlugin
     * Table of all installed plugins in this framework.
     * Key is the plugin location.
     */
    QHash<QString, QSharedPointer<QTKPlugin> > m_mapLocationToPlugin;

    /**
     * @brief m_pPFWContext
     * Link to framework object.
     */
    QTKPluginFrameworkContext *m_pPFWContext;

    /**
     * @brief m_pluginsLock
     * Read write lock for protecting the plugins object
     */
    mutable QReadWriteLock m_pluginsLock;

    /**
     * @brief m_objectLock
     * Lock for protecting this object.
     */
    QMutex m_objectLock;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINS_P_H
