#include <qextMvvmItemContainer.h>
#include <qextMvvmItemContainer_p.h>
#include <qextMvvmItem.h>
#include <qextMvvmUtils.h>


QEXTMvvmItemContainerPrivate::QEXTMvvmItemContainerPrivate(QEXTMvvmItemContainer *q)
    : q_ptr(q)
{

}

QEXTMvvmItemContainerPrivate::~QEXTMvvmItemContainerPrivate()
{

}



QEXTMvvmItemContainer::QEXTMvvmItemContainer(const QEXTMvvmTagInfo &tagInfo)
    : d_ptr(new QEXTMvvmItemContainerPrivate(this))
{
    d_ptr->m_tagInfo = tagInfo;
}

QEXTMvvmItemContainer::~QEXTMvvmItemContainer()
{

}

bool QEXTMvvmItemContainer::isEmpty() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_itemVector.isEmpty();
}

//! Returns number of items in given tag.

int QEXTMvvmItemContainer::itemCount() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_itemVector.size();
}

//! Returns vector of items in this container.

QVector<QEXTMvvmItem *> QEXTMvvmItemContainer::items() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_itemVector;
}

/*!
@brief Inserts item in a vector of children at given index, returns true in the case of success.
@param item Item to be inserted, ownership will be taken.
@param index Item insert index in a range [0, itemCount]

Insert index is an index which item will have after insertion. If item can't be inserted
(wrong model type, wrong index or maximum number of items reached), will return false.
*/

bool QEXTMvvmItemContainer::insertItem(QEXTMvvmItem *item, int index)
{
    QEXT_DECL_D(QEXTMvvmItemContainer);
    if (!this->canInsertItem(item, index))
    {
        return false;
    }
    d->m_itemVector.insert(index, item);
    return true;
}

//! Removes item at given index and returns it to the user.

QEXTMvvmItem *QEXTMvvmItemContainer::takeItem(int index)
{
    QEXT_DECL_D(QEXTMvvmItemContainer);
    if (this->minimumReached())
    {
        return QEXT_DECL_NULLPTR;
    }

    QEXTMvvmItem *item = this->itemAt(index);
    if (item)
    {
        d->m_itemVector.removeOne(item);
    }
    return item;
}

//! Returns true if item can be taken.

bool QEXTMvvmItemContainer::canTakeItem(int index) const
{
    return this->itemAt(index) && !this->minimumReached();
}

//! Returns true if given item can be inserted under given index.

bool QEXTMvvmItemContainer::canInsertItem(QEXTMvvmItem *item, int index) const
{
    const bool validIndex = (index >= 0 && index <= this->itemCount());
    const bool enoughPlace = !this->maximumReached();
    return validIndex && enoughPlace && this->isValidItem(item);
}

//! Returns index of item in vector of items.
//! Returns -1 if item doesn't belong to us.

int QEXTMvvmItemContainer::indexOfItem(QEXTMvvmItem *item) const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_itemVector.indexOf(item);
}

//! Returns item at given index. Returns nullptr if index is invalid.

QEXTMvvmItem *QEXTMvvmItemContainer::itemAt(int index) const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    if (index >= 0 && index < d->m_itemVector.size())
    {
        return d->m_itemVector.at(index);
    }
    return QEXT_DECL_NULLPTR;
}

//! Returns the name of SessionItemTag.

QString QEXTMvvmItemContainer::name() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_tagInfo.name();
}

QEXTMvvmTagInfo QEXTMvvmItemContainer::tagInfo() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_tagInfo;
}

QEXTMvvmItemContainer::ConstIterator QEXTMvvmItemContainer::begin() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_itemVector.begin();
}

QEXTMvvmItemContainer::ConstIterator QEXTMvvmItemContainer::end() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_itemVector.end();
}

//! Returns true if no more items are allowed.

bool QEXTMvvmItemContainer::maximumReached() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_tagInfo.max() != -1 && d->m_tagInfo.max() == d->m_itemVector.size();
}

//! Returns true if less items than now is not allowed.

bool QEXTMvvmItemContainer::minimumReached() const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return d->m_tagInfo.min() != -1 && d->m_tagInfo.min() == d->m_itemVector.size();
}

//! Returns true if item's modelType is intended for this tag.

bool QEXTMvvmItemContainer::isValidItem(const QEXTMvvmItem *item) const
{
    QEXT_DECL_DC(QEXTMvvmItemContainer);
    return item && d->m_tagInfo.isValidChild(item->modelType());
}

