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

#include <qextOsgiPluginEvent.h>
#include <qextOsgiPlugin.h>

#include <QDebug>

class QExtOsgiPluginEventData : public QSharedData
{
public:

  QExtOsgiPluginEventData(QExtOsgiPluginEvent::Type type, QSharedPointer<QExtOsgiPlugin> plugin)
    : type(type), plugin(plugin)
  {

  }

  QExtOsgiPluginEventData(const QExtOsgiPluginEventData& other)
    : QSharedData(other), type(other.type), plugin(other.plugin)
  {

  }

  const QExtOsgiPluginEvent::Type type;
  const QSharedPointer<QExtOsgiPlugin> plugin;
};

//----------------------------------------------------------------------------
QExtOsgiPluginEvent::QExtOsgiPluginEvent()
  : d(0)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginEvent::~QExtOsgiPluginEvent()
{

}

//----------------------------------------------------------------------------
bool QExtOsgiPluginEvent::isNull() const
{
  return !d;
}

//----------------------------------------------------------------------------
QExtOsgiPluginEvent::QExtOsgiPluginEvent(Type type, QSharedPointer<QExtOsgiPlugin> plugin)
  : d(new QExtOsgiPluginEventData(type, plugin))
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginEvent::QExtOsgiPluginEvent(const QExtOsgiPluginEvent &other)
  : d(other.d)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginEvent &QExtOsgiPluginEvent::operator=(const QExtOsgiPluginEvent &other)
{
  d = other.d;
  return *this;
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiPluginEvent::getPlugin() const
{
  return d->plugin;
}

//----------------------------------------------------------------------------
QExtOsgiPluginEvent::Type QExtOsgiPluginEvent::getType() const
{
  return d->type;
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug debug, QExtOsgiPluginEvent::Type eventType)
{
  switch (eventType)
  {
  case QExtOsgiPluginEvent::INSTALLED:       return debug << "INSTALLED";
  case QExtOsgiPluginEvent::STARTED:         return debug << "STARTED";
  case QExtOsgiPluginEvent::STOPPED:         return debug << "STOPPED";
  case QExtOsgiPluginEvent::UPDATED:         return debug << "UPDATED";
  case QExtOsgiPluginEvent::UNINSTALLED:     return debug << "UNINSTALLED";
  case QExtOsgiPluginEvent::RESOLVED:        return debug << "RESOLVED";
  case QExtOsgiPluginEvent::UNRESOLVED:      return debug << "UNRESOLVED";
  case QExtOsgiPluginEvent::STARTING:        return debug << "STARTING";
  case QExtOsgiPluginEvent::STOPPING:        return debug << "STOPPING";
  case QExtOsgiPluginEvent::LAZY_ACTIVATION: return debug << "LAZY_ACTIVATION";

  default: return debug << "Unknown plugin event type (" << static_cast<int>(eventType) << ")";
  }
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug debug, const QExtOsgiPluginEvent &event)
{
  if (event.isNull()) return debug << "NONE";

  QSharedPointer<QExtOsgiPlugin> p = event.getPlugin();
  debug.nospace() << event.getType() << " #" << p->getPluginId() << " (" << p->getLocation() << ")";
  return debug.maybeSpace();
}
