#ifndef QTKEACACHEMAP_P_H
#define QTKEACACHEMAP_P_H

template<class K, class V, class Impl>
struct QTKEACacheMap
{
    virtual ~QTKEACacheMap() {}

    const V value(const K &key) const
    {
        return static_cast<const Impl*>(this)->value(key);
    }

    const V value(const K &key, const V &defaultValue) const
    {
        return static_cast<const Impl*>(this)->value(key, defaultValue);
    }

    void insert(const K &key, const V &value)
    {
        static_cast<Impl*>(this)->insert(key, value);
    }

    const V remove(const K &key)
    {
        return static_cast<Impl*>(this)->remove(key);
    }

    int size() const
    {
        return static_cast<const Impl*>(this)->size();
    }

    void clear()
    {
        static_cast<Impl*>(this)->clear();
    }
};


#endif // QTKEACACHEMAP_P_H
