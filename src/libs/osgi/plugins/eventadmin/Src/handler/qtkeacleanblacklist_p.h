#ifndef QTKEACLEANBLACKLIST_P_H
#define QTKEACLEANBLACKLIST_P_H

#include "qtkeablacklist_p.h"

#include <QTKPluginFramework/QTKServiceReference>

#include <QMutex>
#include <QSet>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEACleanBlackList : public QTKEABlackList<QTKEACleanBlackList>
{
public:
    void add(const QTKServiceReference &serviceRef);
    bool contains(const QTKServiceReference &serviceRef) const;

private:
    mutable QMutex m_mutex;
    mutable QSet<QTKServiceReference> m_blackList;
};

#endif // QTKEACLEANBLACKLIST_P_H
