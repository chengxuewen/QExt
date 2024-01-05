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

#include <private/qextOsgiServices_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiServiceRegistration_p.h>
#include <private/qextOsgiLDAPExpr_p.h>
#include <qextOsgiServiceException.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiServiceFactory.h>

#include <QStringListIterator>
#include <QMutexLocker>
#include <QBuffer>

#include <algorithm>

//----------------------------------------------------------------------------
struct ServiceRegistrationComparator
{
    bool operator()(const QExtOsgiServiceRegistration& a, const QExtOsgiServiceRegistration& b) const
    {
        return a < b;
    }
};

//----------------------------------------------------------------------------
QExtOsgiDictionary QExtOsgiServices::createServiceProperties(const QExtOsgiDictionary& in,
                                                             const QStringList& classes,
                                                             long sid)
{
    static qlonglong nextServiceID = 1;
    QExtOsgiDictionary props = in;

    if (!classes.isEmpty())
    {
        props.insert(QExtOsgiPluginConstants::OBJECTCLASS, classes);
    }

    props.insert(QExtOsgiPluginConstants::SERVICE_ID, sid != -1 ? sid : nextServiceID++);

    return props;
}

//----------------------------------------------------------------------------
QExtOsgiServices::QExtOsgiServices(QExtOsgiPluginFrameworkContext* fwCtx)
    : mutex(), framework(fwCtx)
{

}

//----------------------------------------------------------------------------
QExtOsgiServices::~QExtOsgiServices()
{
    clear();
}

//----------------------------------------------------------------------------
void QExtOsgiServices::clear()
{
    services.clear();
    classServices.clear();
    framework = 0;
}

//----------------------------------------------------------------------------
QExtOsgiServiceRegistration QExtOsgiServices::registerService(QExtOsgiPluginPrivate* plugin,
                                                              const QStringList& classes,
                                                              QObject* service,
                                                              const QExtOsgiDictionary& properties)
{
    if (service == 0)
    {
        throw QExtInvalidArgumentException("Can't register 0 as a service");
    }

    // Check if service implements claimed classes and that they exist.
    for (QStringListIterator i(classes); i.hasNext();)
    {
        QString cls = i.next();
        if (cls.isEmpty())
        {
            throw QExtInvalidArgumentException("Can't register as null class");
        }

        if (!(qobject_cast<QExtOsgiServiceFactory*>(service)))
        {
            if (!checkServiceClass(service, cls))
            {
                QString msg = QString("Service class %1 is not an instance of %2. Maybe you forgot the Q_INTERFACES macro in the service class.")
                                  .arg(service->metaObject()->className()).arg(cls);
                throw QExtInvalidArgumentException(msg);
            }
        }
    }

    QExtOsgiServiceRegistration res(plugin, service,
                                    createServiceProperties(properties, classes));
    {
        QMutexLocker lock(&mutex);
        services.insert(res, classes);
        for (QStringListIterator i(classes); i.hasNext(); )
        {
            QString currClass = i.next();
            QList<QExtOsgiServiceRegistration>& s = classServices[currClass];
            QList<QExtOsgiServiceRegistration>::iterator ip =
                std::lower_bound(s.begin(), s.end(), res, ServiceRegistrationComparator());
            s.insert(ip, res);
        }
    }

    QExtOsgiServiceReference r = res.getReference();
    plugin->fwCtx->listeners.serviceChanged(
        plugin->fwCtx->listeners.getMatchingServiceSlots(r),
        QExtOsgiServiceEvent(QExtOsgiServiceEvent::REGISTERED, r));
    return res;
}

//----------------------------------------------------------------------------
void QExtOsgiServices::updateServiceRegistrationOrder(const QExtOsgiServiceRegistration& sr,
                                                      const QStringList& classes)
{
    QMutexLocker lock(&mutex);
    for (QStringListIterator i(classes); i.hasNext(); )
    {
        QList<QExtOsgiServiceRegistration>& s = classServices[i.next()];
        s.removeAll(sr);
        s.insert(std::lower_bound(s.begin(), s.end(), sr, ServiceRegistrationComparator()), sr);
    }
}

//----------------------------------------------------------------------------
bool QExtOsgiServices::checkServiceClass(QObject* service, const QString& cls) const
{
    return service->inherits(cls.toLatin1());
}

//----------------------------------------------------------------------------
QList<QExtOsgiServiceRegistration> QExtOsgiServices::get(const QString& clazz) const
{
    QMutexLocker lock(&mutex);
    return classServices.value(clazz);
}

//----------------------------------------------------------------------------
QExtOsgiServiceReference QExtOsgiServices::get(QExtOsgiPluginPrivate* plugin, const QString& clazz) const
{
    QMutexLocker lock(&mutex);
    try {
        QList<QExtOsgiServiceReference> srs = get_unlocked(clazz, QString(), plugin);
        if (framework->debug.service_reference)
        {
            qDebug() << "get service ref" << clazz << "for plugin"
                     << plugin->location << " = " << srs.size() << "refs";
        }
        if (!srs.isEmpty()) {
            return srs.front();
        }
    }
    catch (const QExtInvalidArgumentException& )
    { }

    return QExtOsgiServiceReference();
}

//----------------------------------------------------------------------------
QList<QExtOsgiServiceReference> QExtOsgiServices::get(const QString& clazz, const QString& filter,
                                                      QExtOsgiPluginPrivate* plugin) const
{
    QMutexLocker lock(&mutex);
    return get_unlocked(clazz, filter, plugin);
}

//----------------------------------------------------------------------------
QList<QExtOsgiServiceReference> QExtOsgiServices::get_unlocked(const QString& clazz, const QString& filter,
                                                               QExtOsgiPluginPrivate* plugin) const
{
    Q_UNUSED(plugin)

    QListIterator<QExtOsgiServiceRegistration>* s = 0;
    QList<QExtOsgiServiceRegistration> v;
    QExtOsgiLDAPExpr ldap;
    if (clazz.isEmpty())
    {
        if (!filter.isEmpty())
        {
            ldap = QExtOsgiLDAPExpr(filter);
            QSet<QString> matched;
            if (ldap.getMatchedObjectClasses(matched))
            {
                v.clear();
                foreach (QString className, matched)
                {
                    const QList<QExtOsgiServiceRegistration>& cl = classServices[className];
                    v += cl;
                }
                if (!v.isEmpty())
                {
                    s = new QListIterator<QExtOsgiServiceRegistration>(v);
                }
                else
                {
                    return QList<QExtOsgiServiceReference>();
                }
            }
            else
            {
                s = new QListIterator<QExtOsgiServiceRegistration>(services.keys());
            }
        }
        else
        {
            s = new QListIterator<QExtOsgiServiceRegistration>(services.keys());
        }
    }
    else
    {
        QList<QExtOsgiServiceRegistration> v = classServices.value(clazz);
        if (!v.isEmpty())
        {
            s = new QListIterator<QExtOsgiServiceRegistration>(v);
        }
        else
        {
            return QList<QExtOsgiServiceReference>();
        }
        if (!filter.isEmpty())
        {
            ldap = QExtOsgiLDAPExpr(filter);
        }
    }

    QList<QExtOsgiServiceReference> res;
    while (s->hasNext())
    {
        QExtOsgiServiceRegistration sr = s->next();
        QExtOsgiServiceReference sri = sr.getReference();

        if (filter.isEmpty() || ldap.evaluate(sr.d_func()->properties, false))
        {
            res.push_back(sri);
        }
    }

    delete s;

    return res;
}

//----------------------------------------------------------------------------
void QExtOsgiServices::removeServiceRegistration(const QExtOsgiServiceRegistration& sr)
{
    QMutexLocker lock(&mutex);

    QStringList classes = sr.d_func()->properties.value(QExtOsgiPluginConstants::OBJECTCLASS).toStringList();
    services.remove(sr);
    for (QStringListIterator i(classes); i.hasNext(); )
    {
        QString currClass = i.next();
        QList<QExtOsgiServiceRegistration>& s = classServices[currClass];
        if (s.size() > 1)
        {
            s.removeAll(sr);
        }
        else
        {
            classServices.remove(currClass);
        }
    }
}

//----------------------------------------------------------------------------
QList<QExtOsgiServiceRegistration> QExtOsgiServices::getRegisteredByPlugin(QExtOsgiPluginPrivate* p) const
{
    QMutexLocker lock(&mutex);

    QList<QExtOsgiServiceRegistration> res;
    for (QHashIterator<QExtOsgiServiceRegistration, QStringList> i(services); i.hasNext(); )
    {
        QExtOsgiServiceRegistration sr = i.next().key();
        if (sr.d_func()->plugin == p)
        {
            res.push_back(sr);
        }
    }
    return res;
}

//----------------------------------------------------------------------------
QList<QExtOsgiServiceRegistration> QExtOsgiServices::getUsedByPlugin(QSharedPointer<QExtOsgiPlugin> p) const
{
    QMutexLocker lock(&mutex);

    QList<QExtOsgiServiceRegistration> res;
    for (QHashIterator<QExtOsgiServiceRegistration, QStringList> i(services); i.hasNext(); )
    {
        QExtOsgiServiceRegistration sr = i.next().key();
        if (sr.d_func()->isUsedByPlugin(p))
        {
            res.push_back(sr);
        }
    }
    return res;
}

