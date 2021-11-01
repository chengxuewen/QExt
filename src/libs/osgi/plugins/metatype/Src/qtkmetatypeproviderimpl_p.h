#ifndef QTKMETATYPEPROVIDERIMPL_P_H
#define QTKMETATYPEPROVIDERIMPL_P_H

#include <QTKPluginFramework/Service/Metatype/QTKMetaTypeProvider>
#include <QTKPluginFramework/Service/Log/QTKLogService>
#include <QTKPluginFramework/QTKPlugin>

#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKObjectClassDefinitionImpl;

/**
 * Implementation of QTKMetaTypeProvider
 */
class QTKMetaTypeProviderImpl : public QTKMetaTypeProvider
{

public:

    static const QString METADATA_NOT_FOUND; // = "METADATA_NOT_FOUND"
    static const QString OCD_ID_NOT_FOUND; // = "OCD_ID_NOT_FOUND"
    static const QString ASK_INVALID_LOCALE; // = "ASK_INVALID_LOCALE"

    static const QString META_FILE_EXT; // = ".XML";
    static const QString RESOURCE_FILE_CONN; // = "_"
    static const QString RESOURCE_FILE_EXT; // = ".qm"
    static const QChar DIRECTORY_SEP; // = '/'

protected:

    QSharedPointer<QTKPlugin> m__pPlugin;
    QHash<QString, QSharedPointer<QTKObjectClassDefinitionImpl> > m__mapAllPidOCDs;
    QHash<QString, QSharedPointer<QTKObjectClassDefinitionImpl> > m_map_AllFPidOCDs;
    QTKLogService *m_pLogger;

private:

    mutable QList<QLocale> _locales;
    bool _isThereMeta;

    friend class QTKMetaTypeServiceImpl;

public:

    /**
   * Constructor of class MetaTypeProviderImpl.
   */
    QTKMetaTypeProviderImpl(const QSharedPointer<QTKPlugin>& plugin, QTKLogService* m_pLogger);

    /*
   * @see QTKMetaTypeProvider#getObjectClassDefinition(const QString&, const QLocale&)
   */
    QTKObjectClassDefinitionPtr getObjectClassDefinition(const QString& pid, const QLocale& locale);

    /*
   * @see QTKMetaTypeProvider#getLocales()
   */
    QList<QLocale> getLocales() const;

private:

    /**
   * This method should do the following:
   *
   * <p> - Pass the XML Parser the location for the plugin's METADATA.XML file
   * <p> - Handle the callbacks from the parser and build the appropriate
   * MetaType objects - ObjectClassDefinitions & AttributeDefinitions
   *
   * @param plugin The plugin object for which the metadata should be read
   * @return void
   */
    bool readMetaFiles(const QSharedPointer<QTKPlugin>& plugin);

    /**
   * Internal Method - checkForDefault
   */
    QList<QLocale> checkForDefault(const QList<QLocale>& locales) const;

};

#endif // QTKMETATYPEPROVIDERIMPL_P_H
