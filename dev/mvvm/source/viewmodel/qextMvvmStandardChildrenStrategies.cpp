// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmStandardChildrenStrategies.h>
#include <qextMvvmGroupItem.h>
#include <qextMvvmItemUtils.h>

using namespace ModelView;

// ----------------------------------------------------------------------------

std::vector<QExtMvvmSessionItem*> QExtMvvmAllChildrenStrategy::children(const QExtMvvmSessionItem* item) const
{
    // we returns all children, even if some marked as invisible
    return item ? item->children() : std::vector<QExtMvvmSessionItem*>();
}

std::vector<QExtMvvmSessionItem*> QExtMvvmTopItemsStrategy::children(const QExtMvvmSessionItem* item) const
{
    return item ? Utils::TopLevelItems(*item) : std::vector<QExtMvvmSessionItem*>();
}

// ----------------------------------------------------------------------------

/*
QExtMvvmPropertyItemsStrategy example: if group property has Cylinder active:

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

std::vector<QExtMvvmSessionItem*> QExtMvvmPropertyItemsStrategy::children(const QExtMvvmSessionItem* item) const
{
    if (!item)
        return std::vector<QExtMvvmSessionItem*>();

    auto group = dynamic_cast<const QExtMvvmGroupItem*>(item);
    auto next_item = group ? group->currentItem() : item;
    return Utils::SinglePropertyItems(*next_item);
}

// ----------------------------------------------------------------------------

/*
QExtMvvmPropertyItemsFlatStrategy example: if group property has Cylinder active:

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

std::vector<QExtMvvmSessionItem*> QExtMvvmPropertyItemsFlatStrategy::children(const QExtMvvmSessionItem* item) const
{
    if (!item) return std::vector<QExtMvvmSessionItem*>();

    auto group = dynamic_cast<const QExtMvvmGroupItem*>(item);
    if (group) return Utils::SinglePropertyItems(*group->currentItem());

    std::vector<QExtMvvmSessionItem*> result;
    for (auto child : Utils::SinglePropertyItems(*item))
    {
        auto group_item = dynamic_cast<QExtMvvmGroupItem*>(child);
        if (group_item)
        {
            result.push_back(group_item);
            for (auto sub_property : Utils::SinglePropertyItems(*group_item->currentItem()))
            {
                result.push_back(sub_property);
            }
        }
        else
        {
            result.push_back(child);
        }
    }

    return result;
}
