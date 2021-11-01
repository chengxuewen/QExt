#include <qextMvvmUniqueIdGenerator.h>
#include <qextMvvmItemPool.h>
#include <stdexcept>

using namespace ModelView;

size_t QEXTMvvmItemPool::size() const
{
    if (m_key_to_item.size() != m_item_to_key.size())
        throw std::runtime_error("Error in QEXTMvvmItemPool: array size mismatch");
    return m_key_to_item.size();
}

QEXTMvvmIdentifierType QEXTMvvmItemPool::register_item(QEXTMvvmSessionItem* item, QEXTMvvmIdentifierType key)

{
    if (m_item_to_key.find(item) != m_item_to_key.end())
        throw std::runtime_error("QEXTMvvmItemPool::register_item() -> Attempt to register already "
                                 "registered item.");

    if (key.empty()) {
        key = QEXTMvvmUniqueIdGenerator::generate();
        while (m_key_to_item.find(key) != m_key_to_item.end())
            key = QEXTMvvmUniqueIdGenerator::generate(); // preventing improbable duplicates
    } else {
        if (m_key_to_item.find(key) != m_key_to_item.end())
            throw std::runtime_error(" QEXTMvvmItemPool::register_item() -> Attempt to reuse existing key");
    }

    m_key_to_item.insert(std::make_pair(key, item));
    m_item_to_key.insert(std::make_pair(item, key));

    return key;
}

void QEXTMvvmItemPool::unregister_item(QEXTMvvmSessionItem* item)
{
    auto it = m_item_to_key.find(item);
    if (it == m_item_to_key.end())
        throw std::runtime_error("QEXTMvvmItemPool::deregister_item() -> Attempt to deregister "
                                 "non existing item.");
    auto key = it->second;
    m_item_to_key.erase(it);

    auto it2 = m_key_to_item.find(key);
    m_key_to_item.erase(it2);
}

QEXTMvvmIdentifierType QEXTMvvmItemPool::key_for_item(QEXTMvvmSessionItem* item) const
{
    auto it = m_item_to_key.find(item);
    if (it != m_item_to_key.end())
        return it->second;

    return {};
}

QEXTMvvmSessionItem* QEXTMvvmItemPool::item_for_key(const QEXTMvvmIdentifierType& key) const
{
    auto it = m_key_to_item.find(key);
    if (it != m_key_to_item.end())
        return it->second;

    return nullptr;
}
