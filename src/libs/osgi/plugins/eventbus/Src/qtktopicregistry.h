#ifndef QTKTOPICREGISTRY_H
#define QTKTOPICREGISTRY_H

// Includes list
#include "qtkeventdefinitions.h"

namespace qtkeventbus {

class QTK_EVENTBUS_EXPORT QTKTopicRegistry
{
public:
    static QTKTopicRegistry *instance();

    void shutdown();

    bool registerTopic(const QString strTopic, const QObject *pOwner);

    bool unregisterTopic(const QString strTopic);

    const QObject *owner(const QString strTopic) const;

    bool isTopicRegistered(const QString strTopic) const;

    void dump();

private:
    QTKTopicRegistry();

    QHash<QString, const QObject*> m_mapTopic; ///< Hash containing pairs (topic,owner).
};

} //nameSpace QTKEventBus

#endif // MAFTOPICREGISTRY_H
