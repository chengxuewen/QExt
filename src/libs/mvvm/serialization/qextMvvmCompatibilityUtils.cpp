// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGroupItem.h>
#include <qextMvvmItemContainer.h>
#include <qextMvvmItemData.h>
#include <qextMvvmCompatibilityUtils.h>
#include <set>

namespace  Compatibility
{

/*
Returns `true` if given QEXTMvvmTagInfo is compatible with given container.
Here, `container` is what exists at runtime, `taginfo` has been obtained from the serialization.
Container is considered to be compatible (i.e. can be updated from serialized content), if it has
exactly same tag, and it is empty.
*/

bool IsCompatibleUniversalTag(const QEXTMvvmItemContainer& container, const QEXTMvvmTagInfo& taginfo)
{
    auto container_taginfo = container.tagInfo();

    bool is_empty = container.isEmpty();
    bool both_are_universal =
        !container_taginfo.isSinglePropertyTag() && !taginfo.isSinglePropertyTag();
    bool same_tags = container_taginfo == taginfo;

    return both_are_universal && same_tags && is_empty;
}

/*
Returns `true` if given QEXTMvvmTagInfo is a single property tag which is compatible with given container.
Here, `container` is what exists at runtime, `taginfo` has been obtained from the serialization.
Container is considered to be compatible (i.e. can be updated from serialized content), if it has
exactly same tag, and property item ready for update.
*/

bool IsCompatibleSinglePropertyTag(const QEXTMvvmItemContainer& container, const QEXTMvvmTagInfo& taginfo)
{
    auto container_taginfo = container.tagInfo();

    bool has_item = !container.isEmpty();
    bool both_are_properties =
        container_taginfo.isSinglePropertyTag() && taginfo.isSinglePropertyTag();
    bool same_tags = container_taginfo == taginfo;

    return both_are_properties && same_tags && has_item;
}

/*
Returns `true` if given QEXTMvvmTagInfo is compatible with given container.
Here, `container` is what exists at runtime, `taginfo` has been obtained from the serialization.
Container is considered to be compatible (i.e. can be updated from serialized content),
if it has exactly same tag, and it's name corresponds to QEXTMvvmGroupItem.
*/

bool IsCompatibleGroupTag(const QEXTMvvmItemContainer& container, const QEXTMvvmTagInfo& taginfo)
{
    auto container_taginfo = container.tagInfo();
    bool has_item = !container.isEmpty();
    bool same_tags = container_taginfo == taginfo;
    bool both_are_universal = !container_taginfo.isSinglePropertyTag() && !taginfo.isSinglePropertyTag();
    bool valid_tag_name = taginfo.name() == QEXTMvvmGroupItem::T_GROUP_ITEMS;
    return both_are_universal && same_tags && has_item && valid_tag_name;
}

} // namespace Compatibility
