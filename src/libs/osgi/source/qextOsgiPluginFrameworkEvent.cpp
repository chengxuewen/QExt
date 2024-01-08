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

#include <qextOsgiPluginFrameworkEvent.h>
#include <qextOsgiPlugin.h>
#include <qextException.h>

#include <QString>
#include <QDebug>

class QExtOsgiPluginFrameworkEventData : public QSharedData
{
public:

    QExtOsgiPluginFrameworkEventData(QExtOsgiPluginFrameworkEvent::Type type, QSharedPointer<QExtOsgiPlugin> plugin, const QString &exc)
        : plugin(plugin), errorString(exc), type(type)
    {

    }

    QExtOsgiPluginFrameworkEventData(const QExtOsgiPluginFrameworkEventData& other)
        : QSharedData(other), plugin(other.plugin), errorString(other.errorString),
        type(other.type)
    {

    }

    /**
   * Plugin related to the event.
   */
    const QSharedPointer<QExtOsgiPlugin>	plugin;

    /**
   * Exception related to the event.
   */
    const QString errorString;

    /**
   * Type of event.
   */
    const QExtOsgiPluginFrameworkEvent::Type type;
};

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent::QExtOsgiPluginFrameworkEvent()
    : d(0)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent::~QExtOsgiPluginFrameworkEvent()
{

}

//----------------------------------------------------------------------------
bool QExtOsgiPluginFrameworkEvent::isNull() const
{
    return !d;
}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent::QExtOsgiPluginFrameworkEvent(Type type, QSharedPointer<QExtOsgiPlugin> plugin, const QExtException &fwException)
    : d(new QExtOsgiPluginFrameworkEventData(type, plugin, fwException.what()))
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent::QExtOsgiPluginFrameworkEvent(Type type, QSharedPointer<QExtOsgiPlugin> plugin)
    : d(new QExtOsgiPluginFrameworkEventData(type, plugin, QString()))
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent::QExtOsgiPluginFrameworkEvent(const QExtOsgiPluginFrameworkEvent &other)
    : d(other.d)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent &QExtOsgiPluginFrameworkEvent::operator=(const QExtOsgiPluginFrameworkEvent &other)
{
    d = other.d;
    return *this;
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginFrameworkEvent::getErrorString() const
{
    return d->errorString;
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPluginFrameworkEvent::getPlugin() const
{
    return d->plugin;
}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkEvent::Type QExtOsgiPluginFrameworkEvent::getType() const
{
    return d->type;
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, QExtOsgiPluginFrameworkEvent::Type type)
{
    switch (type)
    {
    case QExtOsgiPluginFrameworkEvent::FRAMEWORK_STARTED:        return dbg << "FRAMEWORK_STARTED";
    case QExtOsgiPluginFrameworkEvent::PLUGIN_ERROR:          return dbg << "PLUGIN_ERROR";
    case QExtOsgiPluginFrameworkEvent::PLUGIN_WARNING:        return dbg << "PLUGIN_WARNING";
    case QExtOsgiPluginFrameworkEvent::PLUGIN_INFO:           return dbg << "PLUGIN_INFO";
    case QExtOsgiPluginFrameworkEvent::FRAMEWORK_STOPPED:        return dbg << "FRAMEWORK_STOPPED";
    case QExtOsgiPluginFrameworkEvent::FRAMEWORK_STOPPED_UPDATE: return dbg << "FRAMEWORK_STOPPED_UPDATE";
    case QExtOsgiPluginFrameworkEvent::FRAMEWORK_WAIT_TIMEDOUT:  return dbg << "FRAMEWORK_WATI_TIMEDOUT";

    default: return dbg << "unknown plugin framework event type (" << static_cast<int>(type) << ")";
    }
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtOsgiPluginFrameworkEvent &event)
{
    if (event.isNull()) return dbg << "NONE";

    QExtOsgiPlugin* p = event.getPlugin().data();
    QString err = event.getErrorString();

    dbg.nospace() << event.getType() << " #" << p->getPluginId() << " ("
                  << p->getLocation() << ")" << (err.isEmpty() ? "" : " exception: ") << err;
    return dbg.maybeSpace();
}
