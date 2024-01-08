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


#include "qextOsgiCMEventDispatcher_p.h"

#include <qextOsgiLogService.h>
#include <qextOsgiConfigurationListener.h>

#include <QRunnable>

class _DispatchEventRunnable : public QRunnable
{
public:

    _DispatchEventRunnable(QExtOsgiServiceTracker<QExtOsgiConfigurationListener*>* tracker,
                           QExtOsgiLogService* log, const QExtOsgiConfigurationEvent& event,
                           const QExtOsgiServiceReference& ref)
        : tracker(tracker), log(log), event(event), ref(ref)
    {

    }

    void run()
    {
        QExtOsgiConfigurationListener* listener = tracker->getService(ref);
        if (listener == 0)
        {
            return;
        }
        try
        {
            listener->configurationEvent(event);
        }
        catch (const std::exception& e)
        {
            log->log(QExtOsgiLogService::LOG_ERROR, e.what());
        }
        catch (...)
        {
            log->log(QExtOsgiLogService::LOG_ERROR, "Unspecified exception");
        }
    }

private:

    QExtOsgiServiceTracker<QExtOsgiConfigurationListener*>* tracker;
    QExtOsgiLogService* log;
    QExtOsgiConfigurationEvent event;
    QExtOsgiServiceReference ref;
};

QExtOsgiCMEventDispatcher::QExtOsgiCMEventDispatcher(QExtOsgiPluginContext* context, QExtOsgiLogService* log)
    : tracker(context), queue("QExtOsgiConfigurationListener Event Queue"), log(log)
{

}

void QExtOsgiCMEventDispatcher::start()
{
    tracker.open();
}

void QExtOsgiCMEventDispatcher::stop()
{
    tracker.close();
    {
        QMutexLocker lock(&mutex);
        configAdminReference = 0;
    }
}


void QExtOsgiCMEventDispatcher::setServiceReference(const QExtOsgiServiceReference& reference)
{
    QMutexLocker lock(&mutex);
    if (!configAdminReference)
    {
        configAdminReference = reference;
    }
}

void QExtOsgiCMEventDispatcher::dispatchEvent(QExtOsgiConfigurationEvent::Type type,
                                              const QString& factoryPid, const QString& pid)
{
    const QExtOsgiConfigurationEvent event = createConfigurationEvent(type, factoryPid, pid);
    if (event.isNull())
        return;

    QList<QExtOsgiServiceReference> refs = tracker.getServiceReferences();

    foreach (QExtOsgiServiceReference ref, refs)
    {
        queue.put(new _DispatchEventRunnable(&tracker, log, event, ref));
    }
}

QExtOsgiConfigurationEvent QExtOsgiCMEventDispatcher::createConfigurationEvent(QExtOsgiConfigurationEvent::Type type,
                                                                               const QString& factoryPid, const QString& pid)
{
    if (!configAdminReference)
    {
        return QExtOsgiConfigurationEvent();
    }

    return QExtOsgiConfigurationEvent(configAdminReference, type, factoryPid, pid);
}

