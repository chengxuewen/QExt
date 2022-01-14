#ifndef _QEXTMVVMMODELITEMPOOL_H
#define _QEXTMVVMMODELITEMPOOL_H

#include <map>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Provides registration of QEXTMvvmSessionItem pointers and their unique identifiers
//! in global memory pool.

class QEXT_MVVM_API QEXTMvvmItemPool
{
public:
    QEXTMvvmItemPool() = default;
    QEXTMvvmItemPool(const QEXTMvvmItemPool&) = delete;
    QEXTMvvmItemPool(QEXTMvvmItemPool&&) = delete;
    QEXTMvvmItemPool& operator=(const QEXTMvvmItemPool&) = delete;
    QEXTMvvmItemPool& operator=(QEXTMvvmItemPool&&) = delete;

    size_t size() const;

    identifier_type register_item(QEXTMvvmSessionItem* item, identifier_type key = {});
    void unregister_item(QEXTMvvmSessionItem* item);

    identifier_type key_for_item(QEXTMvvmSessionItem* item) const;

    QEXTMvvmSessionItem* item_for_key(const identifier_type& key) const;

private:
    std::map<identifier_type, QEXTMvvmSessionItem*> m_key_to_item;
    std::map<QEXTMvvmSessionItem*, identifier_type> m_item_to_key;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELITEMPOOL_H
