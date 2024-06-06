#include <qextModelItemContainer.h>
#include <qextContainerUtils.h>
#include <qextModelTagInfo.h>
#include <qextModelItem.h>

class QExtModelItemContainerPrivate
{
public:
    explicit QExtModelItemContainerPrivate(QExtModelItemContainer *q);
    virtual ~QExtModelItemContainerPrivate();

    //! Returns true if no more items are allowed.
    bool maximumReached() const;
    //! Returns true if less items than now is not allowed.
    bool minimumReached() const;
    //! Returns true if item's modelType is intended for this tag.
    bool isValidItem(const QExtModelItem *item) const;

    QExtModelItemContainer * const q_ptr;

    QExtModelTagInfo m_tagInfo;
    QExtModelItemContainer::Container m_items;

private:
    QEXT_DECL_PUBLIC(QExtModelItemContainer)
    QEXT_DISABLE_COPY_MOVE(QExtModelItemContainerPrivate)
};

QExtModelItemContainerPrivate::QExtModelItemContainerPrivate(QExtModelItemContainer *q)
    : q_ptr(q)
{

}

QExtModelItemContainerPrivate::~QExtModelItemContainerPrivate()
{
    qDeleteAll(m_items);
}

bool QExtModelItemContainerPrivate::maximumReached() const
{
    return m_tagInfo.max() != -1 && m_tagInfo.max() == m_items.size();
}

bool QExtModelItemContainerPrivate::minimumReached() const
{
    return m_tagInfo.min() != -1 && m_tagInfo.min() == m_items.size();
}

bool QExtModelItemContainerPrivate::isValidItem(const QExtModelItem *item) const
{
    return item && m_tagInfo.isValidChild(item->modelType());
}

QExtModelItemContainer::QExtModelItemContainer(const QExtModelTagInfo &tagInfo)
    : dd_ptr(new QExtModelItemContainerPrivate(this))
{
    dd_ptr->m_tagInfo = tagInfo;
}

QExtModelItemContainer::~QExtModelItemContainer()
{

}

bool QExtModelItemContainer::isEmpty() const
{
    Q_D(const QExtModelItemContainer);
    return d->m_items.isEmpty();
}

int QExtModelItemContainer::itemCount() const
{
    Q_D(const QExtModelItemContainer);
    return d->m_items.size();
}

QVector<QExtModelItem *> QExtModelItemContainer::items() const
{
    Q_D(const QExtModelItemContainer);
    return d->m_items;
}

QExtModelItem *QExtModelItemContainer::itemAt(int index) const
{
    Q_D(const QExtModelItemContainer);
    return index >= 0 && index < itemCount() ? d->m_items[static_cast<size_t>(index)] : nullptr;
}

QExtModelItem *QExtModelItemContainer::takeItem(int index)
{
    Q_D(QExtModelItemContainer);
    if (d->minimumReached())
    {
        return QEXT_NULLPTR;
    }

    QExtModelItem *result = itemAt(index);
    if (result)
    {
        d->m_items.erase(std::next(d->m_items.begin(), index));
    }
    return result;
}

bool QExtModelItemContainer::insertItem(QExtModelItem *item, int index)
{
    Q_D(QExtModelItemContainer);
    if (!this->canInsertItem(item, index))
    {
        return false;
    }

    d->m_items.insert(std::next(d->m_items.begin(), index), item);
    return true;
}

bool QExtModelItemContainer::canTakeItem(int index) const
{
    Q_D(const QExtModelItemContainer);
    return this->itemAt(index) && !d->minimumReached();
}

int QExtModelItemContainer::indexOfItem(QExtModelItem *item) const
{
    Q_D(const QExtModelItemContainer);
    return d->m_items.indexOf(item);
}

bool QExtModelItemContainer::canInsertItem(const QExtModelItem *item, int index) const
{
    Q_D(const QExtModelItemContainer);
    const bool validIndex = (index >= 0 && index <= this->itemCount());
    const bool enoughPlace = !d->maximumReached();
    return validIndex && enoughPlace && d->isValidItem(item);
}

QString QExtModelItemContainer::name() const
{
    Q_D(const QExtModelItemContainer);
    return d->m_tagInfo.name();
}

QExtModelTagInfo QExtModelItemContainer::tagInfo() const
{
    Q_D(const QExtModelItemContainer);
    return d->m_tagInfo;
}

QExtModelItemContainer::ConstIterator QExtModelItemContainer::begin() const
{
    Q_D(const QExtModelItemContainer);
    return d->m_items.begin();
}

QExtModelItemContainer::ConstIterator QExtModelItemContainer::end() const
{
    Q_D(const QExtModelItemContainer);
    return d->m_items.end();
}
