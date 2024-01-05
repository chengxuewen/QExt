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

#include <private/qextOsgiPlugin_p.h>
#include <private/qextOsgiPluginContext_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiServiceReference_p.h>
#include <private/qextOsgiServices_p.h>
#include <qextOsgiPluginContext.h>
#include <qextOsgiServiceReference.h>
#include <qextOsgiServiceRegistration.h>

#include <stdexcept>

//----------------------------------------------------------------------------
QExtOsgiPluginContextPrivate::QExtOsgiPluginContextPrivate(QExtOsgiPluginPrivate* plugin)
    : plugin(plugin)
{}

//----------------------------------------------------------------------------
void QExtOsgiPluginContextPrivate::isPluginContextValid() const
{
    if (!plugin)
    {
        throw QExtIllegalStateException("This plugin context is no longer valid");
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginContextPrivate::invalidate()
{
    plugin = 0;
}

//----------------------------------------------------------------------------
QExtOsgiPluginContext::QExtOsgiPluginContext(QExtOsgiPluginPrivate* plugin)
    : d_ptr(new QExtOsgiPluginContextPrivate(plugin))
{}

//----------------------------------------------------------------------------
QExtOsgiPluginContext::~QExtOsgiPluginContext()
{
    Q_D(QExtOsgiPluginContext);
    delete d;
}

//----------------------------------------------------------------------------
QVariant QExtOsgiPluginContext::getProperty(const QString& key) const
{
    Q_D(const QExtOsgiPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->props.value(key);
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPluginContext::getPlugin() const
{
    Q_D(const QExtOsgiPluginContext);
    d->isPluginContextValid();
    return d->plugin->q_func();
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPluginContext::getPlugin(long id) const
{
    Q_D(const QExtOsgiPluginContext);
    return d->plugin->fwCtx->plugins->getPlugin(id);
}

//----------------------------------------------------------------------------
QList<QSharedPointer<QExtOsgiPlugin> > QExtOsgiPluginContext::getPlugins() const
{
    Q_D(const QExtOsgiPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->plugins->getPlugins();
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPluginContext::installPlugin(const QUrl& location, QIODevice* in)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->plugins->install(location, in);
}

//----------------------------------------------------------------------------
QFileInfo QExtOsgiPluginContext::getDataFile(const QString& filename)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    QDir dataRoot(d->plugin->getDataRoot().absolutePath());
    if (!dataRoot.exists())
    {
        if (!dataRoot.mkpath(dataRoot.absolutePath()))
        {
            qWarning() << "Could not create persistent storage area:" << dataRoot.absolutePath();
        }
    }
    return QFileInfo(dataRoot.absolutePath() + '/' + filename);
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration QExtOsgiPluginContext::registerService(const QStringList& clazzes, QObject* service, const QExtOsgiDictionary& properties)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->services->registerService(d->plugin, clazzes, service, properties);
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration QExtOsgiPluginContext::registerService(const char* clazz, QObject* service, const QExtOsgiDictionary& properties)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    QStringList clazzes;
    clazzes.append(clazz);
    return d->plugin->fwCtx->services->registerService(d->plugin, clazzes, service, properties);
}

//----------------------------------------------------------------------------
QList<QExtOsgiServiceReference> QExtOsgiPluginContext::getServiceReferences(const QString& clazz, const QString& filter)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->services->get(clazz, filter, 0);
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference QExtOsgiPluginContext::getServiceReference(const QString& clazz)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->services->get(d->plugin, clazz);
}

//----------------------------------------------------------------------------
QObject* QExtOsgiPluginContext::getService(const QExtOsgiServiceReference& reference)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();

    if (!reference)
    {
        throw QExtInvalidArgumentException("Default constructed QExtOsgiServiceReference is not a valid input to getService()");
    }
    QExtOsgiServiceReference internalRef(reference);
    return internalRef.d_func()->getService(d->plugin->q_func());
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginContext::ungetService(const QExtOsgiServiceReference& reference)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    QExtOsgiServiceReference ref = reference;
    return ref.d_func()->ungetService(d->plugin->q_func(), true);
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginContext::connectPluginListener(const QObject* receiver, const char* slot,
                                                  Qt::ConnectionType type)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    // TODO check permissions for a direct connection
    if (type == Qt::DirectConnection || type == Qt::BlockingQueuedConnection)
    {
        return receiver->connect(&(d->plugin->fwCtx->listeners), SIGNAL(pluginChangedDirect(QExtOsgiPluginEvent)), slot, type);
    }
    else if (type == Qt::QueuedConnection)
    {
        return receiver->connect(&(d->plugin->fwCtx->listeners), SIGNAL(pluginChangedQueued(QExtOsgiPluginEvent)), slot, type);
    }
    else
    {
        throw QExtInvalidArgumentException("Only Qt::DirectConnection, Qt::QueuedConnection, or Qt::BlockingQueuedConnection are allowed as type argument.");
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginContext::disconnectPluginListener(const QObject *receiver, const char* slot)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();

    QObject::disconnect(&(d->plugin->fwCtx->listeners), SIGNAL(pluginChangedDirect(QExtOsgiPluginEvent)), receiver, slot);
    QObject::disconnect(&(d->plugin->fwCtx->listeners), SIGNAL(pluginChangedQueued(QExtOsgiPluginEvent)), receiver, slot);
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginContext::connectFrameworkListener(const QObject* receiver, const char* slot, Qt::ConnectionType type)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    // TODO check permissions for a direct connection
    return receiver->connect(&(d->plugin->fwCtx->listeners), SIGNAL(frameworkEvent(QExtOsgiPluginFrameworkEvent)), slot, type);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginContext::disconnectFrameworkListener(const QObject *receiver, const char* slot)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();

    QObject::disconnect(&(d->plugin->fwCtx->listeners), SIGNAL(frameworkEvent(QExtOsgiPluginFrameworkEvent)), receiver, slot);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginContext::connectServiceListener(QObject* receiver, const char* slot,
                                                   const QString& filter)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    d->plugin->fwCtx->listeners.addServiceSlot(getPlugin(), receiver, slot, filter);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginContext::disconnectServiceListener(QObject* receiver,
                                                      const char* slot)
{
    Q_D(QExtOsgiPluginContext);
    d->isPluginContextValid();
    d->plugin->fwCtx->listeners.removeServiceSlot(getPlugin(), receiver, slot);
}
