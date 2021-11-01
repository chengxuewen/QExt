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

#ifndef QTKPLUGINFRAMEWORKDEBUG_P_H
#define QTKPLUGINFRAMEWORKDEBUG_P_H

#include "qtkpluginframework_global.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkDebug struct
 * Variables that control debugging of the pluginfw code.
 */
struct QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkDebug
{
public:
    QTKPluginFrameworkDebug();

    /**
     * @brief OPTION_DEBUG_GENERAL
     */
    static const QString OPTION_DEBUG_GENERAL;
    bool bGeneralEnabled;

    /**
     * @brief OPTION_DEBUG_ERRORS
     * Report error handling events.
     */
    static const QString OPTION_DEBUG_ERRORS;
    bool bErrorsEnabled;

    /**
     * @brief OPTION_DEBUG_FRAMEWORK
     * Report pluginfw create, init, start, stop
     */
    static const QString OPTION_DEBUG_FRAMEWORK;
    bool bFrameworkEnabled;

    /**
     * @brief OPTION_DEBUG_HOOKS
     * Report hooks handling
     */
    static const QString OPTION_DEBUG_HOOKS;
    bool bHooksEnabled;

    /**
     * @brief OPTION_DEBUG_LAZY_ACTIVATION
     * Report triggering of lazy activation
     */
    static const QString OPTION_DEBUG_LAZY_ACTIVATION;
    bool bLazyActivationEnabled;

    /**
     * @brief OPTION_DEBUG_LDAP
     * Report LDAP handling
     */
    static const QString OPTION_DEBUG_LDAP;
    bool bLdapEnabled;

    /**
     * @brief OPTION_DEBUG_SERVICE_REFERENCE
     * Print information about service reference lookups
     * and rejections due to missing permissions
     * for calling plug-ins.
     */
    static const QString OPTION_DEBUG_SERVICE_REFERENCE;
    bool bServiceReferenceEnabled;

    /**
     * @brief OPTION_DEBUG_STARTLEVEL
     * Report startlevel.
     */
    static const QString OPTION_DEBUG_STARTLEVEL;
    bool bStartLevelEnabled;

    /**
     * @brief OPTION_DEBUG_URL
     * Report url
     */
    static const QString OPTION_DEBUG_URL;
    bool bUrlEnabled;

    /**
     * @brief OPTION_DEBUG_RESOLVE
     * Report plug-in resolve progress
     */
    static const QString OPTION_DEBUG_RESOLVE;
    bool bResolveEnabled;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKDEBUG_P_H
