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


#include <private/qextOsgiPluginFrameworkDebug_p.h>
#include <private/qextOsgiPluginFrameworkProperties_p.h>
#include <private/qextOsgiPluginFrameworkDebugOptions_p.h>

static QString QEXT_OSGI_OSGI = "org.qext.pluginfw";

QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_GENERAL = QEXT_OSGI_OSGI + "/debug";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_FRAMEWORK = QEXT_OSGI_OSGI + "/debug/framework";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_ERRORS = QEXT_OSGI_OSGI + "/debug/errors";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_HOOKS = QEXT_OSGI_OSGI + "/debug/hooks";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_LAZY_ACTIVATION = QEXT_OSGI_OSGI + "/debug/lazy_activation";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_LDAP = QEXT_OSGI_OSGI + "/debug/ldap";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_SERVICE_REFERENCE = QEXT_OSGI_OSGI + "/debug/service_reference";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_STARTLEVEL = QEXT_OSGI_OSGI + "/debug/startlevel";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_URL = QEXT_OSGI_OSGI + "/debug/url";
QString QExtOsgiPluginFrameworkDebug::OPTION_DEBUG_RESOLVE = QEXT_OSGI_OSGI + "/debug/resolve";

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkDebug::QExtOsgiPluginFrameworkDebug()
{
    QExtOsgiPluginFrameworkDebugOptions* dbgOptions = QExtOsgiPluginFrameworkDebugOptions::getDefault();
    if (dbgOptions != NULL)
    {
        enabled = dbgOptions->isDebugEnabled();
        errors = dbgOptions->getBooleanOption(OPTION_DEBUG_ERRORS, false);
        framework = dbgOptions->getBooleanOption(OPTION_DEBUG_FRAMEWORK, false);
        hooks = dbgOptions->getBooleanOption(OPTION_DEBUG_HOOKS, false);
        lazy_activation = dbgOptions->getBooleanOption(OPTION_DEBUG_LAZY_ACTIVATION, false);
        ldap = dbgOptions->getBooleanOption(OPTION_DEBUG_LDAP, false);
        service_reference = dbgOptions->getBooleanOption(OPTION_DEBUG_SERVICE_REFERENCE, false);
        startlevel = dbgOptions->getBooleanOption(OPTION_DEBUG_STARTLEVEL, false);
        url = dbgOptions->getBooleanOption(OPTION_DEBUG_URL, false);
        resolve = dbgOptions->getBooleanOption(OPTION_DEBUG_RESOLVE, false);
    }
}
