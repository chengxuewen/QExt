#include "qtkmetatypeinformationimpl_p.h"
#include "qtkobjectclassdefinitionimpl_p.h"
#include "qtkattributedefinitionimpl_p.h"

QTKMetaTypeInformationImpl::QTKMetaTypeInformationImpl(const QSharedPointer<QTKPlugin>& plugin, QTKLogService* logger)
    : QTKMetaTypeProviderImpl(plugin, logger)
{

}

QStringList QTKMetaTypeInformationImpl::getPids() const
{
    if (m__mapAllPidOCDs.isEmpty())
    {
        return QStringList();
    }

    return m__mapAllPidOCDs.keys();
}

QStringList QTKMetaTypeInformationImpl::getFactoryPids() const
{
    if (m_map_AllFPidOCDs.isEmpty())
    {
        return QStringList();
    }

    return m_map_AllFPidOCDs.keys();
}

QSharedPointer<QTKPlugin> QTKMetaTypeInformationImpl::getPlugin() const
{
    return this->m__pPlugin;
}

QTKObjectClassDefinitionPtr QTKMetaTypeInformationImpl::getObjectClassDefinition(
        const QString& id, const QLocale& locale)
{
    return QTKMetaTypeProviderImpl::getObjectClassDefinition(id, locale);
}

QList<QLocale> QTKMetaTypeInformationImpl::getLocales() const
{
    return QTKMetaTypeProviderImpl::getLocales();
}
