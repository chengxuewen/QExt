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
#include <qextOsgiPluginConstants.h>
#include <qextOsgiPluginFramework.h>
#include <private/qextOsgiPluginFramework_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <qextOsgiEvent.h>

//----------------------------------------------------------------------------
QExtOsgiPluginFramework::QExtOsgiPluginFramework()
  : QExtOsgiPlugin()
{
  qRegisterMetaType<QExtOsgiPluginFrameworkEvent>("qextOsgiPluginFrameworkEvent");
  qRegisterMetaType<QExtOsgiPluginEvent>("qextOsgiPluginEvent");
  qRegisterMetaType<QExtOsgiServiceEvent>("qextOsgiServiceEvent");
  qRegisterMetaType<QExtOsgiEvent>("QExtOsgiEvent");
  qRegisterMetaType<QExtOsgiProperties>("qextOsgiProperties");
  qRegisterMetaType<QExtOsgiDictionary>("QExtOsgiDictionary");
  qRegisterMetaType<QExtOsgiServiceReference>("qextOsgiServiceReference");
  qRegisterMetaType<QSharedPointer<QExtOsgiPlugin> >("QSharedPointer<QExtOsgiPlugin>");
  //TODO: register all qext Framework defined MetaType.
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFramework::init()
{
  Q_D(QExtOsgiPluginFramework);

  QExtOsgiPluginPrivate::Locker sync(&d->lock);
  d->waitOnOperation(&d->lock, "Framework.init", true);
  switch (d->state)
  {
  case QExtOsgiPlugin::INSTALLED:
  case QExtOsgiPlugin::RESOLVED:
    break;
  case QExtOsgiPlugin::STARTING:
  case QExtOsgiPlugin::ACTIVE:
    return;
  default:
    throw QExtIllegalStateException("INTERNAL ERROR, Illegal state");
  }
  d->init();
}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent QExtOsgiPluginFramework::waitForStop(unsigned long timeout)
{
  Q_D(QExtOsgiPluginFramework);

  QExtOsgiPluginPrivate::Locker sync(&d->lock);

  // Already stopped?
  if ((d->state & (INSTALLED | RESOLVED)) == 0)
  {
    d->stopEvent.isNull = true;
    d->lock.wait(timeout ? timeout : ULONG_MAX);

    if (d->stopEvent.isNull)
    {
      return QExtOsgiPluginFrameworkEvent(QExtOsgiPluginFrameworkEvent::FRAMEWORK_WAIT_TIMEDOUT, this->d_func()->q_func());
    }
  }
  else if (d->stopEvent.isNull)
  {
    // Return this if stop or update have not been called and framework is stopped.
    d->stopEvent.isNull = false;
    d->stopEvent.type = QExtOsgiPluginFrameworkEvent::FRAMEWORK_STOPPED;
  }
  return d->stopEvent.isNull ? QExtOsgiPluginFrameworkEvent() :
                               QExtOsgiPluginFrameworkEvent(QExtOsgiPluginFrameworkEvent::FRAMEWORK_STOPPED, this->d_func()->q_func());
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFramework::start(const QExtOsgiPlugin::StartOptions& options)
{
  Q_UNUSED(options);
  Q_D(QExtOsgiPluginFramework);

  QStringList pluginsToStart;
  {
    QExtOsgiPluginPrivate::Locker sync(&d->lock);
    d->waitOnOperation(&d->lock, "qextOsgiPluginFramework::start", true);

    switch (d->state)
    {
    case INSTALLED:
#if (QT_VERSION >= QT_VERSION_CHECK(5,8,0))
      Q_FALLTHROUGH();
#else
      /* FALLTHRU */
#endif
    case RESOLVED:
      d->init();
#if (QT_VERSION >= QT_VERSION_CHECK(5,8,0))
      Q_FALLTHROUGH();
#else
      /* FALLTHRU */
#endif
    case STARTING:
      d->operation.fetchAndStoreOrdered(QExtOsgiPluginPrivate::ACTIVATING);
      break;
    case ACTIVE:
      return;
    default:
      throw QExtIllegalStateException("INTERNAL ERROR, Illegal state");
    }

    pluginsToStart = d->fwCtx->storage->getStartOnLaunchPlugins();
  }

  d->activate(d->pluginContext.data());

  // Start plugins according to their autostart setting.
  QStringListIterator i(pluginsToStart);
  while (i.hasNext())
  {
    QSharedPointer<QExtOsgiPlugin> plugin = d->fwCtx->plugins->getPlugin(i.next());
    try {
      const int autostartSetting = plugin->d_func()->archive->getAutostartSetting();
      // Launch must not change the autostart setting of a plugin
      StartOptions option = QExtOsgiPlugin::START_TRANSIENT;
      if (QExtOsgiPlugin::START_ACTIVATION_POLICY == autostartSetting)
      {
        // Transient start according to the plugins activation policy.
        option |= QExtOsgiPlugin::START_ACTIVATION_POLICY;
      }
      plugin->start(option);
    }
    catch (const QExtOsgiPluginException& pe)
    {
      d->fwCtx->listeners.frameworkError(plugin, pe);
    }
  }

  {
    QExtOsgiPluginPrivate::Locker sync(&d->lock);
    d->state = ACTIVE;
    d->operation = QExtOsgiPluginPrivate::IDLE;
    d->lock.wakeAll();
    d->fwCtx->listeners.emitFrameworkEvent(
        QExtOsgiPluginFrameworkEvent(QExtOsgiPluginFrameworkEvent::FRAMEWORK_STARTED, this->d_func()->q_func()));
  }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFramework::stop(const StopOptions& options)
{
  Q_UNUSED(options)

  Q_D(QExtOsgiPluginFramework);
  d->shutdown(false);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFramework::uninstall()
{
  throw QExtOsgiPluginException("uninstall of System plugin is not allowed",
                           QExtOsgiPluginException::INVALID_OPERATION);
}

//----------------------------------------------------------------------------
QStringList QExtOsgiPluginFramework::getResourceList(const QString &path) const
{
  QString resourcePath = QString(":/") + QExtOsgiPluginConstants::SYSTEM_PLUGIN_SYMBOLICNAME;
  if (path.startsWith('/'))
    resourcePath += path;
  else
    resourcePath += QString("/") + path;

  QStringList paths;
  QFileInfoList entryInfoList = QDir(resourcePath).entryInfoList();
  QListIterator<QFileInfo> infoIter(entryInfoList);
  while (infoIter.hasNext())
  {
    const QFileInfo& resInfo = infoIter.next();
    QString entry = resInfo.canonicalFilePath().mid(resourcePath.size());
    if (resInfo.isDir())
      entry += "/";

    paths << entry;
  }

  return paths;
}

//----------------------------------------------------------------------------
QByteArray QExtOsgiPluginFramework::getResource(const QString &path) const
{
  QString resourcePath = QString(":/") + QExtOsgiPluginConstants::SYSTEM_PLUGIN_SYMBOLICNAME;
  if (path.startsWith('/'))
    resourcePath += path;
  else
    resourcePath += QString("/") + path;

  QFile resourceFile(resourcePath);
  resourceFile.open(QIODevice::ReadOnly);
  return resourceFile.readAll();
}

//----------------------------------------------------------------------------
QHash<QString, QString> QExtOsgiPluginFramework::getHeaders()
{
  //TODO security
  Q_D(QExtOsgiPluginFramework);
  return d->systemHeaders;
}
