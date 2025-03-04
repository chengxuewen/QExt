// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/sessionitemcontainer.h"
#include "model/model/sessionitem.h"
#include "model/utils/containerutils.h"

using namespace ModelView;

QExtMvvmSessionItemContainer::QExtMvvmSessionItemContainer(ModelView::QExtMvvmTagInfo tag_info)
    : m_tag_info(std::move(tag_info))
{
}

QExtMvvmSessionItemContainer::~QExtMvvmSessionItemContainer()
{
    for (auto item : m_items)
        delete item;
}

bool QExtMvvmSessionItemContainer::empty() const
{
    return m_items.empty();
}

//! Returns number of items in given tag.

int QExtMvvmSessionItemContainer::itemCount() const
{
    return static_cast<int>(m_items.size());
}

//! Returns vector of items in this container.

std::vector<QExtMvvmSessionItem*> QExtMvvmSessionItemContainer::items() const
{
    return m_items;
}

/*!
@brief Inserts item in a vector of children at given index, returns true in the case of success.
@param item Item to be inserted, ownership will be taken.
@param index Item insert index in a range [0, itemCount]

Insert index is an index which item will have after insertion. If item can't be inserted
(wrong model type, wrong index or maximum number of items reached), will return false.
*/

bool QExtMvvmSessionItemContainer::insertItem(QExtMvvmSessionItem* item, int index)
{
    if (!canInsertItem(item, index))
        return false;

    m_items.insert(std::next(m_items.begin(), index), item);
    return true;
}

//! Removes item at given index and returns it to the user.

QExtMvvmSessionItem* QExtMvvmSessionItemContainer::takeItem(int index)
{
    if (minimum_reached())
        return nullptr;

    QExtMvvmSessionItem* result = itemAt(index);
    if (result)
        m_items.erase(std::next(m_items.begin(), index));

    return result;
}

//! Returns true if item can be taken.

bool QExtMvvmSessionItemContainer::canTakeItem(int index) const
{
    return itemAt(index) && !minimum_reached();
}

//! Returns true if given item can be inserted under given index.

bool QExtMvvmSessionItemContainer::canInsertItem(const QExtMvvmSessionItem* item, int index) const
{
    const bool valid_index = (index >= 0 && index <= itemCount());
    const bool enough_place = !maximum_reached();
    return valid_index && enough_place && is_valid_item(item);
}

//! Returns index of item in vector of items.
//! Returns -1 if item doesn't belong to us.

int QExtMvvmSessionItemContainer::indexOfItem(const QExtMvvmSessionItem* item) const
{
    return Utils::IndexOfItem(m_items, item);
}

//! Returns item at given index. Returns nullptr if index is invalid.

QExtMvvmSessionItem* QExtMvvmSessionItemContainer::itemAt(int index) const
{
    return index >= 0 && index < itemCount() ? m_items[static_cast<size_t>(index)] : nullptr;
}

//! Returns the name of SessionItemTag.

std::string QExtMvvmSessionItemContainer::name() const
{
    return m_tag_info.name();
}

QExtMvvmTagInfo QExtMvvmSessionItemContainer::tagInfo() const
{
    return m_tag_info;
}

QExtMvvmSessionItemContainer::const_iterator QExtMvvmSessionItemContainer::begin() const
{
    return m_items.begin();
}

QExtMvvmSessionItemContainer::const_iterator QExtMvvmSessionItemContainer::end() const
{
    return m_items.end();
}

//! Returns true if no more items are allowed.

bool QExtMvvmSessionItemContainer::maximum_reached() const
{
    return m_tag_info.max() != -1 && m_tag_info.max() == itemCount();
}

//! Returns true if less items than now is not allowed.

bool QExtMvvmSessionItemContainer::minimum_reached() const
{
    return m_tag_info.min() != -1 && m_tag_info.min() == itemCount();
}

//! Returns true if item's modelType is intended for this tag.

bool QExtMvvmSessionItemContainer::is_valid_item(const QExtMvvmSessionItem* item) const
{
    return item && m_tag_info.isValidChild(item->modelType());
}
