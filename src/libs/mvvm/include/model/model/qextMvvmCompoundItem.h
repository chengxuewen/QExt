// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_COMPOUNDITEM_H
#define MVVM_MODEL_COMPOUNDITEM_H

#include <qextMvvmCustomVariants.h>
#include <qextMvvmPropertyItem.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmRealLimits.h>

namespace ModelView
{

//! Complex item holding mixed QEXTMvvmSessionItem types (single properties and other CompountItems).

class QEXT_MVVM_API QEXTMvvmCompoundItem : public QEXTMvvmSessionItem
{
public:
    QEXTMvvmCompoundItem(const std::string& modelType = Constants::CompoundItemType);

    //! Adds property item of given type.
    template <typename T = PropertyItem> T* addProperty(const std::string& name);

    template <typename V> PropertyItem* addProperty(const std::string& name, const V& value);

    //! Register char property. Special case to turn it into std::string.
    PropertyItem* addProperty(const std::string& name, const char* value);

    std::string displayName() const override;
};

template <typename T> T* QEXTMvvmCompoundItem::addProperty(const std::string& name)
{
    T* property = new T;
    registerTag(TagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    insertItem(property, {name, 0});
    return property;
}

inline PropertyItem* QEXTMvvmCompoundItem::addProperty(const std::string& name, const char* value)
{
    return addProperty(name, std::string(value));
}

template <typename V>
PropertyItem* QEXTMvvmCompoundItem::addProperty(const std::string& name, const V& value)
{
    auto property = new PropertyItem;
    registerTag(TagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    property->setData(value);

    // FIXME consider limitless values by default.

    if constexpr (std::is_floating_point_v<V>)
    {
        property->setData(RealLimits::nonnegative(), ItemDataRole::LIMITS);
    }

    insertItem(property, {name, 0});
    return property;
}

} // namespace ModelView

#endif // MVVM_MODEL_COMPOUNDITEM_H
