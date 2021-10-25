#include <qextMvvmStandardChildrenStrategies.h>
#include <qextMvvmUtils.h>

#include <cfMvvmItem.h>
#include <cfMvvmGroupItem.h>

std::list<CFMvvmItem *> QEXTMvvmAllChildrenStrategy::children(const CFMvvmItem *item) const
{
    return item ? item->children() : std::list<CFMvvmItem *>();
}

std::list<CFMvvmItem *> QEXTMvvmTopItemsStrategy::children(const CFMvvmItem *item) const
{
    return QEXTMvvmUtils::singlePropertyItems(item);
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

std::list<CFMvvmItem *> QEXTMvvmPropertyItemsStrategy::children(const CFMvvmItem *item) const
{
    std::list<CFMvvmItem *> result;
    if (item)
    {
        const CFMvvmGroupItem *group = dynamic_cast<const CFMvvmGroupItem *>(item);
        const CFMvvmItem *nextItem = group ? group->currentItem() : item;
        result = QEXTMvvmUtils::singlePropertyItems(nextItem);
    }
    return result;
}

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
std::list<CFMvvmItem *> QEXTMvvmPropertyItemsFlatStrategy::children(const CFMvvmItem *item) const
{
    std::list<CFMvvmItem *> result;
    if (item)
    {
        const CFMvvmGroupItem *group = dynamic_cast<const CFMvvmGroupItem *>(item);
        if (group)
        {
            result = QEXTMvvmUtils::singlePropertyItems(group->currentItem());
        }
        else
        {
            std::list<CFMvvmItem *> items = QEXTMvvmUtils::singlePropertyItems(item);
            std::list<CFMvvmItem *>::const_iterator iter;
            for (iter = items.begin(); iter != items.end(); ++iter)
            {
                CFMvvmItem *child = *iter;
                const CFMvvmGroupItem *groupItem = dynamic_cast<const CFMvvmGroupItem *>(child);
                if (groupItem)
                {
                    result.push_back(const_cast<CFMvvmGroupItem *>(groupItem));
                    std::list<CFMvvmItem *> subPropertys = QEXTMvvmUtils::singlePropertyItems(groupItem->currentItem());
                    std::list<CFMvvmItem *>::const_iterator subPropertyIter;
                    for (subPropertyIter = subPropertys.begin(); subPropertyIter != subPropertys.end(); ++subPropertyIter)
                    {
                        CFMvvmItem *subProperty = *iter;
                        result.push_back(subProperty);
                    }
                }
                else
                {
                    result.push_back(child);
                }
            }
        }
    }
    return result;
}
