#ifndef QTKMTPROVIDERTRACKER_P_H
#define QTKMTPROVIDERTRACKER_P_H

#include <QTKPluginFramework/Service/Metatype/QTKMetaTypeInformation>
#include <QTKPluginFramework/QTKServiceTracker>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKMTProviderTracker : public QTKMetaTypeInformation
{

private:

    const QSharedPointer<QTKPlugin> _plugin;
    QTKLogService* const log;
    QTKServiceTracker<>* _tracker;

public:

    // this is a simple class just used to temporarily store information about a provider
    // it is public because qHash() needs access to it
    class MetaTypeProviderWrapper;

    /**
   * Constructs a QTKMTProviderTracker which tracks all QTKMetaTypeProviders
   * registered by the specified plugin.
   * @param context The QTKPluginContext of the QTKMetaTypeService implementation
   * @param plugin The plugin to track all QTKMetaTypeProviders for.
   * @param log The <code>QTKLogService</code> to use for logging messages.
   */
    QTKMTProviderTracker(const QSharedPointer<QTKPlugin>& plugin, QTKLogService* log, QTKServiceTracker<>* tracker);

    QStringList getPids() const;
    QStringList getFactoryPids() const;
    QSharedPointer<QTKPlugin> getPlugin() const;
    QTKObjectClassDefinitionPtr getObjectClassDefinition(const QString& id, const QLocale& locale);
    QList<QLocale> getLocales() const;

private:

    QStringList getPids(bool factory) const;

    QSet<MetaTypeProviderWrapper> getMetaTypeProviders() const;

    void addMetaTypeProviderWrappers(const QString& servicePropertyName,
                                     const QTKServiceReference& serviceReference,
                                     QTKMetaTypeProvider* service, bool factory,
                                     QSet<MetaTypeProviderWrapper>& wrappers) const;

    QStringList getStringProperty(const QString& name, const QVariant& value) const;

};

#endif // QTKMTPROVIDERTRACKER_P_H
