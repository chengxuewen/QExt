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

#ifndef QTKPLUGINFRAMEWORKCONTEXT_P_H
#define QTKPLUGINFRAMEWORKCONTEXT_P_H

#include "qtkpluginframeworkfactory.h"
#include "qtkpluginframework.h"
#include "qtkpluginstorage_p.h"
#include "qtkplugins_p.h"
#include "qtkpluginframeworklisteners_p.h"
#include "qtkpluginframeworkdebug_p.h"

#include <QDebug>
#include <QMutex>
#include <QDir>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPlugin;
class QTKPluginStorage;
class QTKServices;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkContext class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkContext
{
public:
    /**
     * @brief QTKPluginFrameworkContext
     * Contruct a framework context
     */
    QTKPluginFrameworkContext();
    ~QTKPluginFrameworkContext();

    /**
     * @brief init
     * Initialize the framework
     */
    void init();

    /**
     * @brief uninit
     * Undo as much as possible of what init() does.
     */
    void uninit();
    int getId() const;

    /**
     * @brief getDataStorage
     * Get private plugin data storage file handle
     *
     * @param lId
     * @return
     */
    QFileInfo getDataStorage(long lId);

    /**
     * @brief checkOurPlugin
     * Check that the plugin belongs to this framework instance.
     *
     * @param pPlugin
     */
    void checkOurPlugin(QTKPlugin *pPlugin) const;

    /**
     * @brief resolvePlugin
     * Check that the plugin specified can resolve all its
     * Require-QTKPlugin constraints.
     *
     * @param pPlugin QTKPlugin to check, must be in INSTALLED state
     *
     * @throws QTKPluginException
     */
    void resolvePlugin(QTKPluginPrivate *pPlugin);

    /**
     * @brief log
     * Log message for debugging framework
     *
     * @return
     */
    QDebug log() const;

    /**
     * @brief sm_globalFWLock
     * global lock.
     */
    static QMutex sm_globalFWLock;

    /**
     * @brief sm_iGlobalId
     * // Id to use for next instance of plugin framework.
     */
    static int sm_iGlobalId;

    /**
     * @brief m_pPlugins
     * All plugins in this framework.
     */
    QTKPlugins *m_pPlugins;

    /**
     * @brief m_listeners
     * All listeners in this framework.
     */
    QTKPluginFrameworkListeners m_listeners;

    /**
     * @brief m_pServices
     * All registered services in this framework.
     */
    QTKServices *m_pServices;

    /**
     * @brief m_pRunTimePlugin
     * System plugin
     */
    QSharedPointer<QTKPluginFramework> m_pRunTimePlugin;

    /**
     * @brief m_pStorage
     * QTKPlugin storage
     */
    QTKPluginStorage *m_pStorage;

    /**
     * @brief m_dataStorage
     * Private Plugin data storage
     */
    QDir m_dataStorage;

    /**
     * @brief m_bFirstInit
     * First framework init
     */
    bool m_bFirstInit;

    /**
     * @brief m_iId
     * Framework id.
     */
    int m_iId;
    QTKProperties &m_properties;

    /**
     * @brief m_debug
     * Debug handle.
     */
    QTKPluginFrameworkDebug m_debug;

private:
    /**
     * @brief deleteFWDir
     * Delete framework directory if it exists.
     */
    void deleteFWDir();
    void checkRequirePlugin(QTKPluginPrivate *pPlugin);
    void initProperties();

    QSet<QTKPluginPrivate *> m_tempResolved;
    bool m_bInitialized = false;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKCONTEXT_P_H
