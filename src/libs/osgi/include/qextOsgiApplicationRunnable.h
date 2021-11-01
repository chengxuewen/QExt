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

#ifndef QTKAPPLICATIONRUNNABLE_H
#define QTKAPPLICATIONRUNNABLE_H

#include "qtkpluginframework_global.h"

class QVariant;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKApplicationRunnable class
 * Like a QRunnable, an object which captures a block of code which can
 * be passed around and executed as well as stopped.  Unlike standard runnables,
 * paramaterized runnables allow an arbitrary QVariant to be passed in when the
 * block is evaluated.
 * <p>
 * Clients may implement this interface.
 * </p>
 */
class QTKApplicationRunnable
{
public:
    virtual ~QTKApplicationRunnable() {}


    /**
     * Executes the block of code encapsulated by this runnable in the context of
     * the given object and returns the result.  The result may be an invalid QVariant.
     *
     * @param context the context for evaluating the runnable
     * @return the result of evaluating the runnable in the given context
     * @throws std::exception if there is a problem running this runnable
     */
    virtual QVariant run(const QVariant &context) = 0;

    /**
     * Forces this runnable to stop.
     */
    virtual void stop() = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKAPPLICATIONRUNNABLE_H
