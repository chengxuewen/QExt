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

#include "qtkplugincontext.h"
#include "qtkplugin_p.h"
#include "qtkplugincontext_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkservices_p.h"
#include "qtkserviceregistration.h"
#include "qtkservicereference.h"
#include "qtkservicereference_p.h"

#include <stdexcept>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKPluginContext::QTKPluginContext(QTKPluginPrivate *pPlugin)
    : d_ptr(new QTKPluginContextPrivate(pPlugin))
{

}

QTKPluginContext::~QTKPluginContext()
{
    Q_D(QTKPluginContext);
    delete d;
}

QVariant QTKPluginContext::getProperty(const QString &strkey) const
{
    Q_D(const QTKPluginContext);
    d->isPluginContextValid();
    return d->m_pPlugin->m_pPFWContext->m_properties.value(strkey);
}

QSharedPointer<QTKPlugin> QTKPluginContext::getPlugin() const
{
    Q_D(const QTKPluginContext);
    d->isPluginContextValid();
    return d->m_pPlugin->q_func();
}

QSharedPointer<QTKPlugin> QTKPluginContext::getPlugin(long lId) const
{
    Q_D(const QTKPluginContext);
    return d->m_pPlugin->m_pPFWContext->m_pPlugins->getPlugin(lId);
}

QList<QSharedPointer<QTKPlugin> > QTKPluginContext::getPlugins() const
{
    Q_D(const QTKPluginContext);
    d->isPluginContextValid();
    return d->m_pPlugin->m_pPFWContext->m_pPlugins->getPlugins();
}

QSharedPointer<QTKPlugin> QTKPluginContext::installPlugin(const QUrl &location, QIODevice *pInput)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    return d->m_pPlugin->m_pPFWContext->m_pPlugins->install(location, pInput);
}

QFileInfo QTKPluginContext::getDataFile(const QString &strFilename)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    QDir dataRoot(d->m_pPlugin->getDataRoot().absolutePath());
    if (!dataRoot.exists()) {
        if (!dataRoot.mkpath(dataRoot.absolutePath())) {
            qWarning() << "Could not create persistent storage area:" << dataRoot.absolutePath();
        }
    }
    return QFileInfo(dataRoot.absolutePath() + '/' + strFilename);
}

QTKServiceRegistration QTKPluginContext::registerService(const QStringList &listClazzes, QObject *pService, const QTKDictionary &properties)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    return d->m_pPlugin->m_pPFWContext->m_pServices->registerService(d->m_pPlugin, listClazzes, pService, properties);
}

QTKServiceRegistration QTKPluginContext::registerService(const char *pClazz, QObject *pService, const QTKDictionary &properties)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    QStringList clazzes;
    clazzes.append(pClazz);
    return d->m_pPlugin->m_pPFWContext->m_pServices->registerService(d->m_pPlugin, clazzes, pService, properties);
}

QList<QTKServiceReference> QTKPluginContext::getServiceReferences(const QString &strClazz, const QString &strFilter)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    return d->m_pPlugin->m_pPFWContext->m_pServices->get(strClazz, strFilter, 0);
}

QTKServiceReference QTKPluginContext::getServiceReference(const QString &strClazz)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    return d->m_pPlugin->m_pPFWContext->m_pServices->get(d->m_pPlugin, strClazz);
}

QObject* QTKPluginContext::getService(const QTKServiceReference &reference)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();

    if (!reference) {
        throw QTKInvalidArgumentException("Default constructed QTKServiceReference is not a valid input to getService()");
    }
    QTKServiceReference internalRef(reference);
    return internalRef.d_func()->getService(d->m_pPlugin->q_func());
}

bool QTKPluginContext::ungetService(const QTKServiceReference &reference)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    QTKServiceReference ref = reference;
    return ref.d_func()->ungetService(d->m_pPlugin->q_func(), true);
}

bool QTKPluginContext::connectPluginListener(const QObject *pReceiver, const char *pSlot, Qt::ConnectionType eType)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    // TODO check permissions for a direct connection
    if (eType == Qt::DirectConnection || eType == Qt::BlockingQueuedConnection) {
        return pReceiver->connect(&(d->m_pPlugin->m_pPFWContext->m_listeners), SIGNAL(pluginChangedDirect(QTKPluginEvent)), pSlot, eType);
    } else if (eType == Qt::QueuedConnection) {
        return pReceiver->connect(&(d->m_pPlugin->m_pPFWContext->m_listeners), SIGNAL(pluginChangedQueued(QTKPluginEvent)), pSlot, eType);
    } else {
        throw QTKInvalidArgumentException("Only Qt::DirectConnection, Qt::QueuedConnection, or Qt::BlockingQueuedConnection are allowed as type argument.");
    }
}

void QTKPluginContext::disconnectPluginListener(const QObject *pReceiver, const char *pSlot)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();

    QObject::disconnect(&(d->m_pPlugin->m_pPFWContext->m_listeners), SIGNAL(pluginChangedDirect(QTKPluginEvent)), pReceiver, pSlot);
    QObject::disconnect(&(d->m_pPlugin->m_pPFWContext->m_listeners), SIGNAL(pluginChangedQueued(QTKPluginEvent)), pReceiver, pSlot);
}

bool QTKPluginContext::connectFrameworkListener(const QObject *pReceiver, const char *pSlot, Qt::ConnectionType eType)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    // TODO check permissions for a direct connection
    return pReceiver->connect(&(d->m_pPlugin->m_pPFWContext->m_listeners), SIGNAL(frameworkEvent(QTKPluginFrameworkEvent)), pSlot, eType);
}

void QTKPluginContext::disconnectFrameworkListener(const QObject *pReceiver, const char *pSlot)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();

    QObject::disconnect(&(d->m_pPlugin->m_pPFWContext->m_listeners), SIGNAL(frameworkEvent(QTKPluginFrameworkEvent)), pReceiver, pSlot);
}

void QTKPluginContext::connectServiceListener(QObject *pReceiver, const char *pSlot, const QString &strFilter)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    d->m_pPlugin->m_pPFWContext->m_listeners.addServiceSlot(getPlugin(), pReceiver, pSlot, strFilter);
}

void QTKPluginContext::disconnectServiceListener(QObject *pReceiver, const char *pSlot)
{
    Q_D(QTKPluginContext);
    d->isPluginContextValid();
    d->m_pPlugin->m_pPFWContext->m_listeners.removeServiceSlot(getPlugin(), pReceiver, pSlot);
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
