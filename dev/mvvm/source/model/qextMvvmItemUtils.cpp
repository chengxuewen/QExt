// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemUtils.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionItemContainer.h>
#include <qextMvvmSessionItemTags.h>
#include <qextMvvmContainerUtils.h>
#include <iterator>

using namespace ModelView;

void Utils::iterate(QExtMvvmSessionItem* item, const std::function<void(QExtMvvmSessionItem*)>& fun)
{
    if (item)
        fun(item);
    else
        return;

    for (auto child : item->children())
        iterate(child, fun);
}

void Utils::iterate_if(const QExtMvvmSessionItem* item, const std::function<bool(const QExtMvvmSessionItem*)>& fun)
{
    bool proceed_with_children(true);

    if (item)
        proceed_with_children = fun(item);

    if (!item || !proceed_with_children)
        return;

    for (auto child : item->children())
        iterate_if(child, fun);
}

int Utils::CopyNumber(const QExtMvvmSessionItem* item)
{
    int result(-1);

    if (!item)
        return result;

    int count(0);
    auto QExtMvvmModelType = item->modelType();
    if (auto parent = item->parent()) {
        for (auto child : parent->children()) {
            if (child == item)
                result = count;
            if (child->modelType() == QExtMvvmModelType)
                ++count;
        }
    }

    return count > 1 ? result : -1;
}

QExtMvvmSessionItem* Utils::ChildAt(const QExtMvvmSessionItem* parent, int index)
{
    if (!parent)
        return nullptr;

    auto container = parent->children();
    return index >= 0 && static_cast<size_t>(index) < container.size()
               ? container[static_cast<size_t>(index)]
               : nullptr;
}

int Utils::IndexOfChild(const QExtMvvmSessionItem* parent, const QExtMvvmSessionItem* child)
{
    return Utils::IndexOfItem(parent->children(), child);
}

bool Utils::HasTag(const QExtMvvmSessionItem& item, const std::string& tag)
{
    return item.itemTags()->isTag(tag);
}

bool Utils::IsSinglePropertyTag(const QExtMvvmSessionItem& item, const std::string& tag)
{
    return item.itemTags()->isSinglePropertyTag(tag);
}

std::vector<std::string> Utils::RegisteredTags(const QExtMvvmSessionItem& item)
{
    std::vector<std::string> result;
    for (const auto container : *item.itemTags())
        result.push_back(container->name());
    return result;
}

std::vector<std::string> Utils::RegisteredUniversalTags(const QExtMvvmSessionItem& item)
{
    std::vector<std::string> result;
    for (const auto& tag : RegisteredTags(item))
        if (!IsSinglePropertyTag(item, tag))
            result.push_back(tag);
    return result;
}

std::vector<QExtMvvmSessionItem*> Utils::TopLevelItems(const QExtMvvmSessionItem& item)
{
    std::vector<QExtMvvmSessionItem*> result;
    for (auto child : item.children())
        if (child->isVisible() && !IsSinglePropertyTag(item, item.tagRowOfItem(child).tag))
            result.push_back(child);
    return result;
}

std::vector<QExtMvvmSessionItem*> Utils::SinglePropertyItems(const QExtMvvmSessionItem& item)
{
    std::vector<QExtMvvmSessionItem*> result;
    for (auto child : item.children())
        if (child->isVisible() && IsSinglePropertyTag(item, item.tagRowOfItem(child).tag))
            result.push_back(child);
    return result;
}

QExtMvvmSessionItem* Utils::FindNextSibling(QExtMvvmSessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = item->tagRow();
    return parent->getItem(tagrow.tag, tagrow.row + 1);
}

QExtMvvmSessionItem* Utils::FindPreviousSibling(QExtMvvmSessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = parent->tagRowOfItem(item);
    return parent->getItem(tagrow.tag, tagrow.row - 1);
}

QExtMvvmSessionItem* Utils::FindNextItemToSelect(QExtMvvmSessionItem* item)
{
    auto next = FindNextSibling(item);
    auto closest = next ? next : FindPreviousSibling(item);
    return closest ? closest : item->parent();
}

bool Utils::IsItemAncestor(const QExtMvvmSessionItem* item, const QExtMvvmSessionItem* candidate)
{
    if (!item || !candidate)
        return false;
    const QExtMvvmSessionItem* parent = item->parent();
    while (parent) {
        if (parent == candidate)
            return true;
        else
            parent = parent->parent();
    }
    return false;
}

std::vector<QExtMvvmSessionItem*> Utils::UniqueItems(const std::vector<QExtMvvmSessionItem*>& items)
{
    auto filtered = Utils::UniqueWithOrder(items);
    std::vector<QExtMvvmSessionItem*> result;
    std::copy_if(filtered.begin(), filtered.end(), std::back_inserter(result),
                 [](QExtMvvmSessionItem *x) { return x != nullptr; });
    return result;
}
