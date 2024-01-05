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

#ifndef _QEXTOSGIAPPLICATIONLAUNCHER_H
#define _QEXTOSGIAPPLICATIONLAUNCHER_H

#include <QObject>

struct QExtOsgiApplicationRunnable;

class QVariant;

/**
 * A QExtOsgiApplicationLauncher is used to launch QExtOsgiApplicationRunnable objects using
 * the main thread.
 * <p>
 * This class is for use by platform-related plug-ins which implement application containers.
 * Clients outside of the base platform should not reference or subclass this class.
 * </p>
 */
struct QExtOsgiApplicationLauncher
{
  virtual ~QExtOsgiApplicationLauncher() {}

  /**
     * Launches the specified runnable using the main thread.
     * @param runnable a ParameterizedRunnalbe to run on the main thread.
     * @param context the context to launch the runnable with
     */
  virtual void launch(QExtOsgiApplicationRunnable* app, const QVariant& applicationContext) = 0;

  /**
   * Forces the current runnable which is running to be stopped.
   * This method will return after the currently running QExtOsgiApplicationRunnable
   * has completely stopped.
   * <p>
   * After this method returns this QExtOsgiApplicationLauncher will no longer allow
   * applications to be launched.
   */
  virtual void shutdown() = 0;

};

Q_DECLARE_INTERFACE(QExtOsgiApplicationLauncher, "org.qext.service.application.ApplicationLauncher")

#endif // _QEXTOSGIAPPLICATIONLAUNCHER_H
