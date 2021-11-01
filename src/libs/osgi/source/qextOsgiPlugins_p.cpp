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

#include "qtkplugins_p.h"
#include "qtkplugin_p.h"
#include "qtkpluginarchive_p.h"
#include "qtkpluginexception.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkplugins_p.h"
#include "qtkversionrange_p.h"

#include <QUrl>

#include <stdexcept>
#include <iostream>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKPlugins::QTKPlugins(QTKPluginFrameworkContext *pPFWContext)
{
    m_pPFWContext = pPFWContext;
    m_mapLocationToPlugin.insert(pPFWContext->m_pRunTimePlugin->getLocation(), pPFWContext->m_pRunTimePlugin);
}

QTKPlugins::~QTKPlugins()
{
    m_mapLocationToPlugin.clear();
}

QSharedPointer<QTKPlugin> QTKPlugins::install(const QUrl &location, QIODevice *pIn)
{
    this->checkIllegalState();

    QSharedPointer<QTKPlugin> pPlugin;
    {
        QMutexLocker lock(&m_objectLock);
        QHash<QString, QSharedPointer<QTKPlugin> >::const_iterator iter = m_mapLocationToPlugin.find(location.toString());
        if (iter != m_mapLocationToPlugin.end()) {
            return iter.value();
        }
        // install new plugin
        QSharedPointer<QTKPluginArchive> pPluginArchive;
        QString strLocalPluginPath;
        try {
            if (nullptr == pIn) {
                if (location.scheme() != "file") {
                    throw QTKRuntimeException(QString("Unsupported url scheme: ") + location.scheme());
                } else {
                    strLocalPluginPath = location.toLocalFile();
                }
            } else {
                //TODO copy the QIODevice to a local cache
            }

            pPluginArchive = m_pPFWContext->m_pStorage->insertPlugin(location, strLocalPluginPath);
            pPlugin = QSharedPointer<QTKPlugin>(new QTKPlugin());
            pPlugin->init(pPlugin, m_pPFWContext, pPluginArchive);
            m_mapLocationToPlugin.insert(location.toString(), pPlugin);
        } catch (const QTKException &e) {
            if (!pPluginArchive.isNull()) {
                pPluginArchive->purge();
            }
            throw QTKPluginException("Failed to install plugin", QTKPluginException::Type_Unspecified, e);
        } catch (...) {
            throw QTKPluginException("Failed to install plugin", QTKPluginException::Type_Unspecified);
        }
    }

    m_pPFWContext->m_listeners.emitPluginChanged(QTKPluginEvent(QTKPluginEvent::Type_Installed, pPlugin));
    return pPlugin;
}

void QTKPlugins::remove(const QUrl &location)
{
    QWriteLocker lock(&m_pluginsLock);
    m_mapLocationToPlugin.remove(location.toString());
}

QSharedPointer<QTKPlugin> QTKPlugins::getPlugin(int iId) const
{
    this->checkIllegalState();

    {
        QReadLocker lock(&m_pluginsLock);

        QHashIterator<QString, QSharedPointer<QTKPlugin> > iter(m_mapLocationToPlugin);
        while (iter.hasNext()) {
            QSharedPointer<QTKPlugin> pPlugin = iter.next().value();
            if (pPlugin->getPluginId() == iId) {
                return pPlugin;
            }
        }
    }
    return QSharedPointer<QTKPlugin>();
}

QSharedPointer<QTKPlugin> QTKPlugins::getPlugin(const QString &strLocation) const
{
    this->checkIllegalState();

    QReadLocker lock(&m_pluginsLock);
    QHash<QString, QSharedPointer<QTKPlugin> >::const_iterator iter = m_mapLocationToPlugin.find(strLocation);
    if (iter != m_mapLocationToPlugin.end()) {
        return iter.value();
    }
    return QSharedPointer<QTKPlugin>(0);
}

QSharedPointer<QTKPlugin> QTKPlugins::getPlugin(const QString &strName, const QTKVersion &version) const
{
    this->checkIllegalState();

    {
        QReadLocker lock(&m_pluginsLock);
        QHashIterator<QString, QSharedPointer<QTKPlugin> > iter(m_mapLocationToPlugin);
        while (iter.hasNext()) {
            QSharedPointer<QTKPlugin> pPlugin = iter.next().value();
            if ((strName == pPlugin->getSymbolicName()) && (version == pPlugin->getVersion())) {
                return pPlugin;
            }
        }
    }
    return QSharedPointer<QTKPlugin>(0);
}

QList<QSharedPointer<QTKPlugin> > QTKPlugins::getPlugins() const
{
    this->checkIllegalState();

    {
        QReadLocker lock(&m_pluginsLock);
        return m_mapLocationToPlugin.values();
    }
}

QList<QTKPlugin *> QTKPlugins::getPlugins(const QString &strName) const
{
    QList<QTKPlugin*> listPlugins;

    {
        QReadLocker lock(&m_pluginsLock);
        QHashIterator<QString, QSharedPointer<QTKPlugin> > iter(m_mapLocationToPlugin);
        while (iter.hasNext()) {
            QTKPlugin *pPlugin = iter.next().value().data();
            if (strName == pPlugin->getSymbolicName()) {
                listPlugins.push_back(pPlugin);
            }
        }
    }

    return listPlugins;
}

QList<QTKPlugin *> QTKPlugins::getPlugins(const QString &strName, const QTKVersionRange &range) const
{
    this->checkIllegalState();

    QList<QTKPlugin *> listPluginsWithName = this->getPlugins(strName);
    QList<QTKPlugin *> listResPlugin;

    QListIterator<QTKPlugin*> iter(listPluginsWithName);
    while (iter.hasNext()) {
        QTKPlugin *pPlugin = iter.next();
        if (range.withinRange(pPlugin->getVersion())) {
            int iSize = listResPlugin.size();
            while (--iSize >= 0) {
                if (pPlugin->getVersion().compare(listResPlugin.at(iSize)->getVersion()) <= 0) {
                    break;
                }
            }
            listResPlugin.insert(iSize + 1, pPlugin);
        }
    }

    return listResPlugin;
}

QList<QSharedPointer<QTKPlugin> > QTKPlugins::getActivePlugins() const
{
    this->checkIllegalState();

    QList<QSharedPointer<QTKPlugin> > listPlugin;
    {
        QReadLocker lock(&m_pluginsLock);
        QHashIterator<QString, QSharedPointer<QTKPlugin> > iter(m_mapLocationToPlugin);
        while (iter.hasNext()) {
            QSharedPointer<QTKPlugin> pPlugin = iter.next().value();
            QTKPlugin::State eState = pPlugin->getState();
            if (eState == QTKPlugin::State_Active || eState == QTKPlugin::State_Starting) {
                listPlugin.push_back(pPlugin);
            }
        }
    }
    return listPlugin;
}

void QTKPlugins::load()
{
    QList<QSharedPointer<QTKPluginArchive> > listPluginArchives = m_pPFWContext->m_pStorage->getAllPluginArchives();
    QListIterator<QSharedPointer<QTKPluginArchive> > iter(listPluginArchives);

    {
        QMutexLocker lock(&m_objectLock);
        while (iter.hasNext()) {
            QSharedPointer<QTKPluginArchive> pPluginArchive = iter.next();
            try {
                QSharedPointer<QTKPlugin> pPlugin(new QTKPlugin());
                pPlugin->init(pPlugin, m_pPFWContext, pPluginArchive);
                m_mapLocationToPlugin.insert(pPluginArchive->getPluginLocation().toString(), pPlugin);
            } catch (const std::exception &e) {
                pPluginArchive->setAutostartSetting(-1); // Do not start on launch
                pPluginArchive->setStartLevel(-2); // Mark as uninstalled

                std::cerr << "Error: Failed to load bundle "
                          << pPluginArchive->getPluginId()
                          << " ("  << qPrintable(pPluginArchive->getPluginLocation().toString())  << ")"
                          << " uninstalled it!\n";
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void QTKPlugins::startPlugins(const QList<QTKPlugin *> &listPlugins) const
{
    // Sort in start order
    // Resolve first to avoid dead lock
    QListIterator<QTKPlugin *> iter(listPlugins);
    while (iter.hasNext()) {
        QTKPlugin *pPlugin = iter.next();
        QTKPluginPrivate *pPluginPrivate = pPlugin->d_func();
        pPluginPrivate->getUpdatedState();
    }

    iter.toFront();
    while (iter.hasNext()) {
        QTKPlugin *pPlugin = iter.next();
        QTKPluginPrivate *pPluginPrivate = pPlugin->d_func();
        if (pPluginPrivate->getUpdatedState() == QTKPlugin::State_Resolved) {
            try {
                pPlugin->start(0);
            } catch (const QTKPluginException &e) {
                pPluginPrivate->m_pPFWContext->m_listeners.frameworkError(pPluginPrivate->q_func(), e);
            }
        }
    }
}

void QTKPlugins::checkIllegalState() const
{
    if (nullptr == m_pPFWContext) {
        throw QTKIllegalStateException("This framework instance is not active");
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
