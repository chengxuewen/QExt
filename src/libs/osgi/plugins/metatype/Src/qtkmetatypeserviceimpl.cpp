#include "qtkmetatypeserviceimpl_p.h"
#include "qtkmetatypeinformationimpl_p.h"
#include "qtkmtprovidertracker_p.h"
#include "qtkobjectclassdefinitionimpl_p.h"
#include "qtkattributedefinitionimpl_p.h"

#include <QTKPluginFramework/Service/Log/QTKLogService>

QTKMetaTypeServiceImpl::QTKMetaTypeServiceImpl(QTKLogService* logger, QTKServiceTracker<>* metaTypeProviderTracker)
    : logger(logger), metaTypeProviderTracker(metaTypeProviderTracker)
{
}

QTKMetaTypeInformationPtr QTKMetaTypeServiceImpl::getMetaTypeInformation(const QSharedPointer<QTKPlugin>& plugin)
{
    QTKMetaTypeInformationPtr mti;
    try
    {
        mti = getMetaTypeProvider(plugin);
    }
    catch (const QTKRuntimeException& )
    {
        QTK_ERROR(logger) << "QTKRuntimeException in QTKMetaTypeInformation::getMetaTypeInformation(QSharedPointer<QTKPlugin> plugin)";
        mti.clear();
    }
    return mti;
}

QTKMetaTypeInformationPtr QTKMetaTypeServiceImpl::getMetaTypeProvider(const QSharedPointer<QTKPlugin>& p)
{
    qlonglong pID = p->getPluginId();
    {
        QMutexLocker lock(&_mtpsMutex);
        if (_mtps.contains(pID))
        {
            return _mtps.value(pID);
        }

        QTKMetaTypeInformationImpl* impl = new QTKMetaTypeInformationImpl(p, logger);
        QTKMetaTypeInformation* mti = impl;
        if (!impl->_isThereMeta)
        {
            delete impl;
            mti = new QTKMTProviderTracker(p, logger, metaTypeProviderTracker);
        }
        QTKMetaTypeInformationPtr mtiPtr(mti);
        _mtps.insert(pID, mtiPtr);
        return mtiPtr;
    }
}

void QTKMetaTypeServiceImpl::pluginChanged(const QTKPluginEvent& event)
{
    QTKPluginEvent::Type type = event.getType();
    qlonglong pID = event.getPlugin()->getPluginId();

    switch (type)
    {
    case QTKPluginEvent::Type_Updated:
    case QTKPluginEvent::Type_Uninstalled:
        _mtps.remove(pID);
        break;
    default :
        break;
    }
}
