// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/itempool.h"
#include "model/core/uniqueidgenerator.h"
#include <stdexcept>

using namespace ModelView;

size_t QExtMvvmItemPool::size() const
{
    if (m_key_to_item.size() != m_item_to_key.size())
        throw std::runtime_error("Error in QExtMvvmItemPool: array size mismatch");
    return m_key_to_item.size();
}

QExtMvvmIdentifierType QExtMvvmItemPool::register_item(QExtMvvmSessionItem* item, QExtMvvmIdentifierType key)

{
    if (m_item_to_key.find(item) != m_item_to_key.end())
        throw std::runtime_error("QExtMvvmItemPool::register_item() -> Attempt to register already "
                                 "registered item.");

    if (key.empty()) {
        key = QExtMvvmUniqueIdGenerator::generate();
        while (m_key_to_item.find(key) != m_key_to_item.end())
            key = QExtMvvmUniqueIdGenerator::generate(); // preventing improbable duplicates
    }
    else {
        if (m_key_to_item.find(key) != m_key_to_item.end())
            throw std::runtime_error(" QExtMvvmItemPool::register_item() -> Attempt to reuse existing key");
    }

    m_key_to_item.insert(std::make_pair(key, item));
    m_item_to_key.insert(std::make_pair(item, key));

    return key;
}

void QExtMvvmItemPool::unregister_item(QExtMvvmSessionItem* item)
{
    auto it = m_item_to_key.find(item);
    if (it == m_item_to_key.end())
        throw std::runtime_error("QExtMvvmItemPool::deregister_item() -> Attempt to deregister "
                                 "non existing item.");
    auto key = it->second;
    m_item_to_key.erase(it);

    auto it2 = m_key_to_item.find(key);
    m_key_to_item.erase(it2);
}

QExtMvvmIdentifierType QExtMvvmItemPool::key_for_item(const QExtMvvmSessionItem* item) const
{
    const auto it = m_item_to_key.find(item);
    if (it != m_item_to_key.end())
        return it->second;

    return {};
}

QExtMvvmSessionItem* QExtMvvmItemPool::item_for_key(const QExtMvvmIdentifierType& key) const
{
    auto it = m_key_to_item.find(key);
    if (it != m_key_to_item.end())
        return it->second;

    return nullptr;
}
