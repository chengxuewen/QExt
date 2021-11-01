#ifndef QTKEALEASTRECENTLYUSEDCACHEMAP_P_H
#define QTKEALEASTRECENTLYUSEDCACHEMAP_P_H

#include "qtkeacachemap_p.h"

#include <QTKCore/QTKException>

#include <QHash>
#include <QList>
#include <QMutex>

QTK_CORE_USE_NAMESPACE

template<typename K, typename V>
class QTKEALeastRecentlyUsedCacheMap : public QTKEACacheMap<K,V, QTKEALeastRecentlyUsedCacheMap<K,V> >
{
public:
    typedef K KeyType;
    typedef V ValueType;

    QTKEALeastRecentlyUsedCacheMap(int m_iMaxSize);

    const V value(const K& key) const;

    const V value(const K& key, const V& defaultValue) const;

    void insert(const K& key, const V& value);

    const V remove(const K& key);

    int size() const;

    void clear();

private:
    // The internal lock for this object
    mutable QMutex m_mutex;
    // The max number of entries in the cache. Once reached entries are replaced
    const int m_iMaxSize;
    // The cache
    QHash<K, V> m_mapCache;
    // The history used to determine the least recently used entries. The end of the
    // list is the most recently used key. In other words history.front() returns
    // the least recently used key.
    mutable QList<K> m_listHistory;
};

template<typename K, typename V>
QTKEALeastRecentlyUsedCacheMap<K,V>::QTKEALeastRecentlyUsedCacheMap(int iMaxSize)
    : m_iMaxSize(iMaxSize)
{
    if(0 >= iMaxSize) {
        throw QTKInvalidArgumentException("Size must be positive");
    }

    // We need one more entry then m_maxSize in the cache and a HashMap is
    // expanded when it reaches 3/4 of its size hence, the funny numbers.
    m_mapCache.reserve(((iMaxSize + 1) * 4)/3);
}

template<typename K, typename V>
const V
QTKEALeastRecentlyUsedCacheMap<K,V>::value(const K &key) const
{
    QMutexLocker lock(&m_mutex);
    if (m_mapCache.contains(key)) {
        m_listHistory.removeAll(key);
        m_listHistory.push_back(key);
        return m_mapCache.value(key);
    } else {
        return V();
    }
}

template<typename K, typename V>
const V QTKEALeastRecentlyUsedCacheMap<K,V>::value(const K &key, const V &defaultValue) const
{
    QMutexLocker lock(&m_mutex);
    if (m_mapCache.contains(key)) {
        m_listHistory.removeAll(key);
        m_listHistory.push_back(key);
        return m_mapCache.value(key);
    } else {
        return defaultValue;
    }
}

template<typename K, typename V>
void QTKEALeastRecentlyUsedCacheMap<K,V>::insert(const K &key, const V &value)
{
    QMutexLocker lock(&m_mutex);
    if (m_mapCache.contains(key)) {
        m_listHistory.removeAll(key);
    }

    m_mapCache.insert(key, value);
    m_listHistory.push_back(key);

    if(m_iMaxSize < m_mapCache.size()) {
        m_mapCache.remove(m_listHistory.takeFirst());
    }
}

template<typename K, typename V>
const V QTKEALeastRecentlyUsedCacheMap<K,V>::remove(const K &key)
{
    QMutexLocker lock(&m_mutex);
    if (m_mapCache.contains(key)) {
        m_listHistory.removeAll(key);
    }

    return m_mapCache.take(key);
}

template<typename K, typename V>
int QTKEALeastRecentlyUsedCacheMap<K,V>::size() const
{
    QMutexLocker lock(&m_mutex);
    return m_mapCache.size();
}

template<typename K, typename V>
void QTKEALeastRecentlyUsedCacheMap<K,V>::clear()
{
    QMutexLocker lock(&m_mutex);
    m_mapCache.clear();
    m_listHistory.clear();
}

#endif // QTKEALEASTRECENTLYUSEDCACHEMAP_P_H
