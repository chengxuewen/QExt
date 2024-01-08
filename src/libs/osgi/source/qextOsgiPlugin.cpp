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

#include <qextOsgiPlugin.h>
#include <private/qextOsgiPlugin_p.h>
#include <private/qextOsgiPluginArchive_p.h>
#include <private/qextOsgiPluginContext_p.h>
#include <private/qextOsgiPluginFrameworkUtil_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiServices_p.h>
#include <qextOsgiPluginContext.h>
#include <qextUtils.h>

#include <QStringList>

QExtOsgiPlugin::QExtOsgiPlugin()
    : d_ptr(0)
{

}

void QExtOsgiPlugin::init(QExtOsgiPluginPrivate *dd)
{
    if (d_ptr)
    {
        throw QExtIllegalStateException("qextOsgiPlugin already initialized");
    }
    d_ptr = dd;
}

void QExtOsgiPlugin::init(const QWeakPointer<QExtOsgiPlugin> &self,
                          QExtOsgiPluginFrameworkContext *fw,
                          QSharedPointer<QExtOsgiPluginArchive> pa)
{
    if (d_ptr)
    {
        throw QExtIllegalStateException("qextOsgiPlugin already initialized");
    }
    d_ptr = new QExtOsgiPluginPrivate(self, fw, pa);
}

QExtOsgiPlugin::~QExtOsgiPlugin()
{
    delete d_ptr;
}

QExtOsgiPlugin::State QExtOsgiPlugin::getState() const
{
    Q_D(const QExtOsgiPlugin);
    return d->state;
}

void QExtOsgiPlugin::start(const StartOptions &options)
{
    Q_D(QExtOsgiPlugin);

    if (d->state == UNINSTALLED)
    {
        throw QExtIllegalStateException("qextOsgiPlugin is uninstalled");
    }

    // Initialize the activation; checks initialization of lazy
    // activation.

    //TODO 1: If activating or deactivating, wait a little
    // we don't use multiple threads to start plugins for now
    //waitOnActivation(lock, "qextOsgiPlugin::start", false);

    //2: start() is idempotent, i.e., nothing to do when already started
    if (d->state == ACTIVE)
    {
        return;
    }

    //3: Record non-transient start requests.
    if ((options & START_TRANSIENT) == 0)
    {
        d->setAutostartSetting(options);
    }

    //4: Resolve plugin (if needed)
    d->getUpdatedState();

    //5: Eager?
    if ((options & START_ACTIVATION_POLICY) && !d->eagerActivation )
    {
        if (STARTING == d->state) return;
        d->state = STARTING;
        d->pluginContext.reset(new QExtOsgiPluginContext(this->d_func()));
        QExtOsgiPluginEvent pluginEvent(QExtOsgiPluginEvent::LAZY_ACTIVATION, d->q_ptr);
        d->fwCtx->listeners.emitPluginChanged(pluginEvent);
    }
    else
    {
        d->finalizeActivation();
    }
}

void QExtOsgiPlugin::stop(const StopOptions &options)
{
    Q_D(QExtOsgiPlugin);

    const QExtRuntimeException *savedException = 0;

    //1:
    if (d->state == UNINSTALLED)
    {
        throw QExtIllegalStateException("qextOsgiPlugin is uninstalled");
    }

    // 2: If an operation is in progress, wait a little
    d->waitOnOperation(&d->operationLock, "Plugin::stop", false);

    //3:
    if ((options & STOP_TRANSIENT) == 0)
    {
        d->ignoreAutostartSetting();
    }

    switch (d->state)
    {
    case INSTALLED:
    case RESOLVED:
    case STOPPING:
    case UNINSTALLED:
        //4:
        return;

    case ACTIVE:
    case STARTING: // Lazy start...
        savedException = d->stop0();
        break;
    };

    if (savedException != 0)
    {
        if (const QExtOsgiPluginException *pluginExc = dynamic_cast<const QExtOsgiPluginException*>(savedException))
        {
            QExtOsgiPluginException pe(*pluginExc);
            delete savedException;
            throw pe;
        }
        else
        {
            QExtRuntimeException re(*savedException);
            delete savedException;
            throw re;
        }
    }
}

void QExtOsgiPlugin::update(const QUrl &updateLocation)
{
    Q_D(QExtOsgiPlugin);
    QExtOsgiPluginPrivate::Locker sync(&d->operationLock);
    const bool wasActive = d->state == ACTIVE;

    switch (d->getUpdatedState_unlocked())
    {
    case ACTIVE:
        stop(STOP_TRANSIENT);
        // Fall through
    case RESOLVED:
    case INSTALLED:
        // Load new plugin
        //secure.callUpdate0(this, in, wasActive);
        d->update0(updateLocation, wasActive);
        break;
    case STARTING:
        // Wait for RUNNING state, this doesn't happen now
        // since we are synchronized.
        throw QExtIllegalStateException("Plugin is in STARTING state");
    case STOPPING:
        // Wait for RESOLVED state, this doesn't happen now
        // since we are synchronized.
        throw QExtIllegalStateException("Plugin is in STOPPING state");
    case UNINSTALLED:
        throw QExtIllegalStateException("Plugin is in UNINSTALLED state");
    }
}

void QExtOsgiPlugin::uninstall()
{
    Q_D(QExtOsgiPlugin);
    {
        QExtOsgiPluginPrivate::Locker sync(&d->operationLock);

        if (d->archive)
        {
            try
            {
                d->archive->setStartLevel(-2); // Mark as uninstalled
            }
            catch (...)
            { }
        }

        switch (d->state)
        {
        case UNINSTALLED:
            throw QExtIllegalStateException("Plugin is in UNINSTALLED state");

        case STARTING: // Lazy start
        case ACTIVE:
        case STOPPING:
        {
            const QExtRuntimeException *exception = 0;
            try
            {
                d->waitOnOperation(&d->operationLock, "qextOsgiPlugin::uninstall", true);
                if (d->state & (ACTIVE | STARTING))
                {
                    exception = d->stop0();
                }
            }
            catch (const QExtException &e)
            {
                // Force to install
                d->setStateInstalled(false);
                d->operationLock.wakeAll();
                exception = new QExtRuntimeException("Stopping plug-in failed", e);
            }
            d->operation.fetchAndStoreOrdered(QExtOsgiPluginPrivate::UNINSTALLING);
            if (exception != 0)
            {
                d->fwCtx->listeners.frameworkError(this->d_func()->q_func(), *exception);
                delete exception;
            }
        }
        // Fall through
        case RESOLVED:
        case INSTALLED:
            d->fwCtx->plugins->remove(d->location);
            if (d->operation.fetchAndAddOrdered(0) != QExtOsgiPluginPrivate::UNINSTALLING)
            {
                try
                {
                    d->waitOnOperation(&d->operationLock, "Plugin::uninstall", true);
                    d->operation.fetchAndStoreOrdered(QExtOsgiPluginPrivate::UNINSTALLING);
                }
                catch (const QExtOsgiPluginException &pe)
                {
                    // Make sure that the context is invalid
                    if (d->pluginContext != 0)
                    {
                        d->pluginContext->d_func()->invalidate();
                        d->pluginContext.reset();
                    }
                    d->operation.fetchAndStoreOrdered(QExtOsgiPluginPrivate::UNINSTALLING);
                    d->fwCtx->listeners.frameworkError(this->d_func()->q_func(), pe);
                }
            }

            d->state = INSTALLED;
            // TODO: use thread
            // bundleThread().bundleChanged(new BundleEvent(BundleEvent.UNRESOLVED, this));
            d->fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::UNRESOLVED, d->q_func()));
            d->cachedHeaders = getHeaders();
            d->pluginActivator = 0;
            d->state = UNINSTALLED;

            // Purge old archive
            if (d->archive)
            {
                d->archive->purge();
            }
            d->operation.fetchAndStoreOrdered(QExtOsgiPluginPrivate::IDLE);

            if (d->pluginDir.exists())
            {
                if (!qext::removeDirRecursively(d->pluginDir.absolutePath()))
                {
                    d->fwCtx->listeners.frameworkError(this->d_func()->q_func(), QExtRuntimeException("Failed to delete plugin data"));
                }
                d->pluginDir.setFile("");
            }

            // id, location and headers survive after uninstall.

            // There might be plug-in threads that are running start or stop
            // operations. This will wake them and give them a chance to terminate.
            d->operationLock.wakeAll();
            break;
        }
    }
    d->fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::UNINSTALLED, d->q_ptr));
}

QExtOsgiPluginContext* QExtOsgiPlugin::getPluginContext() const
{
    //TODO security checks
    Q_D(const QExtOsgiPlugin);
    return d->pluginContext.data();
}

long QExtOsgiPlugin::getPluginId() const
{
    Q_D(const QExtOsgiPlugin);
    return d->id;
}

QString QExtOsgiPlugin::getLocation() const
{
    //TODO security
    Q_D(const QExtOsgiPlugin);
    return d->location;
}

QHash<QString, QString> QExtOsgiPlugin::getHeaders()
{
    //TODO security
    Q_D(QExtOsgiPlugin);
    if (d->cachedRawHeaders.empty())
    {
        d->cachedRawHeaders = d->archive->getUnlocalizedAttributes();
    }

    if (d->state == UNINSTALLED)
    {
        return d->cachedHeaders;
    }

    //TODO use the embedded .qm files to localize header values
    return d->cachedRawHeaders;
}

QString QExtOsgiPlugin::getSymbolicName() const
{
    Q_D(const QExtOsgiPlugin);
    return d->symbolicName;
}

QStringList QExtOsgiPlugin::getResourceList(const QString &path) const
{
    Q_D(const QExtOsgiPlugin);
    return d->archive->findResourcesPath(path);
}

QStringList QExtOsgiPlugin::findResources(const QString &path,
                                          const QString &pattern, bool recurse) const
{
    Q_D(const QExtOsgiPlugin);
    return d->findResourceEntries(path, pattern, recurse);
}

QByteArray QExtOsgiPlugin::getResource(const QString &path) const
{
    Q_D(const QExtOsgiPlugin);
    return d->archive->getPluginResource(path);
}

QExtOsgiPluginLocalization QExtOsgiPlugin::getPluginLocalization(const QLocale &locale, const QString &base) const
{
    Q_D(const QExtOsgiPlugin);

    // There are five searching candidates possible:
    // base +
    //    "_" + language1 + "_" + country1 + ".qm"
    // or "_" + language1 + ".qm"
    // or "_" + language2 + "_" + country2 + ".qm"
    // or "_" + language2 + ".qm"
    // or ""  + ".qm"
    //
    // Where language1[_country1[_variation1]] is the requested locale,
    // and language2[_country2[_variation2]] is the default locale.

    QChar localeSep('_');
    QChar baseSep('_');

    QStringList searchCandidates;

    QStringList localeParts = locale.name().split(localeSep);
    QStringList defaultParts = QLocale().name().split(localeSep);

    searchCandidates << baseSep + localeParts[0] + localeSep + localeParts[1];
    searchCandidates << baseSep + localeParts[0];
    searchCandidates << baseSep + defaultParts[0] + localeSep + defaultParts[1];
    searchCandidates << baseSep + defaultParts[0];
    searchCandidates << "";

    QString localizationPath = base.left(base.lastIndexOf('/'));
    QStringList resourceList = this->getResourceList(localizationPath);

    foreach(QString resource, resourceList)
    {
        foreach(QString candidate, searchCandidates)
        {
            if (resource.endsWith(candidate + ".qm"))
            {
                return QExtOsgiPluginLocalization(localizationPath + '/' + resource, locale, d->q_ptr);
            }
        }
    }

    return QExtOsgiPluginLocalization();
}

QExtOsgiVersion QExtOsgiPlugin::getVersion() const
{
    Q_D(const QExtOsgiPlugin);
    return d->version;
}

QDebug operator<<(QDebug debug, QExtOsgiPlugin::State state)
{
    switch (state)
    {
    case QExtOsgiPlugin::UNINSTALLED:
        return debug << "UNINSTALLED";
    case QExtOsgiPlugin::INSTALLED:
        return debug << "INSTALLED";
    case QExtOsgiPlugin::RESOLVED:
        return debug << "RESOLVED";
    case QExtOsgiPlugin::STARTING:
        return debug << "STARTING";
    case QExtOsgiPlugin::STOPPING:
        return debug << "STOPPING";
    case QExtOsgiPlugin::ACTIVE:
        return debug << "ACTIVE";
    default:
        return debug << "unknown";
    }
}

QDebug operator<<(QDebug debug, const QExtOsgiPlugin& plugin)
{
    debug.nospace() << "qextOsgiPlugin[" << "id=" << plugin.getPluginId() <<
        ", state=" << plugin.getState() << ", loc=" << plugin.getLocation() <<
        ", symName=" << plugin.getSymbolicName() << "]";
    return debug.maybeSpace();
}

QDebug operator<<(QDebug debug, QExtOsgiPlugin const * plugin)
{
    return operator<<(debug, *plugin);
}

QExtOsgiLogStream& operator<<(QExtOsgiLogStream &stream, QExtOsgiPlugin const *plugin)
{
    stream << plugin->getSymbolicName();
    return stream;
}

QExtOsgiLogStream& operator<<(QExtOsgiLogStream &stream, const QSharedPointer<QExtOsgiPlugin> &plugin)
{
    return operator<<(stream, plugin.data());
}
