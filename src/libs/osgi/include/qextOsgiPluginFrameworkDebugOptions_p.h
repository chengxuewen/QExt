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

#ifndef QTKPLUGINFRAMEWORKDEBUGOPTIONS_P_H
#define QTKPLUGINFRAMEWORKDEBUGOPTIONS_P_H

#include "qtkplugincontext.h"
#include "qtkservicetracker.h"
#include "qtkservicetrackercustomizer.h"
#include "Service/Debug/qtkdebugoptions.h"
#include "Service/Debug/qtkdebugoptionslistener.h"

#include <QMutex>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkDebugOptions class
 * Used to get debug options settings.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkDebugOptions : public QObject, public QTKDebugOptions,
        private QTKServiceTrackerCustomizer<QTKDebugOptionsListener*>
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKDebugOptions)

public:
    QTKPluginFrameworkDebugOptions();

    static QTKPluginFrameworkDebugOptions* getDefault();

    void start(QTKPluginContext *pPluginContext);
    void stop(QTKPluginContext *pPluginContext);

    bool getBooleanOption(const QString &strOption, bool bDefaultValue) const;
    QVariant getOption(const QString &strOption) const;
    QVariant getOption(const QString &strOption, const QVariant &defaultValue) const;
    int getIntegerOption(const QString &strOption, int iDefaultValue) const;
    QHash<QString, QVariant> getOptions() const;

    void setOption(const QString &strOption, const QVariant &value);
    void setOptions(const QHash<QString, QVariant> &mapOptions);
    void removeOption(const QString &strOption);

    bool isDebugEnabled() const;
    void setDebugEnabled(bool bEnabled);

private:
    QString getSymbolicName(const QString &strOption) const;

    /**
     * @brief optionsChanged
     * Notifies the trace listener for the specified plug-in that its option-path has changed.
     *
     * @param strBundleSymbolicName The plug-in of the owning trace listener to notify.
     */
    void optionsChanged(const QString &strBundleSymbolicName);

    QTKDebugOptionsListener* addingService(const QTKServiceReference &reference);
    void modifiedService(const QTKServiceReference &reference, QTKDebugOptionsListener *pService);
    void removedService(const QTKServiceReference &reference, QTKDebugOptionsListener*pService);

    static const char *QTK_DEBUG;

    /**
     * @brief OPTIONS
     * The default name of the .options file if loading when the -debug command-line argument is used
     */
    static const char *OPTIONS;

    /**
     * @brief m_mutex
     * mutex used to lock the options maps
     */
    mutable QMutex m_mutex;

    /**
     * @brief m_bEnabled
     * A boolean value indicating if debug was enabled
     */
    bool m_bEnabled;

    /**
     * @brief m_mapOptions
     * A current map of all the options with values set
     */
    QHash<QString, QVariant> m_mapOptions;

    /**
     * @brief m_mapDisabledOptions
     * A map of all the disabled options with values set at the time debug was disabled
     */
    QHash<QString, QVariant> m_mapDisabledOptions;
    QTKPluginContext *m_pPluginContext;
    QScopedPointer<QTKServiceTracker<QTKDebugOptionsListener*> > m_pListenerTracker;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKDEBUGOPTIONS_P_H
