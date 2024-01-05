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

#ifndef _QEXTOSGIPLUGINFRAMEWORKCONTEXT_P_H
#define _QEXTOSGIPLUGINFRAMEWORKCONTEXT_P_H

#include <qextOsgiPluginFramework.h>
#include <qextOsgiPluginFrameworkFactory.h>
#include <private/qextOsgiPlugins_p.h>
#include <private/qextOsgiPluginStorage_p.h>
#include <private/qextOsgiPluginFrameworkDebug_p.h>
#include <private/qextOsgiPluginFrameworkListeners_p.h>

#include <QDebug>
#include <QMutex>
#include <QDir>


class QExtOsgiPlugin;
class QExtOsgiPluginStorage;
class QExtOsgiServices;

/**
 * \ingroup PluginFramework
 */
class QExtOsgiPluginFrameworkContext
{

public:

  /**
   * All plugins in this framework.
   */
  QExtOsgiPlugins* plugins;

  /**
   * All listeners in this framework.
   */
  QExtOsgiPluginFrameworkListeners listeners;

  /**
   * All registered services in this framework.
   */
  QExtOsgiServices* services;

  /**
   * System plugin
   */
  QSharedPointer<QExtOsgiPluginFramework> systemPlugin;

  /**
   * QExtOsgiPlugin storage
   */
  QExtOsgiPluginStorage* storage;

  /**
   * Private Plugin data storage
   */
  QDir dataStorage;

  /**
   * First framework init
   */
  bool firstInit;

  /**
   * Framework id.
   */
  int id;

  /**
   * global lock.
   */
  static QMutex globalFwLock;

  /**
   * Id to use for next instance of plugin framework.
   */
  static int globalId;

  QExtOsgiProperties& props;

  /**
   * Debug handle.
   */
  QExtOsgiPluginFrameworkDebug debug;

  /**
   * Construct a framework context
   *
   */
  QExtOsgiPluginFrameworkContext();

  ~QExtOsgiPluginFrameworkContext();


  /**
   * Initialize the framework
   *
   */
  void init();


  /**
   * Undo as much as possible of what init() does.
   *
   */
  void uninit();


  /**
   *
   */
  int getId() const;

  /**
   * Get private plugin data storage file handle
   */
  QFileInfo getDataStorage(long id);

  /**
   * Check that the plugin belongs to this framework instance.
   *
   */
  void checkOurPlugin(QExtOsgiPlugin* plugin) const;


  /**
   * Check that the plugin specified can resolve all its
   * Require-QExtOsgiPlugin constraints.
   *
   * @param plugin QExtOsgiPlugin to check, must be in INSTALLED state
   *
   * @throws QExtOsgiPluginException
   */
  void resolvePlugin(QExtOsgiPluginPrivate* plugin);


  /**
   * Log message for debugging framework
   *
   */
  QDebug log() const;

private:

  QSet<QExtOsgiPluginPrivate*> tempResolved;

  bool initialized;

  /**
   * Delete framework directory if it exists.
   *
   */
  void deleteFWDir();

  void checkRequirePlugin(QExtOsgiPluginPrivate* plugin);

  void initProperties();
};


#endif // _QEXTOSGIPLUGINFRAMEWORKCONTEXT_P_H
