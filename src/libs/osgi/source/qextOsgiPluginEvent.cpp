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

#include "qtkpluginevent.h"
#include "qtkplugin.h"

#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginEventData : public QSharedData
{
public:
    QTKPluginEventData(QTKPluginEvent::Type eType, QSharedPointer<QTKPlugin> pPlugin)
        : m_eType(eType),
          m_pPlugin(pPlugin)
    {

    }

    QTKPluginEventData(const QTKPluginEventData &other)
        : QSharedData(other),
          m_eType(other.m_eType),
          m_pPlugin(other.m_pPlugin)
    {

    }

    const QTKPluginEvent::Type m_eType;
    const QSharedPointer<QTKPlugin> m_pPlugin;
};

QTKPluginEvent::QTKPluginEvent()
    : d(0)
{

}

QTKPluginEvent::QTKPluginEvent(QTKPluginEvent::Type eType, QSharedPointer<QTKPlugin> pPlugin)
    : d(new QTKPluginEventData(eType, pPlugin))
{

}

QTKPluginEvent::QTKPluginEvent(const QTKPluginEvent &other)
    : d(other.d)
{

}

QTKPluginEvent::~QTKPluginEvent()
{

}

bool QTKPluginEvent::isNull() const
{
    return !d;
}

QSharedPointer<QTKPlugin> QTKPluginEvent::getPlugin() const
{
    return d->m_pPlugin;
}

QTKPluginEvent::Type QTKPluginEvent::getType() const
{
    return d->m_eType;
}

QTKPluginEvent &QTKPluginEvent::operator=(const QTKPluginEvent &other)
{
    d = other.d;
    return *this;
}

QDebug operator<<(QDebug debug, QTKPluginEvent::Type eEventType)
{
    switch (eEventType)
    {
    case QTKPluginEvent::Type_Installed:
        return debug << "INSTALLED";
    case QTKPluginEvent::Type_Started:
        return debug << "STARTED";
    case QTKPluginEvent::Type_Stopped:
        return debug << "STOPPED";
    case QTKPluginEvent::Type_Updated:
        return debug << "UPDATED";
    case QTKPluginEvent::Type_Uninstalled:
        return debug << "UNINSTALLED";
    case QTKPluginEvent::Type_Resolved:
        return debug << "RESOLVED";
    case QTKPluginEvent::Type_Unresolved:
        return debug << "UNRESOLVED";
    case QTKPluginEvent::Type_Starting:
        return debug << "STARTING";
    case QTKPluginEvent::Type_Stopping:
        return debug << "STOPPING";
    case QTKPluginEvent::Type_LazyActivation:
        return debug << "LAZY_ACTIVATION";
    default:
        return debug << "Unknown plugin event type (" << static_cast<int>(eEventType) << ")";
    }
}

QDebug operator<<(QDebug debug, const QTKPluginEvent &event)
{
    if (event.isNull()) {
        return debug << "NONE";
    }

    QSharedPointer<QTKPlugin> pPlugin = event.getPlugin();
    debug.nospace() << event.getType() << " #" << pPlugin->getPluginId() << " (" << pPlugin->getLocation() << ")";
    return debug.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
