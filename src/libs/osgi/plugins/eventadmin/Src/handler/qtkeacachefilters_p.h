#ifndef QTKEACACHEFILTERS_P_H
#define QTKEACACHEFILTERS_P_H

#include "qtkeafilters_p.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

template<class CacheMap>
class QTKEACacheFilters : public QTKEAFilters<QTKEACacheFilters<CacheMap> >
{
public:
    QTKEACacheFilters(CacheMap *pCache, QTKPluginContext *pContext);
    ~QTKEACacheFilters();

    QTKLDAPSearchFilter createFilter(const QString &strFilter);

private:
    // The cache to use
    CacheMap *const m_pCache;
    // The context of the plugin used to create the Filter objects
    QTKPluginContext *const m_pContext;
};

template<class CacheMap>
QTKEACacheFilters<CacheMap>::QTKEACacheFilters(CacheMap *pCache, QTKPluginContext *pContext)
    : m_pCache(pCache),
      m_pContext(pContext)
{
    if(nullptr == pCache) {
        throw QTKInvalidArgumentException("Cache may not be null");
    }
    if(nullptr == pContext) {
        throw QTKInvalidArgumentException("Context may not be null");
    }
}

template<class CacheMap>
QTKEACacheFilters<CacheMap>::~QTKEACacheFilters()
{
    delete m_pCache;
}

template<class CacheMap>
QTKLDAPSearchFilter QTKEACacheFilters<CacheMap>::createFilter(const QString &strFilter)
{
    QTKLDAPSearchFilter result = strFilter.isEmpty() ? this->sm_trueFilter : m_pCache->value(strFilter);
    if (!result) {
        result = QTKLDAPSearchFilter(strFilter);
        m_pCache->insert(strFilter, result);
    }
    return result;
}

#endif // QTKEACACHEFILTERS_P_H
