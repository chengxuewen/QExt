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

#include <private/qextOsgiPlugin_p.h>
#include <private/qextOsgiServiceReference_p.h>
#include <private/qextOsgiServiceRegistration_p.h>
#include <qextOsgiServiceReference.h>
#include <qextOsgiPluginConstants.h>

#include <QStringList>
#include <QMutexLocker>
#include <QDebug>

//----------------------------------------------------------------------------
QExtOsgiServiceReference::QExtOsgiServiceReference()
    : d_ptr(new QExtOsgiServiceReferencePrivate(0))
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceReference::QExtOsgiServiceReference(const QExtOsgiServiceReference& ref)
    : d_ptr(ref.d_ptr)
{
    d_func()->ref.ref();
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference::QExtOsgiServiceReference(QExtOsgiServiceRegistrationPrivate* reg)
    : d_ptr(new QExtOsgiServiceReferencePrivate(reg))
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceReference::operator bool() const
{
    return getPlugin();
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference& QExtOsgiServiceReference::operator=(int null)
{
    if (null == 0)
    {
        if (!d_func()->ref.deref())
            delete d_ptr;
        d_ptr = new QExtOsgiServiceReferencePrivate(0);
    }
    return *this;
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference::~QExtOsgiServiceReference()
{
    if (!d_func()->ref.deref())
        delete d_ptr;
}

//----------------------------------------------------------------------------
QVariant QExtOsgiServiceReference::getProperty(const QString& key) const
{
    Q_D(const QExtOsgiServiceReference);

    QMutexLocker lock(&d->registration->propsLock);

    return d->registration->properties.value(key);
}

//----------------------------------------------------------------------------
QStringList QExtOsgiServiceReference::getPropertyKeys() const
{
    Q_D(const QExtOsgiServiceReference);

    QMutexLocker lock(&d->registration->propsLock);

    return d->registration->properties.keys();
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPlugin> QExtOsgiServiceReference::getPlugin() const
{
    if (d_func()->registration == 0 || d_func()->registration->plugin == 0)
    {
        return QSharedPointer<QExtOsgiPlugin>();
    }

    return d_func()->registration->plugin->q_func().toStrongRef();
}

//----------------------------------------------------------------------------
QList<QSharedPointer<QExtOsgiPlugin> > QExtOsgiServiceReference::getUsingPlugins() const
{
    Q_D(const QExtOsgiServiceReference);

    QMutexLocker lock(&d->registration->propsLock);

    return d->registration->dependents.keys();
}

//----------------------------------------------------------------------------
bool QExtOsgiServiceReference::operator<(const QExtOsgiServiceReference& reference) const
{
    bool sameFw = d_func()->registration->plugin->fwCtx == reference.d_func()->registration->plugin->fwCtx;
    if (!sameFw)
    {
        throw QExtInvalidArgumentException("Can not compare service references "
                                          "belonging to different framework "
                                          "instances.");
    }

    int r1 = getProperty(QExtOsgiPluginConstants::SERVICE_RANKING).toInt();
    int r2 = reference.getProperty(QExtOsgiPluginConstants::SERVICE_RANKING).toInt();

    if (r1 != r2)
    {
        // use ranking if ranking differs
        return r1 < r2;
    }
    else
    {
        qlonglong id1 = getProperty(QExtOsgiPluginConstants::SERVICE_ID).toLongLong();
        qlonglong id2 = reference.getProperty(QExtOsgiPluginConstants::SERVICE_ID).toLongLong();

        // otherwise compare using IDs,
        // is less than if it has a higher ID.
        return id2< id1;
    }
}

//----------------------------------------------------------------------------
bool QExtOsgiServiceReference::operator==(const QExtOsgiServiceReference& reference) const
{
    return d_func()->registration == reference.d_func()->registration;
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference& QExtOsgiServiceReference::operator=(const QExtOsgiServiceReference& reference)
{
    QExtOsgiServiceReferencePrivate* curr_d = d_func();
    d_ptr = reference.d_ptr;
    d_ptr->ref.ref();

    if (!curr_d->ref.deref())
        delete curr_d;

    return *this;
}

//----------------------------------------------------------------------------
uint qHash(const QExtOsgiServiceReference& serviceRef)
{
    return qHash(serviceRef.d_func()->registration);
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtOsgiServiceReference& serviceRef)
{
    dbg.nospace() << "Reference for service object registered from "
                  << serviceRef.getPlugin()->getSymbolicName() << " " << serviceRef.getPlugin()->getVersion()
                  << " (";
    int i = serviceRef.getPropertyKeys().size();
    foreach(QString key, serviceRef.getPropertyKeys())
    {
        dbg.nospace() << key << "=" << serviceRef.getProperty(key).toString();
        if (--i > 0) dbg.nospace() << ",";
    }
    dbg.nospace() << ")";

    return dbg.maybeSpace();
}
