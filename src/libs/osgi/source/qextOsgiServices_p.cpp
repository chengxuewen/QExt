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

#include "qtkservices_p.h"
#include "qtkservicefactory.h"
#include "qtkpluginconstants.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkserviceexception.h"
#include "qtkserviceregistration_p.h"
#include "qtkldapexpr_p.h"

#include <QStringListIterator>
#include <QMutexLocker>
#include <QBuffer>

#include <algorithm>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

struct ServiceRegistrationComparator
{
    bool operator()(const QTKServiceRegistration &a, const QTKServiceRegistration &b) const {
        return a < b;
    }
};

/**
 * @brief QTKServices::createServiceProperties
 *
 * Creates a new QTKDictionary object containing <code>in</code>
 * with the keys converted to lower case.
 *
 * @param in QTKDictionary object
 * @param listClasses A list of class names which will be added to the created QTKDictionary
 * object under the key QTKPluginConstants::OBJECT_CLASS.
 * @param lId A service id which will be used instead of a default one.
 * @return
 */
QTKDictionary QTKServices::createServiceProperties(const QTKDictionary &in,
                                                   const QStringList &listClasses,
                                                   long lId)
{
    static qlonglong llNextServiceID = 1;
    QTKDictionary props = in;

    if (!listClasses.isEmpty()) {
        props.insert(QTKPluginConstants::OBJECT_CLASS, listClasses);
    }

    props.insert(QTKPluginConstants::SERVICE_ID, lId != -1 ? lId : llNextServiceID++);

    return props;
}

QTKServices::QTKServices(QTKPluginFrameworkContext *pPFWContext)
    : m_mutex(),
      m_pPFWContext(pPFWContext)
{

}

QTKServices::~QTKServices()
{
    this->clear();
}

void QTKServices::clear()
{
    m_mapServices.clear();
    m_mapClassServices.clear();
    m_pPFWContext = nullptr;
}

/**
 * @brief QTKServices::registerService
 * Register a service in the framework wide register.
 *
 * @param pPlugin The plugin registering the service.
 * @param listClasses The class names under which the service can be located.
 * @param pService The service object.
 * @param properties The properties for this service.
 * @return A QTKServiceRegistration object.
 * @exception QTKInvalidArgumentException If one of the following is true:
 * <ul>
 * <li>The service object is 0.</li>
 * <li>The service parameter is not a QTKServiceFactory or an
 * instance of all the named classes in the classes parameter.</li>
 * </ul>
 */
QTKServiceRegistration QTKServices::registerService(QTKPluginPrivate *pPlugin, const QStringList &listClasses,
                                                    QObject *pService, const QTKDictionary &properties)
{
    if (nullptr == pService) {
        throw QTKInvalidArgumentException("Can't register 0 as a service");
    }

    // Check if service implements claimed classes and that they exist.
    for (QStringListIterator iter(listClasses); iter.hasNext();) {
        QString strClass = iter.next();
        if (strClass.isEmpty()) {
            throw QTKInvalidArgumentException("Can't register as null class");
        }

        if (!(qobject_cast<QTKServiceFactory*>(pService))) {
            if (!this->checkServiceClass(pService, strClass)) {
                QString strMsg = QString("Service class %1 is not an instance of %2. Maybe you forgot the Q_INTERFACES macro in the service class.")
                        .arg(pService->metaObject()->className()).arg(strClass);
                throw QTKInvalidArgumentException(strMsg);
            }
        }
    }

    QTKServiceRegistration serviceReg(pPlugin, pService,
                                      QTKServices::createServiceProperties(properties, listClasses));
    {
        QMutexLocker locker(&m_mutex);
        m_mapServices.insert(serviceReg, listClasses);
        for (QStringListIterator iter(listClasses); iter.hasNext();) {
            QString currClass = iter.next();
            QList<QTKServiceRegistration> &listServiceRegs = m_mapClassServices[currClass];
            QList<QTKServiceRegistration>::iterator serviceRegIter = std::lower_bound(listServiceRegs.begin(),
                                                                                      listServiceRegs.end(),
                                                                                      serviceReg,
                                                                                      ServiceRegistrationComparator());
            listServiceRegs.insert(serviceRegIter, serviceReg);
        }
    }

    QTKServiceReference ref = serviceReg.getReference();
    pPlugin->m_pPFWContext->m_listeners.serviceChanged(
                pPlugin->m_pPFWContext->m_listeners.getMatchingServiceSlots(ref),
                QTKServiceEvent(QTKServiceEvent::Type_Registered, ref));
    return serviceReg;
}

/**
 * @brief QTKServices::updateServiceRegistrationOrder
 * Service ranking changed, reorder registered services according to ranking.
 *
 * @param serviceReg The QTKServiceRegistrationPrivate object.
 * @param listClasses New rank of object.
 */
void QTKServices::updateServiceRegistrationOrder(const QTKServiceRegistration &serviceReg,
                                                 const QStringList &listClasses)
{
    QMutexLocker locker(&m_mutex);
    for (QStringListIterator iter(listClasses); iter.hasNext();) {
        QList<QTKServiceRegistration> &listServiceRegs = m_mapClassServices[iter.next()];
        listServiceRegs.removeAll(serviceReg);
        listServiceRegs.insert(std::lower_bound(listServiceRegs.begin(),
                                                listServiceRegs.end(),
                                                serviceReg,
                                                ServiceRegistrationComparator()),
                               serviceReg);
    }
}

/**
 * @brief QTKServices::checkServiceClass
 * Checks that a given service object is an instance of the given class name.
 *
 * @param pService The service object to check.
 * @param strClasse The class name to check for.
 * @return return the check result.
 */
bool QTKServices::checkServiceClass(QObject *pService, const QString &strClasse) const
{
    return pService->inherits(strClasse.toLatin1());
}

/**
 * @brief QTKServices::get
 * Get all services implementing a certain class.
 * Only used internally by the framework.
 *
 * @param strClazz The class name of the requested service.
 * @return A sorted list of {@link QTKServiceRegistrationPrivate} objects.
 */
QList<QTKServiceRegistration> QTKServices::get(const QString &strClazz) const
{
    QMutexLocker locker(&m_mutex);
    return m_mapClassServices.value(strClazz);
}

/**
 * @brief QTKServices::get
 * Get a service implementing a certain class.
 *
 * @param pPlugin The plugin requesting reference
 * @param strClazz The class name of the requested service.
 * @return A {@link QTKServiceReference} object.
 */
QTKServiceReference QTKServices::get(QTKPluginPrivate *pPlugin, const QString &strClazz) const
{
    QMutexLocker locker(&m_mutex);
    try {
        QList<QTKServiceReference> listServiceRefs = this->getUnlocked(strClazz, QString(), pPlugin);
        if (m_pPFWContext->m_debug.bServiceReferenceEnabled) {
            qDebug() << "get service ref" << strClazz
                     << "for plugin" << pPlugin->m_strLocation
                     << " = " << listServiceRefs.size() << "refs";
        }
        if (!listServiceRefs.isEmpty()) {
            return listServiceRefs.front();
        }
    } catch (const QTKInvalidArgumentException &exception) {
        Q_UNUSED(exception)
        //do nothing, ignore exception
    }

    return QTKServiceReference();
}

/**
 * @brief QTKServices::get
 * Get all services implementing a certain class and then
 * filter these with a property filter.
 *
 * @param strClazz The class name of requested service.
 * @param strFilter The property filter.
 * @param pPlugin The plugin requesting reference.
 * @return A list of {@link QTKServiceReference} object.
 */
QList<QTKServiceReference> QTKServices::get(const QString &strClazz, const QString &strFilter,
                                            QTKPluginPrivate *pPlugin) const
{
    QMutexLocker locker(&m_mutex);
    return this->getUnlocked(strClazz, strFilter, pPlugin);
}

QList<QTKServiceReference> QTKServices::getUnlocked(const QString &strClazz, const QString &strFilter,
                                                    QTKPluginPrivate *pPlugin) const
{
    Q_UNUSED(pPlugin)

    QListIterator<QTKServiceRegistration> *pIter = nullptr;
    QList<QTKServiceRegistration> listServiceRegs;
    QTKLDAPExpr ldap;
    if (strClazz.isEmpty()) {
        if (!strFilter.isEmpty()) {
            ldap = QTKLDAPExpr(strFilter);
            QSet<QString> matched;
            if (ldap.getMatchedObjectClasses(matched)) {
                listServiceRegs.clear();
                foreach (QString strClassName, matched) {
                    const QList<QTKServiceRegistration>& cl = m_mapClassServices[strClassName];
                    listServiceRegs += cl;
                }
                if (!listServiceRegs.isEmpty()) {
                    pIter = new QListIterator<QTKServiceRegistration>(listServiceRegs);
                } else {
                    return QList<QTKServiceReference>();
                }
            } else {
                pIter = new QListIterator<QTKServiceRegistration>(m_mapServices.keys());
            }
        } else {
            pIter = new QListIterator<QTKServiceRegistration>(m_mapServices.keys());
        }
    } else {
        QList<QTKServiceRegistration> listServiceRegs = m_mapClassServices.value(strClazz);
        if (!listServiceRegs.isEmpty()) {
            pIter = new QListIterator<QTKServiceRegistration>(listServiceRegs);
        } else {
            return QList<QTKServiceReference>();
        }
        if (!strFilter.isEmpty()) {
            ldap = QTKLDAPExpr(strFilter);
        }
    }

    QList<QTKServiceReference> listServiceRefs;
    while (pIter->hasNext()) {
        QTKServiceRegistration serviceReg = pIter->next();
        QTKServiceReference serviceRef = serviceReg.getReference();

        if (strFilter.isEmpty() || ldap.evaluate(serviceReg.d_func()->m_properties, false)) {
            listServiceRefs.push_back(serviceRef);
        }
    }

    delete pIter;
    return listServiceRefs;
}

/**
 * @brief QTKServices::removeServiceRegistration
 * Remove a registered service.
 *
 * @param serviceReg The QTKServiceRegistration object that is registered.
 */
void QTKServices::removeServiceRegistration(const QTKServiceRegistration &serviceReg)
{
    QMutexLocker locker(&m_mutex);

    QStringList listClasses = serviceReg.d_func()->m_properties.value(QTKPluginConstants::OBJECT_CLASS).toStringList();
    m_mapServices.remove(serviceReg);
    for (QStringListIterator iter(listClasses); iter.hasNext(); ) {
        QString strCurrClass = iter.next();
        QList<QTKServiceRegistration> &listServiceReg = m_mapClassServices[strCurrClass];
        if (listServiceReg.size() > 1) {
            listServiceReg.removeAll(serviceReg);
        } else {
            m_mapClassServices.remove(strCurrClass);
        }
    }
}

/**
 * @brief QTKServices::getRegisteredByPlugin
 * Get all services that a plugin has registered.
 *
 * @param pPluginPrivate The plugin
 * @return A set of {@link QTKServiceRegistration} objects
 */
QList<QTKServiceRegistration> QTKServices::getRegisteredByPlugin(QTKPluginPrivate *pPluginPrivate) const
{
    QMutexLocker locker(&m_mutex);

    QList<QTKServiceRegistration> listServiceRegs;
    for (QHashIterator<QTKServiceRegistration, QStringList> iter(m_mapServices); iter.hasNext();) {
        QTKServiceRegistration serviceReg = iter.next().key();
        if (serviceReg.d_func()->m_pPluginPrivate == pPluginPrivate) {
            listServiceRegs.push_back(serviceReg);
        }
    }
    return listServiceRegs;
}

/**
 * @brief QTKServices::getUsedByPlugin
 * Get all services that a plugin uses.
 *
 * @param pPlugin The plugin
 * @return A set of {@link QTKServiceRegistration} objects
 */
QList<QTKServiceRegistration> QTKServices::getUsedByPlugin(QSharedPointer<QTKPlugin> pPlugin) const
{
    QMutexLocker locker(&m_mutex);

    QList<QTKServiceRegistration> listServiceRegs;
    for (QHashIterator<QTKServiceRegistration, QStringList> iter(m_mapServices); iter.hasNext();) {
        QTKServiceRegistration serviceReg = iter.next().key();
        if (serviceReg.d_func()->isUsedByPlugin(pPlugin)) {
            listServiceRegs.push_back(serviceReg);
        }
    }
    return listServiceRegs;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
