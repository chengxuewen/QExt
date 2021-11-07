#include <qextMvvmGroupItem.h>
#include <qextMvvmUtils.h>
#include <qextMvvmStandardChildrenStrategies.h>


QVector<QEXTMvvmItem *> QEXTMvvmAllChildrenStrategy::children(const QEXTMvvmItem *item) const
{
    return item ? item->children() : QVector<QEXTMvvmItem*>();
}

QVector<QEXTMvvmItem*> QEXTMvvmTopItemsStrategy::children(const QEXTMvvmItem *item) const
{
    return item ? QEXTMvvmUtils::topLevelItems(*item) : QVector<QEXTMvvmItem*>();
}

/*
QEXTMvvmPropertyItemsStrategy example: if group property has Cylinder active:

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

QVector<QEXTMvvmItem *> QEXTMvvmPropertyItemsStrategy::children(const QEXTMvvmItem *item) const
{
    if (!item)
        return QVector<QEXTMvvmItem*>();

    auto group = dynamic_cast<const QEXTMvvmGroupItem*>(item);
    auto next_item = group ? group->currentItem() : item;
    return QEXTMvvmUtils::singlePropertyItems(*next_item);
}

// ----------------------------------------------------------------------------

/*
QEXTMvvmPropertyItemsFlatStrategy example: if group property has Cylinder active:

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

QVector<QEXTMvvmItem*> QEXTMvvmPropertyItemsFlatStrategy::children(const QEXTMvvmItem* item) const
{
    if (!item)
        return QVector<QEXTMvvmItem*>();

    if (auto group = dynamic_cast<const QEXTMvvmGroupItem*>(item); group)
        return QEXTMvvmUtils::singlePropertyItems(*group->currentItem());

    QVector<QEXTMvvmItem*> result;
    for (auto child : QEXTMvvmUtils::singlePropertyItems(*item)) {
        if (auto group_item = dynamic_cast<QEXTMvvmGroupItem*>(child); group_item) {
            result.push_back(group_item);
            for (auto sub_property : QEXTMvvmUtils::singlePropertyItems(*group_item->currentItem()))
                result.push_back(sub_property);
        } else {
            result.push_back(child);
        }
    }

    return result;
}
