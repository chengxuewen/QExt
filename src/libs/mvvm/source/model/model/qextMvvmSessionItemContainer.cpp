// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionItemContainer.h>
#include <qextMvvmContainerUtils.h>

using namespace ModelView;

QEXTMvvmSessionItemContainer::QEXTMvvmSessionItemContainer(ModelView::QEXTMvvmTagInfo tag_info)
    : m_tag_info(std::move(tag_info))
{
}

QEXTMvvmSessionItemContainer::~QEXTMvvmSessionItemContainer()
{
    for (auto item : m_items)
        delete item;
}

bool QEXTMvvmSessionItemContainer::empty() const
{
    return m_items.empty();
}

//! Returns number of items in given tag.

int QEXTMvvmSessionItemContainer::itemCount() const
{
    return static_cast<int>(m_items.size());
}

//! Returns vector of items in this container.

std::vector<QEXTMvvmSessionItem*> QEXTMvvmSessionItemContainer::items() const
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

bool QEXTMvvmSessionItemContainer::insertItem(QEXTMvvmSessionItem* item, int index)
{
    if (!canInsertItem(item, index))
        return false;

    m_items.insert(std::next(m_items.begin(), index), item);
    return true;
}

//! Removes item at given index and returns it to the user.

QEXTMvvmSessionItem* QEXTMvvmSessionItemContainer::takeItem(int index)
{
    if (minimum_reached())
        return nullptr;

    QEXTMvvmSessionItem* result = itemAt(index);
    if (result)
        m_items.erase(std::next(m_items.begin(), index));

    return result;
}

//! Returns true if item can be taken.

bool QEXTMvvmSessionItemContainer::canTakeItem(int index) const
{
    return itemAt(index) && !minimum_reached();
}

//! Returns true if given item can be inserted under given index.

bool QEXTMvvmSessionItemContainer::canInsertItem(const QEXTMvvmSessionItem* item, int index) const
{
    const bool valid_index = (index >= 0 && index <= itemCount());
    const bool enough_place = !maximum_reached();
    return valid_index && enough_place && is_valid_item(item);
}

//! Returns index of item in vector of items.
//! Returns -1 if item doesn't belong to us.

int QEXTMvvmSessionItemContainer::indexOfItem(const QEXTMvvmSessionItem* item) const
{
    return QEXTMvvmUtils::IndexOfItem(m_items, item);
}

//! Returns item at given index. Returns nullptr if index is invalid.

QEXTMvvmSessionItem* QEXTMvvmSessionItemContainer::itemAt(int index) const
{
    return index >= 0 && index < itemCount() ? m_items[static_cast<size_t>(index)] : nullptr;
}

//! Returns the name of SessionItemTag.

std::string QEXTMvvmSessionItemContainer::name() const
{
    return m_tag_info.name();
}

QEXTMvvmTagInfo QEXTMvvmSessionItemContainer::tagInfo() const
{
    return m_tag_info;
}

QEXTMvvmSessionItemContainer::const_iterator QEXTMvvmSessionItemContainer::begin() const
{
    return m_items.begin();
}

QEXTMvvmSessionItemContainer::const_iterator QEXTMvvmSessionItemContainer::end() const
{
    return m_items.end();
}

//! Returns true if no more items are allowed.

bool QEXTMvvmSessionItemContainer::maximum_reached() const
{
    return m_tag_info.max() != -1 && m_tag_info.max() == itemCount();
}

//! Returns true if less items than now is not allowed.

bool QEXTMvvmSessionItemContainer::minimum_reached() const
{
    return m_tag_info.min() != -1 && m_tag_info.min() == itemCount();
}

//! Returns true if item's modelType is intended for this tag.

bool QEXTMvvmSessionItemContainer::is_valid_item(const QEXTMvvmSessionItem* item) const
{
    return item && m_tag_info.isValidChild(item->modelType());
}
