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
#include <private/qextOsgiPluginArchive_p.h>
#include <qextOsgiPluginException.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiPlugins_p.h>
#include <private/qextOsgiVersionRange_p.h>

#include <QUrl>

#include <stdexcept>
#include <iostream>

//----------------------------------------------------------------------------
void QExtOsgiPlugins::checkIllegalState() const
{
    if (!fwCtx)
    {
        throw QExtIllegalStateException("This framework instance is not active");
    }
}

//----------------------------------------------------------------------------
QExtOsgiPlugins::QExtOsgiPlugins(QExtOsgiPluginFrameworkContext* fw)
{
    fwCtx = fw;
    plugins.insert(fw->systemPlugin->getLocation(), fw->systemPlugin);
}

//----------------------------------------------------------------------------
void QExtOsgiPlugins::clear()
{
    QWriteLocker lock(&pluginsLock);
    plugins.clear();
    fwCtx = 0;
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPlugins::install(const QUrl &location, QIODevice *in)
{
    checkIllegalState();

    QSharedPointer<QExtOsgiPlugin> res;
    {
        QMutexLocker lock(&objectLock);

        QHash<QString, QSharedPointer<QExtOsgiPlugin> >::const_iterator it = plugins.find(location.toString());
        if (it != plugins.end())
        {
            return it.value();
        }

        // install new plugin
        QSharedPointer<QExtOsgiPluginArchive> pa;
        QString localPluginPath;
        try
        {
            if (!in)
            {
                // extract the input stream from the given location


                //          //TODO Support for http proxy authentication
                //          //TODO put in update as well
                //          String auth = fwCtx.props.getProperty("http.proxyAuth");
                //          if (auth != null && !"".equals(auth)) {
                //            if ("http".equals(url.getProtocol()) ||
                //                "https".equals(url.getProtocol())) {
                //              String base64 = Util.base64Encode(auth);
                //              conn.setRequestProperty("Proxy-Authorization",
                //                                      "Basic " + base64);
                //            }
                //          }
                //          // Support for http basic authentication
                //          String basicAuth = fwCtx.props.getProperty("http.basicAuth");
                //          if (basicAuth != null && !"".equals(basicAuth)) {
                //            if ("http".equals(url.getProtocol()) ||
                //                "https".equals(url.getProtocol())) {
                //              String base64 = Util.base64Encode(basicAuth);
                //              conn.setRequestProperty("Authorization",
                //                                      "Basic " +base64);
                //            }
                //          }

                if (location.scheme() != "file")
                {
                    throw QExtRuntimeException(QString("Unsupported url scheme: ") + location.scheme());
                }
                else
                {
                    localPluginPath = location.toLocalFile();
                }
            }
            else
            {
                //TODO copy the QIODevice to a local cache
            }

            pa = fwCtx->storage->insertPlugin(location, localPluginPath);

            res = QSharedPointer<QExtOsgiPlugin>(new QExtOsgiPlugin());
            res->init(res, fwCtx, pa);
            plugins.insert(location.toString(), res);
        }
        catch (const QExtException& e)
        {
            if (!pa.isNull())
            {
                pa->purge();
            }
            //      if (dynamic_cast<const SecurityException&>(e)) {
            //        throw;
            //      }
            //      else
            //      {
            throw QExtOsgiPluginException("Failed to install plugin",
                                          QExtOsgiPluginException::UNSPECIFIED, e);
            //      }
        }
        catch (...)
        {
            throw QExtOsgiPluginException("Failed to install plugin", QExtOsgiPluginException::UNSPECIFIED);
        }
    }

    fwCtx->listeners.emitPluginChanged(QExtOsgiPluginEvent(QExtOsgiPluginEvent::INSTALLED, res));
    return res;
}

//----------------------------------------------------------------------------
void QExtOsgiPlugins::remove(const QUrl &location)
{
    QWriteLocker lock(&pluginsLock);
    plugins.remove(location.toString());
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPlugins::getPlugin(int id) const
{
    checkIllegalState();

    {
        QReadLocker lock(&pluginsLock);

        QHashIterator<QString, QSharedPointer<QExtOsgiPlugin> > it(plugins);
        while (it.hasNext())
        {
            QSharedPointer<QExtOsgiPlugin> plugin = it.next().value();
            if (plugin->getPluginId() == id)
            {
                return plugin;
            }
        }
    }
    return QSharedPointer<QExtOsgiPlugin>();
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPlugins::getPlugin(const QString &location) const
{
    checkIllegalState();

    QReadLocker lock(&pluginsLock);
    QHash<QString, QSharedPointer<QExtOsgiPlugin> >::const_iterator it = plugins.find(location);
    if (it != plugins.end()) return it.value();
    return QSharedPointer<QExtOsgiPlugin>(0);
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPlugins::getPlugin(const QString &name, const QExtOsgiVersion& version) const
{
    checkIllegalState();

    {
        QReadLocker lock(&pluginsLock);

        QHashIterator<QString, QSharedPointer<QExtOsgiPlugin> > it(plugins);
        while (it.hasNext())
        {
            QSharedPointer<QExtOsgiPlugin> plugin = it.next().value();
            if ((name == plugin->getSymbolicName()) && (version == plugin->getVersion()))
            {
                return plugin;
            }
        }
    }
    return QSharedPointer<QExtOsgiPlugin>(0);
}

//----------------------------------------------------------------------------
QList<QSharedPointer<QExtOsgiPlugin> > QExtOsgiPlugins::getPlugins() const
{
    checkIllegalState();

    {
        QReadLocker lock(&pluginsLock);
        return plugins.values();
    }
}

//----------------------------------------------------------------------------
QList<QExtOsgiPlugin*> QExtOsgiPlugins::getPlugins(const QString &name) const
{
    QList<QExtOsgiPlugin*> res;

    {
        QReadLocker lock(&pluginsLock);
        QHashIterator<QString, QSharedPointer<QExtOsgiPlugin> > it(plugins);
        while (it.hasNext())
        {
            QExtOsgiPlugin* plugin = it.next().value().data();
            if (name == plugin->getSymbolicName())
            {
                res.push_back(plugin);
            }
        }
    }

    return res;
}

//----------------------------------------------------------------------------
QList<QExtOsgiPlugin*> QExtOsgiPlugins::getPlugins(const QString &name, const QExtOsgiVersionRange& range) const
{
    checkIllegalState();

    QList<QExtOsgiPlugin*> pluginsWithName = getPlugins(name);
    QList<QExtOsgiPlugin*> res;

    QListIterator<QExtOsgiPlugin*> it(pluginsWithName);
    while (it.hasNext()) {
        QExtOsgiPlugin* plugin = it.next();
        if (range.withinRange(plugin->getVersion()))
        {
            int j = res.size();
            while (--j >= 0)
            {
                if (plugin->getVersion().compare(res.at(j)->getVersion()) <= 0)
                {
                    break;
                }
            }
            res.insert(j + 1, plugin);
        }
    }

    return res;
}

//----------------------------------------------------------------------------
QList<QSharedPointer<QExtOsgiPlugin> > QExtOsgiPlugins::getActivePlugins() const
{
    checkIllegalState();

    QList<QSharedPointer<QExtOsgiPlugin> > slist;
    {
        QReadLocker lock(&pluginsLock);
        QHashIterator<QString, QSharedPointer<QExtOsgiPlugin> > it(plugins);
        while (it.hasNext())
        {
            QSharedPointer<QExtOsgiPlugin> plugin = it.next().value();
            QExtOsgiPlugin::State s = plugin->getState();
            if (s == QExtOsgiPlugin::ACTIVE || s == QExtOsgiPlugin::STARTING) {
                slist.push_back(plugin);
            }
        }
    }
    return slist;
}

//----------------------------------------------------------------------------
void QExtOsgiPlugins::load()
{
    QList<QSharedPointer<QExtOsgiPluginArchive> > pas = fwCtx->storage->getAllPluginArchives();
    QListIterator<QSharedPointer<QExtOsgiPluginArchive> > it(pas);

    {
        QMutexLocker lock(&objectLock);
        while (it.hasNext())
        {
            QSharedPointer<QExtOsgiPluginArchive> pa = it.next();
            try
            {
                QSharedPointer<QExtOsgiPlugin> plugin(new QExtOsgiPlugin());
                plugin->init(plugin, fwCtx, pa);
                plugins.insert(pa->getPluginLocation().toString(), plugin);
            }
            catch (const std::exception& e)
            {
                pa->setAutostartSetting(-1); // Do not start on launch
                pa->setStartLevel(-2); // Mark as uninstalled

                std::cerr << "Error: Failed to load bundle "
                          << pa->getPluginId()
                          << " ("  << qPrintable(pa->getPluginLocation().toString())  << ")"
                          << " uninstalled it!\n";
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPlugins::startPlugins(const QList<QExtOsgiPlugin*>& slist) const
{
    // Sort in start order
    // Resolve first to avoid dead lock
    QListIterator<QExtOsgiPlugin*> it(slist);
    while (it.hasNext())
    {
        QExtOsgiPlugin* plugin = it.next();
        QExtOsgiPluginPrivate *pp = plugin->d_func();
        pp->getUpdatedState();
    }

    it.toFront();
    while (it.hasNext())
    {
        QExtOsgiPlugin* plugin = it.next();
        QExtOsgiPluginPrivate *pp = plugin->d_func();
        if (pp->getUpdatedState() == QExtOsgiPlugin::RESOLVED)
        {
            try
            {
                plugin->start();
            }
            catch (const QExtOsgiPluginException& pe)
            {
                pp->fwCtx->listeners.frameworkError(pp->q_func(), pe);
            }
        }
    }
}
