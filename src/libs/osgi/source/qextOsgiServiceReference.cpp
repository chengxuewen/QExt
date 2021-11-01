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

#include "qtkservicereference.h"
#include "qtkplugin_p.h"
#include "qtkpluginconstants.h"
#include "qtkservicereference.h"
#include "qtkservicereference_p.h"
#include "qtkserviceregistration_p.h"

#include <QStringList>
#include <QMutexLocker>
#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKServiceReference::QTKServiceReference()
    : d_ptr(new QTKServiceReferencePrivate(nullptr))
{

}

QTKServiceReference::QTKServiceReference(const QTKServiceReference &serviceRef)
    : d_ptr(serviceRef.d_ptr)
{
    d_func()->m_ref.ref();
}

QTKServiceReference::QTKServiceReference(QTKServiceRegistrationPrivate *pReg)
    : d_ptr(new QTKServiceReferencePrivate(pReg))
{

}

QTKServiceReference::operator bool() const
{
    return this->getPlugin();
}

QTKServiceReference& QTKServiceReference::operator=(int iNull)
{
    if (iNull == 0) {
        if (!d_func()->m_ref.deref()) {
            delete d_ptr;
        }
        d_ptr = new QTKServiceReferencePrivate(nullptr);
    }
    return *this;
}

QTKServiceReference::~QTKServiceReference()
{
    if (!d_func()->m_ref.deref()) {
        delete d_ptr;
    }
}

QVariant QTKServiceReference::getProperty(const QString &strKey) const
{
    Q_D(const QTKServiceReference);

    QMutexLocker locker(&d->m_pRegistration->m_propsLock);
    return d->m_pRegistration->m_properties.value(strKey);
}

QStringList QTKServiceReference::getPropertyKeys() const
{
    Q_D(const QTKServiceReference);

    QMutexLocker locker(&d->m_pRegistration->m_propsLock);
    return d->m_pRegistration->m_properties.keys();
}

QSharedPointer<QTKPlugin> QTKServiceReference::getPlugin() const
{
    if (nullptr == d_func()->m_pRegistration || nullptr == d_func()->m_pRegistration->m_pPluginPrivate) {
        return QSharedPointer<QTKPlugin>();
    }

    return d_func()->m_pRegistration->m_pPluginPrivate->q_func().toStrongRef();
}

QList<QSharedPointer<QTKPlugin> > QTKServiceReference::getUsingPlugins() const
{
    Q_D(const QTKServiceReference);

    QMutexLocker locker(&d->m_pRegistration->m_propsLock);
    return d->m_pRegistration->m_mapDependents.keys();
}

//----------------------------------------------------------------------------
bool QTKServiceReference::operator<(const QTKServiceReference &serviceRef) const
{
    bool bSameFw = d_func()->m_pRegistration->m_pPluginPrivate->m_pPFWContext == serviceRef.d_func()->m_pRegistration->m_pPluginPrivate->m_pPFWContext;
    if (!bSameFw) {
        throw QTKInvalidArgumentException("Can not compare service references "
                                          "belonging to different framework "
                                          "instances.");
    }

    int iR1 = getProperty(QTKPluginConstants::SERVICE_RANKING).toInt();
    int iR2 = serviceRef.getProperty(QTKPluginConstants::SERVICE_RANKING).toInt();

    if (iR1 != iR2) {
        // use ranking if ranking differs
        return iR1 < iR2;
    } else {
        qlonglong llId1 = getProperty(QTKPluginConstants::SERVICE_ID).toLongLong();
        qlonglong llId2 = serviceRef.getProperty(QTKPluginConstants::SERVICE_ID).toLongLong();

        // otherwise compare using IDs,
        // is less than if it has a higher ID.
        return llId2< llId1;
    }
}

bool QTKServiceReference::operator==(const QTKServiceReference &serviceRef) const
{
    return d_func()->m_pRegistration == serviceRef.d_func()->m_pRegistration;
}

QTKServiceReference& QTKServiceReference::operator=(const QTKServiceReference &serviceRef)
{
    QTKServiceReferencePrivate *serviceRefPrivate = d_func();
    d_ptr = serviceRef.d_ptr;
    d_ptr->m_ref.ref();

    if (!serviceRefPrivate->m_ref.deref()) {
        delete serviceRefPrivate;
    }

    return *this;
}

uint qHash(const QTKServiceReference &serviceRef)
{
    QByteArray address((const char *)serviceRef.d_func()->m_pRegistration);
    return qHash(address.toHex());
}

QDebug operator<<(QDebug dbg, const QTKServiceReference &serviceRef)
{
    dbg.nospace() << "Reference for service object registered from "
                  << serviceRef.getPlugin()->getSymbolicName() << " " << serviceRef.getPlugin()->getVersion()
                  << " (";
    int iSize = serviceRef.getPropertyKeys().size();
    foreach (QString strKey, serviceRef.getPropertyKeys()) {
        dbg.nospace() << strKey << "=" << serviceRef.getProperty(strKey).toString();
        if (--iSize > 0) dbg.nospace() << ",";
    }
    dbg.nospace() << ")";

    return dbg.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
