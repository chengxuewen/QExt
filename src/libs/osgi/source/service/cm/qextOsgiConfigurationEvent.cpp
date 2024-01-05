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


#include <qext/osgi/service/cm/qextOsgiConfigurationEvent.h>
#include <qextException.h>

class QExtOsgiConfigurationEventData : public QSharedData
{
public:

  QExtOsgiConfigurationEventData(const QExtOsgiServiceReference& reference,
                            QExtOsgiConfigurationEvent::Type type,
                            const QString& factoryPid,
                            const QString& pid)
    : type(type), factoryPid(factoryPid), pid(pid), reference(reference)
  {

  }

  QExtOsgiConfigurationEventData(const QExtOsgiConfigurationEventData& other)
    : QSharedData(other), type(other.type), factoryPid(other.factoryPid),
      pid(other.pid), reference(other.reference)
  {

  }

  /**
   * Type of this event.
   */
  const QExtOsgiConfigurationEvent::Type type;

  /**
   * The factory pid associated with this event.
   */
  const QString factoryPid;

  /**
   * The pid associated with this event.
   */
  const QString pid;

  /**
   * The ConfigurationAdmin service which created this event.
   */
  const QExtOsgiServiceReference reference;
};

//----------------------------------------------------------------------------
QExtOsgiConfigurationEvent::QExtOsgiConfigurationEvent()
  : d(0)
{

}

//----------------------------------------------------------------------------
QExtOsgiConfigurationEvent::~QExtOsgiConfigurationEvent()
{

}

//----------------------------------------------------------------------------
bool QExtOsgiConfigurationEvent::isNull() const
{
  return !d;
}

//----------------------------------------------------------------------------
QExtOsgiConfigurationEvent::QExtOsgiConfigurationEvent(const QExtOsgiServiceReference& reference,
                      Type type, const QString& factoryPid,
                      const QString& pid)
  : d(new QExtOsgiConfigurationEventData(reference, type, factoryPid, pid))
{
  if (pid.isNull())
  {
    throw QExtInvalidArgumentException("pid must not be null");
  }
}

//----------------------------------------------------------------------------
QExtOsgiConfigurationEvent::QExtOsgiConfigurationEvent(const QExtOsgiConfigurationEvent& other)
  : d(other.d)
{

}

//----------------------------------------------------------------------------
QExtOsgiConfigurationEvent& QExtOsgiConfigurationEvent::operator=(const QExtOsgiConfigurationEvent& other)
{
  d = other.d;
  return *this;
}

//----------------------------------------------------------------------------
QString QExtOsgiConfigurationEvent::getFactoryPid() const
{
  return d->factoryPid;
}

//----------------------------------------------------------------------------
QString QExtOsgiConfigurationEvent::getPid() const
{
  return d->pid;
}

//----------------------------------------------------------------------------
int QExtOsgiConfigurationEvent::getType() const
{
  return d->type;
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference QExtOsgiConfigurationEvent::getReference() const
{
  return d->reference;
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, QExtOsgiConfigurationEvent::Type type)
{
  switch (type)
  {
  case QExtOsgiConfigurationEvent::CM_UPDATED: return dbg << "CM_UPDATED";
  case QExtOsgiConfigurationEvent::CM_DELETED: return dbg << "CM_DELETED";

  default: return dbg << "unknown configuration event type (" << static_cast<int>(type) << ")";
  }
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtOsgiConfigurationEvent& event)
{
  if (event.isNull()) return dbg << "NONE";

  dbg.nospace() << event.getType() << (event.getFactoryPid().isEmpty() ? " " : event.getFactoryPid() + ", ")
                   << "pid=" << event.getPid();
  return dbg.maybeSpace();
}
