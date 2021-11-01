#ifndef QTKEATOPICHANDLERFILTERS_P_H
#define QTKEATOPICHANDLERFILTERS_P_H

#include <QString>

template<class Impl>
struct QTKEATopicHandlerFilters
{
    virtual ~QTKEATopicHandlerFilters() {}

    QString createFilterForTopic(const QString &strTopic) {
        return static_cast<Impl*>(this)->createFilterForTopic(strTopic);
    }
};

#endif // QTKEATOPICHANDLERFILTERS_P_H
