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

#include "qtkserviceevent.h"
#include "qtkservicereference.h"
#include "qtkpluginconstants.h"

#include <QStringList>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKServiceEventData : public QSharedData
{
public:
    QTKServiceEventData(QTKServiceEvent::Type eType, const QTKServiceReference &reference)
        : m_eType(eType),
          m_reference(reference)
    {

    }

    QTKServiceEventData(const QTKServiceEventData &other)
        : QSharedData(other),
          m_eType(other.m_eType),
          m_reference(other.m_reference)
    {

    }

    const QTKServiceEvent::Type m_eType;
    const QTKServiceReference m_reference;
};

QTKServiceEvent::QTKServiceEvent()
    : d(0)
{

}

QTKServiceEvent::~QTKServiceEvent()
{

}

bool QTKServiceEvent::isNull() const
{
    return !d;
}

QTKServiceEvent::QTKServiceEvent(Type eType, const QTKServiceReference &reference)
    : d(new QTKServiceEventData(eType, reference))
{

}

QTKServiceEvent::QTKServiceEvent(const QTKServiceEvent &other)
    : d(other.d)
{

}

QTKServiceEvent& QTKServiceEvent::operator=(const QTKServiceEvent &other)
{
    d = other.d;
    return *this;
}

QTKServiceReference QTKServiceEvent::getServiceReference() const
{
    return d->m_reference;
}

QTKServiceEvent::Type QTKServiceEvent::getType() const
{
    return d->m_eType;
}

const char *QTKServiceEvent::getTypeName(const QTKServiceEvent::Type &eType)
{
    switch(eType)
    {
    case QTKServiceEvent::Type_Modified:
        return "Type_Modified";
    case QTKServiceEvent::Type_ModifiedEndMatch:
        return "Type_ModifiedEndMatch";
    case QTKServiceEvent::Type_Registered:
        return "Type_Registered";
    case QTKServiceEvent::Type_Unregistering:
        return "Type_Unregistering";
    default:
        return QString("unknown service event type (" + QString::number(static_cast<int>(eType)) + ")").toLatin1().data();
    }
}

QDebug operator<<(QDebug dbg, QTKServiceEvent::Type eType)
{
    return dbg << QTKServiceEvent::getTypeName(eType);
}

QDebug operator<<(QDebug dbg, const QTKServiceEvent &event)
{
    if (event.isNull()) {
        return dbg << "NONE";
    }

    QTKServiceReference serviceReference = event.getServiceReference();
    // Some events will not have a service reference
    qlonglong llId = serviceReference.getProperty(QTKPluginConstants::SERVICE_ID).toLongLong();
    QStringList listClasses = serviceReference.getProperty(QTKPluginConstants::OBJECT_CLASS).toStringList();

    dbg.nospace() << event.getType() << " " << llId << " objectClass=" << listClasses;
    return dbg.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
