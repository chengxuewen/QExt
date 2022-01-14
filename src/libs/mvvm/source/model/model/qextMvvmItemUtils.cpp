// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <iterator>
#include <qextMvvmItemUtils.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmContainerUtils.h>

using namespace ModelView;

void QEXTMvvmUtils::iterate(QEXTMvvmSessionItem* item, const std::function<void(QEXTMvvmSessionItem*)>& fun)
{
    if (item)
        fun(item);
    else
        return;

    for (auto child : item->children())
        iterate(child, fun);
}

void QEXTMvvmUtils::iterate_if(const QEXTMvvmSessionItem* item, const std::function<bool(const QEXTMvvmSessionItem*)>& fun)
{
    bool proceed_with_children(true);

    if (item)
        proceed_with_children = fun(item);

    if (!item || !proceed_with_children)
        return;

    for (auto child : item->children())
        iterate_if(child, fun);
}

int QEXTMvvmUtils::CopyNumber(const QEXTMvvmSessionItem* item)
{
    int result(-1);

    if (!item)
        return result;

    int count(0);
    auto model_type = item->modelType();
    if (auto parent = item->parent()) {
        for (auto child : parent->children()) {
            if (child == item)
                result = count;
            if (child->modelType() == model_type)
                ++count;
        }
    }

    return count > 1 ? result : -1;
}

QEXTMvvmSessionItem* QEXTMvvmUtils::ChildAt(const QEXTMvvmSessionItem* parent, int index)
{
    if (!parent)
        return nullptr;

    auto container = parent->children();
    return index >= 0 && static_cast<size_t>(index) < container.size()
               ? container[static_cast<size_t>(index)]
               : nullptr;
}

int QEXTMvvmUtils::IndexOfChild(const QEXTMvvmSessionItem* parent, const QEXTMvvmSessionItem* child)
{
    return QEXTMvvmUtils::IndexOfItem(parent->children(), child);
}

std::vector<QEXTMvvmSessionItem*> QEXTMvvmUtils::TopLevelItems(const QEXTMvvmSessionItem& item)
{
    std::vector<QEXTMvvmSessionItem*> result;
    for (auto child : item.children())
        if (!item.isSinglePropertyTag(item.tagOfItem(child)))
            result.push_back(child);
    return result;
}

std::vector<QEXTMvvmSessionItem*> QEXTMvvmUtils::SinglePropertyItems(const QEXTMvvmSessionItem& item)
{
    std::vector<QEXTMvvmSessionItem*> result;
    for (auto child : item.children())
        if (item.isSinglePropertyTag(item.tagOfItem(child)))
            result.push_back(child);
    return result;
}

QEXTMvvmSessionItem* QEXTMvvmUtils::FindNextSibling(QEXTMvvmSessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = item->tagRow();
    return parent->getItem(tagrow.tag, tagrow.row + 1);
}

QEXTMvvmSessionItem* QEXTMvvmUtils::FindPreviousSibling(QEXTMvvmSessionItem* item)
{
    auto parent = item ? item->parent() : nullptr;
    if (!parent)
        return nullptr;
    auto tagrow = parent->tagRowOfItem(item);
    return parent->getItem(tagrow.tag, tagrow.row - 1);
}

QEXTMvvmSessionItem* QEXTMvvmUtils::FindNextItemToSelect(QEXTMvvmSessionItem* item)
{
    auto next = FindNextSibling(item);
    auto closest = next ? next : FindPreviousSibling(item);
    return closest ? closest : item->parent();
}

bool QEXTMvvmUtils::IsItemAncestor(const QEXTMvvmSessionItem* item, const QEXTMvvmSessionItem* candidate)
{
    if (!item || !candidate)
        return false;
    const QEXTMvvmSessionItem* parent = item->parent();
    while (parent) {
        if (parent == candidate)
            return true;
        else
            parent = parent->parent();
    }
    return false;
}

std::vector<QEXTMvvmSessionItem*> QEXTMvvmUtils::UniqueItems(const std::vector<QEXTMvvmSessionItem*>& items)
{
    auto filtered = QEXTMvvmUtils::UniqueWithOrder(items);
    std::vector<QEXTMvvmSessionItem*> result;
    std::copy_if(filtered.begin(), filtered.end(), std::back_inserter(result),
                 [](QEXTMvvmSessionItem *x) { return x != nullptr; });
    return result;
}
