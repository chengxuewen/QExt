// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGroupItem.h>
#include <qextMvvmItemUtils.h>
#include <viewmodel/qextMvvmStandardChildrenStrategies.h>

using namespace ModelView;

// ----------------------------------------------------------------------------

std::vector<QEXTMvvmSessionItem*> QEXTMvvmAllChildrenStrategy::children(const QEXTMvvmSessionItem* item) const
{
    return item ? item->children() : std::vector<QEXTMvvmSessionItem*>();
}

std::vector<QEXTMvvmSessionItem*> QEXTMvvmTopItemsStrategy::children(const QEXTMvvmSessionItem* item) const
{
    return item ? QEXTMvvmUtils::TopLevelItems(*item) : std::vector<QEXTMvvmSessionItem*>();
}

// ----------------------------------------------------------------------------

/*
PropertyItemsStrategy example: if group property has Cylinder active:

Particle
    ShapeGroup
        Sphere
            Radius
        Cylinder
            Height
            Radius

will become:
Particle
    ShapeGroup -> Cylinder
        Height
        Radius
*/

std::vector<QEXTMvvmSessionItem*> QEXTMvvmPropertyItemsStrategy::children(const QEXTMvvmSessionItem* item) const
{
    if (!item)
        return std::vector<QEXTMvvmSessionItem*>();

    auto group = dynamic_cast<const QEXTMvvmGroupItem*>(item);
    auto next_item = group ? group->currentItem() : item;
    return QEXTMvvmUtils::SinglePropertyItems(*next_item);
}

// ----------------------------------------------------------------------------

/*
PropertyItemsFlatStrategy example: if group property has Cylinder active:

Particle
    ShapeGroup
        Sphere
            Radius
        Cylinder
            Height
            Radius

will become:
Particle
    ShapeGroup -> Cylinder
    Height
    Radius
*/

std::vector<QEXTMvvmSessionItem*> QEXTMvvmPropertyItemsFlatStrategy::children(const QEXTMvvmSessionItem* item) const
{
    if (!item)
        return std::vector<QEXTMvvmSessionItem*>();

    if (auto group = dynamic_cast<const QEXTMvvmGroupItem*>(item); group)
        return QEXTMvvmUtils::SinglePropertyItems(*group->currentItem());

    std::vector<QEXTMvvmSessionItem*> result;
    for (auto child : QEXTMvvmUtils::SinglePropertyItems(*item)) {
        if (auto group_item = dynamic_cast<QEXTMvvmGroupItem*>(child); group_item) {
            result.push_back(group_item);
            for (auto sub_property : QEXTMvvmUtils::SinglePropertyItems(*group_item->currentItem()))
                result.push_back(sub_property);
        } else {
            result.push_back(child);
        }
    }

    return result;
}
