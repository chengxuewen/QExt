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

#include <qextOsgiServiceEvent.h>
#include <qextOsgiServiceReference.h>
#include <qextOsgiPluginConstants.h>

#include <QStringList>

//----------------------------------------------------------------------------
class QExtOsgiServiceEventData : public QSharedData
{
public:

    QExtOsgiServiceEventData(QExtOsgiServiceEvent::Type type, const QExtOsgiServiceReference &reference)
        : type(type), reference(reference)
    {

    }

    QExtOsgiServiceEventData(const QExtOsgiServiceEventData& other)
        : QSharedData(other), type(other.type), reference(other.reference)
    {

    }

    const QExtOsgiServiceEvent::Type type;
    const QExtOsgiServiceReference reference;
};

//----------------------------------------------------------------------------
QExtOsgiServiceEvent::QExtOsgiServiceEvent()
    : d(0)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceEvent::~QExtOsgiServiceEvent()
{

}

//----------------------------------------------------------------------------
bool QExtOsgiServiceEvent::isNull() const
{
    return !d;
}

//----------------------------------------------------------------------------
QExtOsgiServiceEvent::QExtOsgiServiceEvent(Type type, const QExtOsgiServiceReference &reference)
    : d(new QExtOsgiServiceEventData(type, reference))
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceEvent::QExtOsgiServiceEvent(const QExtOsgiServiceEvent &other)
    : d(other.d)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceEvent &QExtOsgiServiceEvent::operator=(const QExtOsgiServiceEvent &other)
{
    d = other.d;
    return *this;
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference QExtOsgiServiceEvent::getServiceReference() const
{
    return d->reference;
}

//----------------------------------------------------------------------------
QExtOsgiServiceEvent::Type QExtOsgiServiceEvent::getType() const
{
    return d->type;
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, QExtOsgiServiceEvent::Type type)
{
    switch(type)
    {
    case QExtOsgiServiceEvent::MODIFIED:          return dbg << "MODIFIED";
    case QExtOsgiServiceEvent::MODIFIED_ENDMATCH: return dbg << "MODIFIED_ENDMATCH";
    case QExtOsgiServiceEvent::REGISTERED:        return dbg << "REGISTERED";
    case QExtOsgiServiceEvent::UNREGISTERING:     return dbg << "UNREGISTERING";

    default: return dbg << "unknown service event type (" << static_cast<int>(type) << ")";
    }
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtOsgiServiceEvent &event)
{
    if (event.isNull()) return dbg << "NONE";

    QExtOsgiServiceReference sr = event.getServiceReference();
    // Some events will not have a service reference
    qlonglong sid = sr.getProperty(QExtOsgiPluginConstants::SERVICE_ID).toLongLong();
    QStringList classes = sr.getProperty(QExtOsgiPluginConstants::OBJECTCLASS).toStringList();

    dbg.nospace() << event.getType() << " " << sid << " objectClass=" << classes;
    return dbg.maybeSpace();
}
