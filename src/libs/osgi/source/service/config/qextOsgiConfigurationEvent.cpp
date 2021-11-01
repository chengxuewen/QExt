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

#include "qtkconfigurationevent.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKConfigurationEventData : public QSharedData
{
public:
    QTKConfigurationEventData(const QTKServiceReference& reference,
                              QTKConfigurationEvent::Type type,
                              const QString& factoryPid,
                              const QString& pid)
        : type(type), factoryPid(factoryPid), pid(pid), reference(reference)
    {

    }

    QTKConfigurationEventData(const QTKConfigurationEventData& other)
        : QSharedData(other), type(other.type), factoryPid(other.factoryPid),
          pid(other.pid), reference(other.reference)
    {

    }

    /**
   * Type of this event.
   */
    const QTKConfigurationEvent::Type type;

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
    const QTKServiceReference reference;
};

//----------------------------------------------------------------------------
QTKConfigurationEvent::QTKConfigurationEvent()
    : d(0)
{

}

//----------------------------------------------------------------------------
QTKConfigurationEvent::~QTKConfigurationEvent()
{

}

//----------------------------------------------------------------------------
bool QTKConfigurationEvent::isNull() const
{
    return !d;
}

//----------------------------------------------------------------------------
QTKConfigurationEvent::QTKConfigurationEvent(const QTKServiceReference& reference,
                                             Type type, const QString& factoryPid,
                                             const QString& pid)
    : d(new QTKConfigurationEventData(reference, type, factoryPid, pid))
{
    if (pid.isNull())
    {
        throw QTKInvalidArgumentException("pid must not be null");
    }
}

//----------------------------------------------------------------------------
QTKConfigurationEvent::QTKConfigurationEvent(const QTKConfigurationEvent& other)
    : d(other.d)
{

}

//----------------------------------------------------------------------------
QTKConfigurationEvent& QTKConfigurationEvent::operator=(const QTKConfigurationEvent& other)
{
    d = other.d;
    return *this;
}

//----------------------------------------------------------------------------
QString QTKConfigurationEvent::getFactoryPid() const
{
    return d->factoryPid;
}

//----------------------------------------------------------------------------
QString QTKConfigurationEvent::getPid() const
{
    return d->pid;
}

//----------------------------------------------------------------------------
int QTKConfigurationEvent::getType() const
{
    return d->type;
}

//----------------------------------------------------------------------------
QTKServiceReference QTKConfigurationEvent::getReference() const
{
    return d->reference;
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, QTKConfigurationEvent::Type type)
{
    switch (type)
    {
    case QTKConfigurationEvent::CM_UPDATED: return dbg << "CM_UPDATED";
    case QTKConfigurationEvent::CM_DELETED: return dbg << "CM_DELETED";

    default: return dbg << "unknown configuration event type (" << static_cast<int>(type) << ")";
    }
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QTKConfigurationEvent& event)
{
    if (event.isNull()) return dbg << "NONE";

    dbg.nospace() << event.getType() << (event.getFactoryPid().isEmpty() ? " " : event.getFactoryPid() + ", ")
                  << "pid=" << event.getPid();
    return dbg.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
