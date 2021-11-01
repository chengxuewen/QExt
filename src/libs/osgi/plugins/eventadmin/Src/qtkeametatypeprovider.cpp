#include "qtkeametatypeprovider_p.h"
#include "qtkeaconfiguration_p.h"

#include <limits>

class QTKEAMetaTypeProvider::QTKObjectClassDefinitionImpl : public QTKObjectClassDefinition
{
public:
    QTKObjectClassDefinitionImpl(const QList<QTKAttributeDefinitionPtr> &listAttrs)
        : m_listAttrs(listAttrs)
    {

    }

    QString getName() const
    {
        return "qtk Event Admin Implementation";
    }

    QByteArray getIcon(int iSize) const
    {
        Q_UNUSED(iSize)
        return QByteArray();
    }

    QString getID() const
    {
        return QTKEAConfiguration::PID;
    }

    QString getDescription() const
    {
        return "Configuration for the qtk Event Admin Implementation."
               " This configuration overwrites configuration defined in framework properties of the same names.";
    }

    QList<QTKAttributeDefinitionPtr> getAttributeDefinitions(Filter filter)
    {
        return (filter == OPTIONAL) ? QList<QTKAttributeDefinitionPtr>() : m_listAttrs;
    }

private:
    QList<QTKAttributeDefinitionPtr> m_listAttrs;
};

class QTKEAMetaTypeProvider::QTKAttributeDefinitionImpl : public QTKAttributeDefinition
{
public:
    QTKAttributeDefinitionImpl(const QString &strId, const QString &strName, const QString &strDescription, int iType,
                               const  QStringList &listDefaultValues, int iCardinality = 0,
                               const QStringList &listOptionLabels = QStringList(),
                               const QStringList &listOptionValues = QStringList())
        : m_strId(strId),
          m_strName(strName),
          m_strDescription(strDescription),
          m_iType(iType),
          m_listDefaultValues(listDefaultValues),
          m_iCardinality(iCardinality),
          m_listOptionLabels(listOptionLabels),
          m_listOptionValues(listOptionValues)
    {

    }

    int getCardinality() const
    {
        return m_iCardinality;
    }

    QStringList getDefaultValue() const
    {
        return m_listDefaultValues;
    }

    QString getDescription() const
    {
        return m_strDescription;
    }

    QString getID() const
    {
        return m_strId;
    }

    QString getName() const
    {
        return m_strName;
    }

    QStringList getOptionLabels() const
    {
        return m_listOptionLabels;
    }

    QStringList getOptionValues() const
    {
        return m_listOptionValues;
    }

    int getType() const
    {
        return m_iType;
    }

    QString validate(const QString &str) const
    {
        Q_UNUSED(str)
        return QString();
    }

private:
    const QString m_strId;
    const QString m_strName;
    const QString m_strDescription;
    const int m_iType;
    const QStringList m_listDefaultValues;
    const int m_iCardinality;
    const QStringList m_listOptionLabels;
    const QStringList m_listOptionValues;
};

QTKEAMetaTypeProvider::QTKEAMetaTypeProvider(QTKManagedService *pDelegatee, int iCacheSize,
                                             int iThreadPoolSize, int iTimeout, bool bRequireTopic,
                                             const QStringList &listIgnoreTimeout)
    : m_iCacheSize(iCacheSize),
      m_ihreadPoolSize(iThreadPoolSize),
      m_iTimeout(iTimeout),
      m_bRequireTopic(bRequireTopic),
      m_listIgnoreTimeout(listIgnoreTimeout),
      m_pDelegatee(pDelegatee)
{
}

void QTKEAMetaTypeProvider::updated(const QTKDictionary &properties)
{
    m_pDelegatee->updated(properties);
}

QList<QLocale> QTKEAMetaTypeProvider::getLocales() const
{
    return QList<QLocale>();
}

QTKObjectClassDefinitionPtr QTKEAMetaTypeProvider::getObjectClassDefinition(const QString &strId, const QLocale &locale)
{
    Q_UNUSED(locale)

    if (QTKEAConfiguration::PID != strId) {
        return QTKObjectClassDefinitionPtr();
    }

    if (!m_objectClassDefinitionPtr) {
        QList<QTKAttributeDefinitionPtr> listPtr;

        listPtr.push_back(QTKAttributeDefinitionPtr(
                              new QTKAttributeDefinitionImpl(QTKEAConfiguration::PROP_CACHE_SIZE, "Cache Size",
                                                             "The size of various internal caches. The default value is 30. Increase in case "
                                                             "of a large number (more then 100) of services. A value less then 10 triggers the "
                                                             "default value.", QVariant::Int, QStringList(QString::number(m_iCacheSize)))));

        listPtr.push_back(QTKAttributeDefinitionPtr(
                              new QTKAttributeDefinitionImpl(QTKEAConfiguration::PROP_THREAD_POOL_SIZE, "Thread Pool Size",
                                                             "The size of the thread pool. The default value is 10. Increase in case of a large amount "
                                                             "of synchronous events where the event handler services in turn send new synchronous events in "
                                                             "the event dispatching thread or a lot of timeouts are to be expected. A value of "
                                                             "less then 2 triggers the default value. A value of 2 effectively disables thread pooling.",
                                                             QVariant::Int, QStringList(QString::number(m_ihreadPoolSize)))));

        listPtr.push_back(QTKAttributeDefinitionPtr(
                              new QTKAttributeDefinitionImpl(QTKEAConfiguration::PROP_TIMEOUT, "Timeout",
                                                             "The black-listing timeout in milliseconds. The default value is 5000. Increase or decrease "
                                                             "at own discretion. A value of less then 100 turns timeouts off. Any other value is the time "
                                                             "in milliseconds granted to each event handler before it gets blacklisted",
                                                             QVariant::Int, QStringList(QString::number(m_iTimeout)))));

        listPtr.push_back(QTKAttributeDefinitionPtr(
                              new QTKAttributeDefinitionImpl(QTKEAConfiguration::PROP_REQUIRE_TOPIC, "Require Topic",
                                                             "Are event handlers required to be registered with a topic? "
                                                             "This is enabled by default. The specification says that event handlers "
                                                             "must register with a list of topics they are interested in. Disabling this setting "
                                                             "will enable that handlers without a topic are receiving all events "
                                                             "(i.e., they are treated the same as with a topic=*).",
                                                             QVariant::Bool, m_bRequireTopic ? QStringList("true") : QStringList("false"))));

        listPtr.push_back(QTKAttributeDefinitionPtr(
                              new QTKAttributeDefinitionImpl(QTKEAConfiguration::PROP_IGNORE_TIMEOUT, "Ignore Timeouts",
                                                             "Configure event handlers to be called without a timeout. If a timeout is configured by default "
                                                             "all event handlers are called using the timeout. For performance optimization it is possible to "
                                                             "configure event handlers where the timeout handling is not used - this reduces the thread usage "
                                                             "from the thread pools as the timout handling requires an additional thread to call the event "
                                                             "handler. However, the application should work without this configuration property. It is a "
                                                             "pure optimization! The value is a list of strings (separated by comma) which is assumed to define "
                                                             "exact class names.",
                                                             QVariant::String, m_listIgnoreTimeout, 0,
                                                             QStringList(QString::number(std::numeric_limits<int>::max())))));

        m_objectClassDefinitionPtr = QTKObjectClassDefinitionPtr(new QTKObjectClassDefinitionImpl(listPtr));
    }

    return m_objectClassDefinitionPtr;
}

