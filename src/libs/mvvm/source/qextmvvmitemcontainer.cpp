#include <qextmvvmitemcontainer.h>
#include <qextmvvmitemcontainer_p.h>

QEXT_USE_NAMESPACE

QEXTMvvmItemContainerPrivate::QEXTMvvmItemContainerPrivate(QEXTMvvmItemContainer *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTMvvmItemContainerPrivate::~QEXTMvvmItemContainerPrivate()
{
    qDeleteAll(m_items);
    m_items.clear();
}

bool QEXTMvvmItemContainerPrivate::maximum_reached() const
{
    QEXT_QC(QEXTMvvmItemContainer);
    return m_tag_info.max() != -1 && m_tag_info.max() == q->itemCount();
}

bool QEXTMvvmItemContainerPrivate::minimum_reached() const
{
    QEXT_QC(QEXTMvvmItemContainer);
    return m_tag_info.min() != -1 && m_tag_info.min() == q->itemCount();
}

bool QEXTMvvmItemContainerPrivate::is_valid_item(const QEXTMvvmItem *item) const
{
    return item && m_tag_info.isValidChild(item->modelType());
}



QEXTMvvmItemContainer::QEXTMvvmItemContainer(const QEXTMvvmTagInfo &tagInfo)
    : QEXTObject(*(new QEXTMvvmItemContainerPrivate(this)))
{
    QEXT_D(QEXTMvvmItemContainer);
    d->m_tag_info = tagInfo;
}

QEXTMvvmItemContainer::~QEXTMvvmItemContainer()
{

}

bool QEXTMvvmItemContainer::isEmpty() const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_items.isEmpty();
}

int QEXTMvvmItemContainer::itemCount() const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_items.count();
}

QList<QEXTMvvmItem *> QEXTMvvmItemContainer::items() const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_items;
}

bool QEXTMvvmItemContainer::insertItem(QEXTMvvmItem *item, int index)
{
    QEXT_D(QEXTMvvmItemContainer);
    if (!this->canInsertItem(item, index)) {
        return false;
    }
    d->m_items.insert(index, item);
    return true;
}

QEXTMvvmItem *QEXTMvvmItemContainer::takeItem(int index)
{
    QEXT_D(QEXTMvvmItemContainer);
    if (d->minimum_reached()) {
        return QEXT_NULLPTR;
    }

    QEXTMvvmItem *result = this->itemAt(index);
    if (result) {
        d->m_items.erase(index);
    }
    return result;
}

bool QEXTMvvmItemContainer::canTakeItem(int index) const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return this->itemAt(index) && !d->minimum_reached();
}

bool QEXTMvvmItemContainer::canInsertItem(const QEXTMvvmItem *item, int index) const
{
    QEXT_DC(QEXTMvvmItemContainer);
    const bool valid_index = (index >= 0 && index <= this->itemCount());
    const bool enough_place = !d->maximum_reached();
    return valid_index && enough_place && d->is_valid_item(item);
}

int QEXTMvvmItemContainer::indexOfItem(const QEXTMvvmItem *item) const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_items.indexOf(item);
}

QEXTMvvmItem *QEXTMvvmItemContainer::itemAt(int index) const
{
    QEXT_DC(QEXTMvvmItemContainer);
    if (index >= 0 && index <= d->m_items.size()) {
        return d->m_items.at(index);
    }
    return QEXT_NULLPTR;
}

QString QEXTMvvmItemContainer::name() const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_tag_info.name();
}

QEXTMvvmTagInfo QEXTMvvmItemContainer::tagInfo() const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_tag_info;
}

QEXTMvvmItemContainer::const_iterator QEXTMvvmItemContainer::begin() const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_items.begin();
}

QEXTMvvmItemContainer::const_iterator QEXTMvvmItemContainer::end() const
{
    QEXT_DC(QEXTMvvmItemContainer);
    return d->m_items.end();
}
