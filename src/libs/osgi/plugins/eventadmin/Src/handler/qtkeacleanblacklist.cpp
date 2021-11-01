#include "qtkeacleanblacklist_p.h"

void QTKEACleanBlackList::add(const QTKServiceReference &serviceRef)
{
    QMutexLocker lock(&m_mutex);
    m_blackList.insert(serviceRef);
}

bool QTKEACleanBlackList::contains(const QTKServiceReference &serviceRef) const
{
    QMutexLocker lock(&m_mutex);

    // This removes stale (i.e., unregistered) references on any call to implContains
    foreach (QTKServiceReference ref, m_blackList) {
        if (!ref) {
            m_blackList.remove(ref);
        }
    }

    return m_blackList.contains(serviceRef);
}
