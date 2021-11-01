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

#ifndef QTKAPPLICATIONLAUNCHER_H
#define QTKAPPLICATIONLAUNCHER_H

#include "../../qtkpluginframework_global.h"

#include <QObject>

class QVariant;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKApplicationRunnable;

/**
 * @brief The QTKApplicationLauncher class
 * A ctkApplicationLauncher is used to launch ctkApplicationRunnable objects using
 * the main thread.
 * <p>
 * This class is for use by platform-related plug-ins which implement application containers.
 * Clients outside of the base platform should not reference or subclass this class.
 * </p>
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKApplicationLauncher
{
public:
    virtual ~QTKApplicationLauncher() {}

    /**
     * @brief launch
       * Launches the specified runnable using the main thread.
       * @param pApp a ParameterizedRunnalbe to run on the main thread.
       * @param applicationContext the context to launch the runnable with
       */
    virtual void launch(QTKApplicationRunnable *pApp, const QVariant &applicationContext) = 0;

    /**
     * @brief shutdown
     * Forces the current runnable which is running to be stopped.
     * This method will return after the currently running ctkApplicationRunnable
     * has completely stopped.
     * <p>
     * After this method returns this ctkApplicationLauncher will no longer allow
     * applications to be launched.
     */
    virtual void shutdown() = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

Q_DECLARE_INTERFACE(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKApplicationLauncher,
                    "org.qtk.service.application.ApplicationLauncher")

#endif // QTKAPPLICATIONLAUNCHER_H
