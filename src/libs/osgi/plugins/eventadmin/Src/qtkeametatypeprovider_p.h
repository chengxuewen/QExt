#ifndef QTKEAMETATYPEPROVIDER_P_H
#define QTKEAMETATYPEPROVIDER_P_H

#include <QTKPluginFramework/Service/Metatype/QTKMetaTypeProvider>
#include <QTKPluginFramework/Service/Config/QTKManagedService>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEAMetaTypeProvider : public QObject, public QTKMetaTypeProvider, public QTKManagedService
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKMetaTypeProvider)
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKManagedService)

public:
    QTKEAMetaTypeProvider(QTKManagedService *pDelegatee, int iCacheSize,
                          int iThreadPoolSize, int iTimeout, bool bRequireTopic,
                          const QStringList &listIgnoreTimeout);

    void updated(const QTKDictionary &properties);

    QList<QLocale> getLocales() const;

    QTKObjectClassDefinitionPtr getObjectClassDefinition(const QString &strId, const QLocale &locale);

private:
    class QTKObjectClassDefinitionImpl;
    class QTKAttributeDefinitionImpl;

    const int m_iCacheSize;
    const int m_ihreadPoolSize;
    const int m_iTimeout;
    const bool m_bRequireTopic;
    const QStringList m_listIgnoreTimeout;

    QTKManagedService *const m_pDelegatee;
    QTKObjectClassDefinitionPtr m_objectClassDefinitionPtr;
};

#endif // QTKEAMETATYPEPROVIDER_P_H
