#ifndef QTKMETATYPEINFORMATIONIMPL_P_H
#define QTKMETATYPEINFORMATIONIMPL_P_H

#include "qtkmetatypeproviderimpl_p.h"

#include <QTKPluginFramework/Service/Metatype/QTKMetaTypeInformation>
#include <QTKPluginFramework/Service/Log/QTKLogService>
#include <QTKPluginFramework/QTKPlugin>

#include <QStringList>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * Implementation of QTKMetaTypeInformation
 * <p>
 * Extension of QTKMetaTypeProvider
 * <p>
 * Provides methods to:
 * <p> - getPids() get the Pids for a given QLocale
 * <p> - getFactoryPids() get the Factory Pids for a given QLocale
 * <p>
 */
class QTKMetaTypeInformationImpl : public QTKMetaTypeProviderImpl, public QTKMetaTypeInformation
{

public:

    /**
   * Constructor of class QTKMetaTypeInformationImpl.
   */
    QTKMetaTypeInformationImpl(const QSharedPointer<QTKPlugin>& plugin, QTKLogService* m_pLogger);

    /*
   * @see QTKMetaTypeInformation#getPids()
   */
    QStringList getPids() const;

    /*
   * @see QTKMetaTypeInformation#getFactoryPids()
   */
    QStringList getFactoryPids() const;

    /*
   * @see QTKMetaTypeInformation#getPlugin()
   */
    QSharedPointer<QTKPlugin> getPlugin() const;

    /*
   * @see QTKMetaTypeProviderImpl#getLocales()
   */
    QTKObjectClassDefinitionPtr getObjectClassDefinition(
            const QString& id, const QLocale& locale = QLocale());

    /*
   * @see QTKMetaTypeProviderImpl#getLocales()
   */
    QList<QLocale> getLocales() const;
};

#endif // QTKMETATYPEINFORMATIONIMPL_P_H
