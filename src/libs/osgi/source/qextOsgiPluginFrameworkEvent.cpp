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

#include "qtkpluginframeworkevent.h"
#include "qtkplugin.h"

#include <QTKCore/QTKException>

#include <QString>
#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginFrameworkEventData : public QSharedData
{
public:
    QTKPluginFrameworkEventData(QTKPluginFrameworkEvent::Type eType,
                                QSharedPointer<QTKPlugin> pPlugin,
                                const QString &strExc)
        : m_pPlugin(pPlugin),
          m_strErrorString(strExc),
          m_eType(eType)
    {

    }

    QTKPluginFrameworkEventData(const QTKPluginFrameworkEventData &other)
        : QSharedData(other),
          m_pPlugin(other.m_pPlugin),
          m_strErrorString(other.m_strErrorString),
          m_eType(other.m_eType)
    {

    }

    const QSharedPointer<QTKPlugin>	m_pPlugin;
    const QString m_strErrorString;
    const QTKPluginFrameworkEvent::Type m_eType;
};

QTKPluginFrameworkEvent::QTKPluginFrameworkEvent()
    : d(0)
{

}

QTKPluginFrameworkEvent::QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type eType,
                                                 QSharedPointer<QTKPlugin> pPlugin,
                                                 const QTKException &exception)
    : d(new QTKPluginFrameworkEventData(eType, pPlugin, exception.what()))
{

}

QTKPluginFrameworkEvent::QTKPluginFrameworkEvent(QTKPluginFrameworkEvent::Type eType,
                                                 QSharedPointer<QTKPlugin> pPlugin)
    : d(new QTKPluginFrameworkEventData(eType, pPlugin, QString()))
{

}

QTKPluginFrameworkEvent::QTKPluginFrameworkEvent(const QTKPluginFrameworkEvent &other)
    : d(other.d)
{

}

QTKPluginFrameworkEvent::~QTKPluginFrameworkEvent()
{

}

QTKPluginFrameworkEvent &QTKPluginFrameworkEvent::operator=(const QTKPluginFrameworkEvent &other)
{
    d = other.d;
    return *this;
}

bool QTKPluginFrameworkEvent::isNull() const
{
    return !d;
}

QString QTKPluginFrameworkEvent::getErrorString() const
{
    return d->m_strErrorString;
}

QSharedPointer<QTKPlugin> QTKPluginFrameworkEvent::getPlugin() const
{
    return d->m_pPlugin;
}

QTKPluginFrameworkEvent::Type QTKPluginFrameworkEvent::getType() const
{
    return d->m_eType;
}

QDebug operator<<(QDebug dbg, QTKPluginFrameworkEvent::Type eType)
{
    switch (eType)
    {
    case QTKPluginFrameworkEvent::Type_FrameworkStarted:
        return dbg << "Type_FrameworkStarted";
    case QTKPluginFrameworkEvent::Type_PluginError:
        return dbg << "Type_PluginError";
    case QTKPluginFrameworkEvent::Type_PluginWarning:
        return dbg << "Type_PluginWarning";
    case QTKPluginFrameworkEvent::Type_PluginInfo:
        return dbg << "Type_PluginInfo";
    case QTKPluginFrameworkEvent::Type_FrameworkStopped:
        return dbg << "Type_FrameworkStopped";
    case QTKPluginFrameworkEvent::Type_FrameworkStoppedUpdate:
        return dbg << "Type_FrameworkStoppedUpdate";
    case QTKPluginFrameworkEvent::Type_FrameworkWaitTimeOut:
        return dbg << "FRAMEWORK_WATI_TIMEDOUT";
    default:
        return dbg << "unknown plugin framework event type (" << static_cast<int>(eType) << ")";
    }
}

QDebug operator<<(QDebug dbg, const QTKPluginFrameworkEvent &pfwEvent)
{
    if (pfwEvent.isNull()) {
        return dbg << "NONE";
    }

    QTKPlugin *pPlugin = pfwEvent.getPlugin().data();
    QString strErr = pfwEvent.getErrorString();

    dbg.nospace() << pfwEvent.getType() << " #"
                  << pPlugin->getPluginId() << " ("
                  << pPlugin->getLocation() << ")"
                  << (strErr.isEmpty() ? "" : " exception: ")
                  << strErr;
    return dbg.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
