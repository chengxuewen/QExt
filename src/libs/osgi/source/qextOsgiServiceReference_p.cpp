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

#include "qtkservicereference_p.h"
#include "qtkplugin_p.h"
#include "qtkpluginconstants.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkservicefactory.h"
#include "qtkserviceexception.h"
#include "qtkservices_p.h"
#include "qtkserviceregistration_p.h"

#include <QObject>
#include <QMutexLocker>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKServiceReferencePrivate::QTKServiceReferencePrivate(QTKServiceRegistrationPrivate *pServiceRegPrivate)
    : m_ref(1),
      m_pRegistration(pServiceRegPrivate)
{
    if (m_pRegistration) {
        m_pRegistration->m_ref.ref();
    }
}

QTKServiceReferencePrivate::~QTKServiceReferencePrivate()
{
    if (m_pRegistration && !m_pRegistration->m_ref.deref()) {
        delete m_pRegistration;
    }
}

QObject *QTKServiceReferencePrivate::getService(QSharedPointer<QTKPlugin> pPlugin)
{
    QObject *pService = nullptr;

    QMutexLocker locker(&m_pRegistration->m_propsLock);
    if (m_pRegistration->m_bAvailable) {
        int iCount = m_pRegistration->m_mapDependents.value(pPlugin);
        if (iCount == 0) {
            QStringList listClasses = m_pRegistration->m_properties.value(QTKPluginConstants::OBJECT_CLASS).toStringList();
            m_pRegistration->m_mapDependents[pPlugin] = 1;
            if (QTKServiceFactory *pServiceFactory = qobject_cast<QTKServiceFactory*>(m_pRegistration->getService())) {
                try {
                    pService = pServiceFactory->getService(pPlugin, QTKServiceRegistration(m_pRegistration));
                } catch (const QTKException &exception) {
                    QTKServiceException serviceException("QTKServiceFactory throw an exception",
                                                         QTKServiceException::Type_FactoryException, exception);
                    pPlugin->d_func()->m_pPFWContext->m_listeners.frameworkError(m_pRegistration->m_pPluginPrivate->q_func(), serviceException);
                    return nullptr;
                }
                if (nullptr == pService) {
                    QTKServiceException serviceException("QTKServiceFactory produced null",
                                                         QTKServiceException::Type_FactoryError);
                    pPlugin->d_func()->m_pPFWContext->m_listeners.frameworkError(m_pRegistration->m_pPluginPrivate->q_func(), serviceException);
                    return nullptr;
                }
                for (QStringListIterator iter(listClasses); iter.hasNext(); ) {
                    QString strClasses = iter.next();
                    if (!m_pRegistration->m_pPluginPrivate->m_pPFWContext->m_pServices->checkServiceClass(pService, strClasses)) {
                        QTKServiceException serviceException(QString("QTKServiceFactory produced an object ") +
                                                             "that did not implement: " + strClasses,
                                                             QTKServiceException::Type_FactoryError);
                        pPlugin->d_func()->m_pPFWContext->m_listeners.frameworkError(m_pRegistration->m_pPluginPrivate->q_func(), serviceException);
                        return 0;
                    }
                }
                m_pRegistration->m_mapServiceInstances.insert(pPlugin, pService);
            } else {
                pService = m_pRegistration->getService();
            }
        } else {
            m_pRegistration->m_mapDependents.insert(pPlugin, iCount + 1);
            if (qobject_cast<QTKServiceFactory*>(m_pRegistration->getService())) {
                pService = m_pRegistration->m_mapServiceInstances.value(pPlugin);
            } else {
                pService = m_pRegistration->getService();
            }
        }
    }

    return pService;
}

bool QTKServiceReferencePrivate::ungetService(QSharedPointer<QTKPlugin> pPlugin, bool bCheckRefCounter)
{
    QMutexLocker locker(&m_pRegistration->m_propsLock);
    bool bHadReferences = false;
    bool bRemoveService = false;

    int iCount= m_pRegistration->m_mapDependents.value(pPlugin);
    if (iCount > 0) {
        bHadReferences = true;
    }

    if(bCheckRefCounter) {
        if (iCount > 1) {
            m_pRegistration->m_mapDependents[pPlugin] = iCount - 1;
        } else if(iCount == 1) {
            bRemoveService = true;
        }
    } else {
        bRemoveService = true;
    }

    if (bRemoveService) {
        QObject *pServiceInstance = m_pRegistration->m_mapServiceInstances[pPlugin];
        m_pRegistration->m_mapServiceInstances.remove(pPlugin);
        if (nullptr != pServiceInstance) {
            try {
                qobject_cast<QTKServiceFactory*>(m_pRegistration->getService())->ungetService(pPlugin, QTKServiceRegistration(m_pRegistration), pServiceInstance);
            } catch (const QTKException &exception) {
                pPlugin->d_func()->m_pPFWContext->m_listeners.frameworkError(m_pRegistration->m_pPluginPrivate->q_func(), exception);
            }
        }
        m_pRegistration->m_mapDependents.remove(pPlugin);
    }

    return bHadReferences;
}

const QTKServiceProperties &QTKServiceReferencePrivate::getProperties() const
{
    return m_pRegistration->m_properties;
}

QVariant QTKServiceReferencePrivate::getProperty(const QString &strKey, bool bLock) const
{
    if (bLock) {
        QMutexLocker locker(&m_pRegistration->m_propsLock);
        return m_pRegistration->m_properties.value(strKey);
    }
    return m_pRegistration->m_properties.value(strKey);
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
