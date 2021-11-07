#ifndef _QEXTMVVMFACTORYINTERFACE_H
#define _QEXTMVVMFACTORYINTERFACE_H

#include <qextFunction.h>

#include <QMap>

#include <sstream>
#include <stdexcept>

//! Base for factories.

template <typename Key, typename Value>
class QEXTMvvmFactoryInterface
{
public:
    typedef QEXTFunction<Value *>           Function;
    typedef QMap<Key, Function>             Map;
    typedef typename Map::ConstIterator     ConstIterator;
    typedef typename Map::Iterator          Iterator;

    bool contains(const Key &key) const
    {
        return m_data.contains(key);
    }

    Value *create(const Key &key) const
    {
        if (!m_data.contains(key))
        {
            std::ostringstream message;
            message << "QEXTMvvmFactoryInterface::createItem() -> Error. Unknown item key ";
            throw std::runtime_error(message.str());
        }
        return m_data.value(key)();
    }

    void add(const Key &key, Function func)
    {
        if (m_data.contains(key))
        {
            std::ostringstream message;
            message << "QEXTMvvmFactoryInterface::createItem() -> Already registered item key ";
            throw std::runtime_error(message.str());
        }
        m_data.insert(key, func);
    }

    int size() const
    {
        return m_data.size();
    }

    typename Map::Iterator begin() { return m_data.begin(); }
    typename Map::Iterator end() { return m_data.end(); }

private:
    Map m_data;
};

#endif // _QEXTMVVMFACTORYINTERFACE_H
