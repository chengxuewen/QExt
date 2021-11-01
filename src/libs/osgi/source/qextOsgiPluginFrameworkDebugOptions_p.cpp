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

#include "qtkpluginframeworkdebugoptions_p.h"
#include "qtkpluginframeworklauncher.h"
#include "qtkpluginframeworkproperties_p.h"
#include "qtkplugincontext.h"

#include <QTKCore/QTKException>

#include <QSettings>
#include <QMutex>
#include <QDir>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const char *QTKPluginFrameworkDebugOptions::QTK_DEBUG = "qtk.debug";
const char *QTKPluginFrameworkDebugOptions::OPTIONS = ".qtk.options";

QTKPluginFrameworkDebugOptions::QTKPluginFrameworkDebugOptions()
    : m_bEnabled(false)
    , m_pPluginContext(nullptr)
{
    // if no debug option was specified, don't even bother to try.
    // Must ensure that the options slot is null as this is the signal to the
    // platform that debugging is not enabled.
    QVariant debugOptions = QTKPluginFrameworkProperties::getProperty(QTK_DEBUG);
    if (debugOptions.isNull()) {
        return;
    }

    QString strDebugOptionsFilename = debugOptions.toString();

    if (strDebugOptionsFilename.isEmpty()) {
        // default options location is user.dir (install location may be r/o so
        // is not a good candidate for a trace options that need to be updatable by
        // by the user)
        QDir userDir(QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_USER_DIR).toString());
        strDebugOptionsFilename = userDir.absoluteFilePath(OPTIONS);
    }
    QFile optionsFile(strDebugOptionsFilename);
    QString strMsgState;
    if (!optionsFile.exists()) {
        strMsgState = "not found";
    } else {
        QSettings settings(strDebugOptionsFilename, QSettings::IniFormat);
        if (settings.status() != QSettings::NoError) {
            strMsgState = ".... did not parse";
        } else {
            foreach (const QString &strKey, settings.allKeys()) {
                m_mapOptions.insert(strKey, settings.value(strKey));
            }
            m_bEnabled = true;
        }
    }
    qDebug() << "Debug options:\n    " << optionsFile.fileName() << "    " << strMsgState;
}

QTKPluginFrameworkDebugOptions *QTKPluginFrameworkDebugOptions::getDefault()
{
    static QTKPluginFrameworkDebugOptions singleton;
    return &singleton;
}

void QTKPluginFrameworkDebugOptions::start(QTKPluginContext *pPluginContext)
{
    m_pPluginContext = pPluginContext;
    m_pListenerTracker.reset(new QTKServiceTracker<QTKDebugOptionsListener*>(pPluginContext, this));
    m_pListenerTracker->open();
}

void QTKPluginFrameworkDebugOptions::stop(QTKPluginContext *pPluginContext)
{
    Q_UNUSED(pPluginContext)
    m_pListenerTracker->close();
    m_pListenerTracker.reset();
    m_pPluginContext = nullptr;
}

bool QTKPluginFrameworkDebugOptions::getBooleanOption(const QString &strOption, bool bDefaultValue) const
{
    return this->getOption(strOption, bDefaultValue).toBool();
}

QVariant QTKPluginFrameworkDebugOptions::getOption(const QString &strOption) const
{
    return this->getOption(strOption, QVariant());
}

QVariant QTKPluginFrameworkDebugOptions::getOption(const QString &strOption, const QVariant &defaultValue) const
{
    QMutexLocker lock(&m_mutex);
    return m_mapOptions.value(strOption, defaultValue);
}

int QTKPluginFrameworkDebugOptions::getIntegerOption(const QString &strOption, int iDefaultValue) const
{
    return m_mapOptions.value(strOption, iDefaultValue).toInt();
}

QHash<QString, QVariant> QTKPluginFrameworkDebugOptions::getOptions() const
{
    QHash<QString, QVariant> mapSnapShot;
    {
        QMutexLocker lock(&m_mutex);
        if (this->isDebugEnabled()) {
            mapSnapShot = m_mapOptions;
        } else {
            mapSnapShot = m_mapDisabledOptions;
        }
    }
    return mapSnapShot;
}

void QTKPluginFrameworkDebugOptions::setOption(const QString &strOption, const QVariant &value)
{
    if (!this->isDebugEnabled()) {
        return;
    }

    QString strFireChangedEvent;
    {
        QMutexLocker lock(&m_mutex);
        // get the current value
        QHash<QString, QVariant>::iterator currentValue = m_mapOptions.find(strOption);
        if (currentValue != m_mapOptions.end()){
            if (currentValue.value() != value) {
                strFireChangedEvent = this->getSymbolicName(strOption);
            }
        } else {
            if (!value.isNull()) {
                strFireChangedEvent = this->getSymbolicName(strOption);
            }
        }
        if (!strFireChangedEvent.isEmpty()) {
            m_mapOptions.insert(strOption, value);
        }
    }
    // Send the options change event outside the sync block
    if (!strFireChangedEvent.isEmpty()) {
        this->optionsChanged(strFireChangedEvent);
    }
}

void QTKPluginFrameworkDebugOptions::setOptions(const QHash<QString, QVariant> &mapOptions)
{
    QHash<QString, QVariant> mapNewOptions = mapOptions;
    QSet<QString> fireChangesTo;
    {
        QMutexLocker lock(&m_mutex);
        if (!this->isDebugEnabled()) {
            m_mapDisabledOptions = mapNewOptions;
            // no events to fire
            return;
        }
        // first check for removals
        foreach (const QString &strkey, m_mapOptions.keys()) {
            if (!mapNewOptions.contains(strkey)) {
                QString strSymbolicName = this->getSymbolicName(strkey);
                if (!strSymbolicName.isEmpty()) {
                    fireChangesTo.insert(strSymbolicName);
                }
            }
        }
        // now check for changes to existing values
        QHash<QString, QVariant>::iterator iter;
        for(iter = mapNewOptions.begin(); iter != mapNewOptions.end(); ++iter) {
            QVariant existingValue = m_mapOptions.value(iter.key());
            if (iter.value() != existingValue) {
                QString strSymbolicName = this->getSymbolicName(iter.key());
                if (!strSymbolicName.isEmpty()) {
                    fireChangesTo.insert(strSymbolicName);
                }
            }
        }
        // finally set the actual options
        m_mapOptions = mapNewOptions;
    }
    foreach (const QString &strSymbolicName, fireChangesTo) {
        this->optionsChanged(strSymbolicName);
    }
}

void QTKPluginFrameworkDebugOptions::removeOption(const QString &strOption)
{
    if (!this->isDebugEnabled()) {
        return;
    }
    QString strFireChangedEvent;
    {
        QMutexLocker lock(&m_mutex);
        if (m_mapOptions.remove(strOption)) {
            strFireChangedEvent = this->getSymbolicName(strOption);
        }
    }
    // Send the options change event outside the sync block
    if (!strFireChangedEvent.isEmpty()) {
        this->optionsChanged(strFireChangedEvent);
    }
}

bool QTKPluginFrameworkDebugOptions::isDebugEnabled() const
{
    QMutexLocker lock(&m_mutex);
    return m_bEnabled;
}

void QTKPluginFrameworkDebugOptions::setDebugEnabled(bool bEnabled)
{
    bool bFireChangedEvent = false;
    {
        QMutexLocker lock(&m_mutex);
        if (bEnabled) {
            if (this->isDebugEnabled()) {
                return;
            }

            // enable platform debugging - there is no .options file
            QTKPluginFrameworkProperties::setProperty(QTK_DEBUG, QString(""));
            m_mapOptions = this->m_mapDisabledOptions;
            m_mapDisabledOptions.clear();
            m_bEnabled = true;
            if (!m_mapOptions.isEmpty()) {
                // fire changed event to indicate some options were re-enabled
                bFireChangedEvent = true;
            }
        } else {
            if (!this->isDebugEnabled()) {
                return;
            }
            // disable platform debugging.
            QTKPluginFrameworkProperties::clearProperty(QTK_DEBUG);
            if (!m_mapOptions.isEmpty()) {
                // Save the current options off in case debug is re-enabled
                m_mapDisabledOptions = m_mapOptions;
                // fire changed event to indicate some options were disabled
                bFireChangedEvent = true;
            }
            m_mapOptions.clear();
            m_bEnabled = false;
        }
    }
    if (bFireChangedEvent) {
        // need to fire event to listeners that options have been disabled
        this->optionsChanged("*");
    }
}

QString QTKPluginFrameworkDebugOptions::getSymbolicName(const QString &strOption) const
{
    int iFirstSlashIndex = strOption.indexOf("/");
    if (iFirstSlashIndex > 0) {
        return strOption.left(iFirstSlashIndex);
    }
    return QString::null;
}

void QTKPluginFrameworkDebugOptions::optionsChanged(const QString &strBundleSymbolicName)
{
    // use osgi services to get the listeners
    if (nullptr == m_pPluginContext) {
        return;
    }
    // do not use the service tracker because that is only used to call all listeners initially when they are registered
    // here we only want the services with the specified name.
    QList<QTKServiceReference> listServiceReference;
    try {
        QString strFilter = "(" + QLatin1String(QTKDebugOptions::LISTENER_SYMBOLICNAME) +
                "=" + strBundleSymbolicName + ")";
        listServiceReference = m_pPluginContext->getServiceReferences<QTKDebugOptionsListener>(strFilter);
    } catch (const QTKInvalidArgumentException& /*e*/) {
        // consider logging; should not happen
    }
    if (listServiceReference.empty()) {
        return;
    }

    foreach (const QTKServiceReference &reference, listServiceReference) {
        QTKDebugOptionsListener *pService = m_pPluginContext->getService<QTKDebugOptionsListener>(reference);
        if (nullptr == pService) {
            continue;
        }

        try {
            pService->optionsChanged(*this);
        } catch (const std::exception& /*e*/) {
            // TODO consider logging
        }
        m_pPluginContext->ungetService(reference);
    }
}

QTKDebugOptionsListener* QTKPluginFrameworkDebugOptions::addingService(const QTKServiceReference &reference)
{
    QTKDebugOptionsListener *pListener = m_pPluginContext->getService<QTKDebugOptionsListener>(reference);
    pListener->optionsChanged(*this);
    return pListener;
}

void QTKPluginFrameworkDebugOptions::modifiedService(const QTKServiceReference &reference,
                                                     QTKDebugOptionsListener *pService)
{
    Q_UNUSED(reference)
    Q_UNUSED(pService)
}

void QTKPluginFrameworkDebugOptions::removedService(const QTKServiceReference &reference,
                                                    QTKDebugOptionsListener *pService)
{
    Q_UNUSED(pService)
    m_pPluginContext->ungetService(reference);
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
