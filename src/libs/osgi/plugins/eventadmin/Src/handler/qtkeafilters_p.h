#ifndef QTKEAFILTERS_P_H
#define QTKEAFILTERS_P_H

#include <QTKPluginFramework/QTKLDAPSearchFilter>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

template<class Impl>
struct QTKEAFilters
{
    virtual ~QTKEAFilters() {}

    QTKLDAPSearchFilter createFilter(const QString &strFilter) {
        return static_cast<Impl*>(this)->createFilter(strFilter);
    }

    static const QTKLDAPSearchFilter sm_trueFilter;
};

template<class Impl>
const QTKLDAPSearchFilter QTKEAFilters<Impl>::sm_trueFilter(QString("(") + QTKEventConstants::EVENT_TOPICS + "=*)");

#endif // QTKEAFILTERS_P_H
