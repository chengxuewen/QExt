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


#include "qextOsgiCMPluginManager_p.h"

#include <qextOsgiServiceTracker.h>
#include <qextOsgiConfigurationPlugin.h>

#include <QStringList>

#include <set>

struct _PluginTrackerCompare
{
    bool operator() (const QExtOsgiServiceReference& l, const QExtOsgiServiceReference& r) const
    {
        return getRank(l) < getRank(r);
    }

    int getRank(const QExtOsgiServiceReference& ref) const
    {
        QVariant ranking = ref.getProperty(QExtOsgiConfigurationPlugin::CM_RANKING);
        if (!ranking.isValid() || !(ranking.canConvert<int>()))
            return 0;
        return ranking.toInt();
    }
};

class _PluginTracker : public QExtOsgiServiceTracker<QExtOsgiConfigurationPlugin*>
{
    mutable QMutex mutex;
    typedef std::set<QExtOsgiServiceReference, _PluginTrackerCompare> ServiceRefContainer;
    ServiceRefContainer serviceReferences;
    QExtOsgiPluginContext* context;

public:

    _PluginTracker(QExtOsgiPluginContext* context)
        : QExtOsgiServiceTracker<QExtOsgiConfigurationPlugin*>(context),
        context(context)
    {
    }

    QList<QExtOsgiServiceReference> getServiceReferences() const
    {
        QMutexLocker lock(&mutex);
        QList<QExtOsgiServiceReference> refs;
        ServiceRefContainer::const_iterator refEnd = serviceReferences.end();
        for (ServiceRefContainer::const_iterator it = serviceReferences.begin();
             it != refEnd; ++it)
        {
            refs.push_back(*it);
        }
        return refs;
    }

    QExtOsgiConfigurationPlugin* addingService(const QExtOsgiServiceReference& reference)
    {
        QMutexLocker lock(&mutex);
        serviceReferences.insert(reference);
        return context->getService<QExtOsgiConfigurationPlugin>(reference);
    }

    void modifiedService(const QExtOsgiServiceReference& reference, QExtOsgiConfigurationPlugin* service)
    {
        Q_UNUSED(reference)
        Q_UNUSED(service)
        // nothing to do
    }

    void removedService(const QExtOsgiServiceReference& reference, QExtOsgiConfigurationPlugin* service)
    {
        Q_UNUSED(service)

        QMutexLocker lock(&mutex);
        serviceReferences.erase(reference);
        context->ungetService(reference);
    }
};

QExtOsgiCMPluginManager::QExtOsgiCMPluginManager(QExtOsgiPluginContext* context)
{
    pluginTracker.reset(new _PluginTracker(context));
}

QExtOsgiCMPluginManager::~QExtOsgiCMPluginManager()
{

}

void QExtOsgiCMPluginManager::start()
{
    pluginTracker->open();
}

void QExtOsgiCMPluginManager::stop()
{
    pluginTracker->close();
}

void QExtOsgiCMPluginManager::modifyConfiguration(const QExtOsgiServiceReference& managedReference, QExtOsgiDictionary& properties)
{
    if (properties.empty())
        return;

    QList<QExtOsgiServiceReference> references = pluginTracker->getServiceReferences();
    foreach(QExtOsgiServiceReference ref, references)
    {
        QVariant pids = ref.getProperty(QExtOsgiConfigurationPlugin::CM_TARGET);
        if (pids.isValid() && pids.canConvert<QStringList>())
        {
            QString pid = properties.value(QExtOsgiPluginConstants::SERVICE_PID).toString();
            if (!pids.toStringList().contains(pid))
                continue;
        }
        QExtOsgiConfigurationPlugin* plugin = pluginTracker->getService(ref);
        if (plugin != 0)
            plugin->modifyConfiguration(managedReference, properties);
    }
}
