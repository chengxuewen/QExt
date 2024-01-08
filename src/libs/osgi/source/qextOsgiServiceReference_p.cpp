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

#include <private/qextOsgiServiceReference_p.h>
#include <private/qextOsgiPlugin_p.h>
#include <private/qextOsgiServices_p.h>
#include <private/qextOsgiServiceRegistration_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiServiceFactory.h>
#include <qextOsgiServiceException.h>


#include <QObject>
#include <QMutexLocker>

//----------------------------------------------------------------------------
QExtOsgiServiceReferencePrivate::QExtOsgiServiceReferencePrivate(QExtOsgiServiceRegistrationPrivate *reg)
    : ref(1), registration(reg)
{
    if (registration) registration->ref.ref();
}

//----------------------------------------------------------------------------
QExtOsgiServiceReferencePrivate::~QExtOsgiServiceReferencePrivate()
{
    if (registration && !registration->ref.deref())
        delete registration;
}

//----------------------------------------------------------------------------
QObject *QExtOsgiServiceReferencePrivate::getService(QSharedPointer<QExtOsgiPlugin> plugin)
{
    QObject *s = 0;
    {
        QMutexLocker lock(&registration->propsLock);
        if (registration->available)
        {
            int count = registration->dependents.value(plugin);
            if (count == 0)
            {
                QStringList classes =
                    registration->properties.value(QExtOsgiPluginConstants::OBJECTCLASS).toStringList();
                registration->dependents[plugin] = 1;
                if (QExtOsgiServiceFactory* serviceFactory = qobject_cast<QExtOsgiServiceFactory*>(registration->getService()))
                {
                    try
                    {
                        s = serviceFactory->getService(plugin, QExtOsgiServiceRegistration(registration));
                    }
                    catch (const QExtException& pe)
                    {
                        QExtOsgiServiceException se("qextOsgiServiceFactory throw an exception",
                                                    QExtOsgiServiceException::FACTORY_EXCEPTION, pe);
                        plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), se);
                        return 0;
                    }
                    if (s == 0)
                    {
                        QExtOsgiServiceException se("qextOsgiServiceFactory produced null",
                                                    QExtOsgiServiceException::FACTORY_ERROR);
                        plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), se);
                        return 0;
                    }
                    for (QStringListIterator i(classes); i.hasNext(); )
                    {
                        QString cls = i.next();
                        if (!registration->plugin->fwCtx->services->checkServiceClass(s, cls))
                        {
                            QExtOsgiServiceException se(QString("qextOsgiServiceFactory produced an object ") +
                                                            "that did not implement: " + cls,
                                                        QExtOsgiServiceException::FACTORY_ERROR);
                            plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), se);
                            return 0;
                        }
                    }
                    registration->serviceInstances.insert(plugin, s);
                }
                else
                {
                    s = registration->getService();
                }
            }
            else
            {
                registration->dependents.insert(plugin, count + 1);
                if (qobject_cast<QExtOsgiServiceFactory*>(registration->getService()))
                {
                    s = registration->serviceInstances.value(plugin);
                }
                else
                {
                    s = registration->getService();
                }
            }
        }
    }
    return s;
}

//----------------------------------------------------------------------------
bool QExtOsgiServiceReferencePrivate::ungetService(QSharedPointer<QExtOsgiPlugin> plugin, bool checkRefCounter)
{
    QMutexLocker lock(&registration->propsLock);
    bool hadReferences = false;
    bool removeService = false;

    int count= registration->dependents.value(plugin);
    if (count > 0)
    {
        hadReferences = true;
    }

    if(checkRefCounter)
    {
        if (count > 1)
        {
            registration->dependents[plugin] = count - 1;
        }
        else if(count == 1)
        {
            removeService = true;
        }
    }
    else
    {
        removeService = true;
    }

    if (removeService)
    {
        QObject *sfi = registration->serviceInstances[plugin];
        registration->serviceInstances.remove(plugin);
        if (sfi != 0)
        {
            try
            {
                qobject_cast<QExtOsgiServiceFactory*>(
                    registration->getService())->ungetService(plugin, QExtOsgiServiceRegistration(registration), sfi);
            }
            catch (const QExtException& e)
            {
                plugin->d_func()->fwCtx->listeners.frameworkError(registration->plugin->q_func(), e);
            }
        }
        registration->dependents.remove(plugin);
    }

    return hadReferences;
}

//----------------------------------------------------------------------------
const QExtOsgiServiceProperties& QExtOsgiServiceReferencePrivate::getProperties() const
{
    return registration->properties;
}

//----------------------------------------------------------------------------
QVariant QExtOsgiServiceReferencePrivate::getProperty(const QString &key, bool lock) const
{
    if (lock)
    {
        QMutexLocker lock(&registration->propsLock);
        return registration->properties.value(key);
    }
    return registration->properties.value(key);
}
