#ifndef QTKEACACHETOPICHANDLERFILTERS_P_H
#define QTKEACACHETOPICHANDLERFILTERS_P_H

#include "qtkeatopichandlerfilters_p.h"
#include "../util/qtkeacachemap_p.h"

#include <QTKCore/QTKException>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>

QTK_CORE_USE_NAMESPACE
QTK_PLUGINFRAMEWORK_USE_NAMESPACE

template<class CacheMap>
class QTKEACacheTopicHandlerFilters : public QTKEATopicHandlerFilters<QTKEACacheTopicHandlerFilters<CacheMap> >
{
    typedef QTKEACacheMap<typename CacheMap::KeyType, typename CacheMap::ValueType, CacheMap> CacheMapInterface;

public:
    QTKEACacheTopicHandlerFilters(CacheMapInterface *pCache, bool bRequireTopic);
    ~QTKEACacheTopicHandlerFilters();

    QString createFilterForTopic(const QString &strTopic);

private:
    CacheMapInterface *m_pCache;
    QString m_strFilterStart;
};

template<class CacheMap>
QTKEACacheTopicHandlerFilters<CacheMap>::QTKEACacheTopicHandlerFilters(CacheMapInterface *pCache, bool bRequireTopic)
    : m_pCache(pCache)
{
    if(nullptr == pCache) {
        throw QTKInvalidArgumentException("Cache may not be null");
    }

    m_strFilterStart = QString("(|") + (bRequireTopic ? QString("") : QString("(!(") + QTKEventConstants::EVENT_TOPICS + "=*))")
            + "(" + QTKEventConstants::EVENT_TOPICS + "=\\*)(" + QTKEventConstants::EVENT_TOPICS + "=";
}

template<class CacheMap>
QTKEACacheTopicHandlerFilters<CacheMap>::~QTKEACacheTopicHandlerFilters()
{
    delete m_pCache;
}

template<class CacheMap>
QString QTKEACacheTopicHandlerFilters<CacheMap>::createFilterForTopic(const QString &strTopic)
{
    QString strResult = m_pCache->value(strTopic);
    if(strResult.isEmpty()) {
        QString strFilter = m_strFilterStart;
        for (int i = 0; i < strTopic.size(); ++i) {
            if (QChar('/') == strTopic.at(i)) {
                strFilter.append('/').append('\\').append('*').append(')');
                strFilter.append('(').append(QTKEventConstants::EVENT_TOPICS).append('=').append(strTopic.left(i+1));
            } else {
                strFilter.append(strTopic.at(i));
            }
        }
        strFilter.append(')').append(')');
        strResult = strFilter;
        m_pCache->insert(strTopic, strResult);
    }
    return strResult;
}

#endif // QTKEACACHETOPICHANDLERFILTERS_P_H
