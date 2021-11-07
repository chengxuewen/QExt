#include <qextMvvmItemTags.h>
#include <qextMvvmItemTags_p.h>
#include <qextMvvmItemContainer.h>

#include <stdexcept>

QEXTMvvmItemTagsPrivate::QEXTMvvmItemTagsPrivate(QEXTMvvmItemTags *q)
    : q_ptr(q)
{

}

QEXTMvvmItemTagsPrivate::~QEXTMvvmItemTagsPrivate()
{
    qDeleteAll(m_containerVector);
    m_containerVector.clear();
}



QEXTMvvmItemTags::QEXTMvvmItemTags()
    : d_ptr(new QEXTMvvmItemTagsPrivate(this))
{

}

QEXTMvvmItemTags::~QEXTMvvmItemTags()
{

}

void QEXTMvvmItemTags::registerTag(const QEXTMvvmTagInfo &tagInfo, bool setAsDefault)
{
    QEXT_DECL_D(QEXTMvvmItemTags);
    if (this->isTag(tagInfo.name()))
    {
        throw std::runtime_error("QEXTMvvmItemTags::registerTag() -> Error. Existing name '" + tagInfo.name().toStdString() + "'");
    }

    d->m_containerVector.append(new QEXTMvvmItemContainer(tagInfo));
    if (setAsDefault)
    {
        d->m_defaultTag = tagInfo.name();
    }
}

//! Returns true if container with such name exists.

bool QEXTMvvmItemTags::isTag(const QString &name) const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    for (int i = 0; i < d->m_containerVector.size(); ++i)
    {
        if (d->m_containerVector.at(i)->name() == name)
        {
            return true;
        }
    }
    return false;
}

//! Returns the name of the default tag.

QString QEXTMvvmItemTags::defaultTag() const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    return d->m_defaultTag;
}

void QEXTMvvmItemTags::setDefaultTag(const QString &tagName)
{
    QEXT_DECL_D(QEXTMvvmItemTags);
    d->m_defaultTag = tagName;
}

int QEXTMvvmItemTags::itemCount(const QString &tagName) const
{
    return this->container(tagName)->itemCount();
}

//! Inserts item in container with given tag name and at given row.
//! Returns true in the case of success. If tag name is empty, default tag will be used.
//!
bool QEXTMvvmItemTags::insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow &tagrow)
{
    QEXTMvvmItemContainer *container = this->container(tagrow.tag);
    int row = tagrow.row < 0 ? container->itemCount() : tagrow.row;
    return this->container(tagrow.tag)->insertItem(item, row);
}

//! Removes item at given row and for given tag, returns it to the user.

QEXTMvvmItem *QEXTMvvmItemTags::takeItem(const QEXTMvvmTagRow &tagrow)
{
    return this->container(tagrow.tag)->takeItem(tagrow.row);
}

//! Returns true if item can be taken.

bool QEXTMvvmItemTags::canTakeItem(const QEXTMvvmTagRow& tagrow) const
{
    return this->container(tagrow.tag)->canTakeItem(tagrow.row);
}

QEXTMvvmItem *QEXTMvvmItemTags::getItem(const QEXTMvvmTagRow &tagrow) const
{
    return this->container(tagrow.tag)->itemAt(tagrow.row);
}

QVector<QEXTMvvmItem *> QEXTMvvmItemTags::getItems(const QString &tag) const
{
    return this->container(tag)->items();
}

QVector<QEXTMvvmItem *> QEXTMvvmItemTags::allItems() const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    QVector<QEXTMvvmItem *> result;
    for (int i = 0; i < d->m_containerVector.size(); ++i)
    {
        QVector<QEXTMvvmItem *> containerItems = d->m_containerVector.at(i)->items();
        result.append(containerItems);
    }
    return result;
}

//! Returns tag name and row of item in container.

QEXTMvvmTagRow QEXTMvvmItemTags::tagRowOfItem(QEXTMvvmItem *item) const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    for (int i = 0; i < d->m_containerVector.size(); ++i)
    {
        QEXTMvvmItemContainer *container = d->m_containerVector.at(i);
        int row = container->indexOfItem(item);
        if (row != -1)
        {
            return QEXTMvvmTagRow(container->name(), row);
        }
    }
    return QEXTMvvmTagRow();
}

QEXTMvvmItemTags::ConstIterator QEXTMvvmItemTags::begin() const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    return d->m_containerVector.begin();
}

QEXTMvvmItemTags::ConstIterator QEXTMvvmItemTags::end() const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    return d->m_containerVector.end();
}

//! Returns true if given tag corresponds to registered single property tag.

bool QEXTMvvmItemTags::isSinglePropertyTag(const QString &tag) const
{
    QEXTMvvmItemContainer *container = this->findContainer(tag);
    return container ? container->tagInfo().isSinglePropertyTag() : false;
}

int QEXTMvvmItemTags::tagsCount() const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    return d->m_containerVector.size();
}

QEXTMvvmItemContainer &QEXTMvvmItemTags::at(int index)
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    if (index < 0 || index >= this->tagsCount())
    {
        throw std::runtime_error("Error it QEXTMvvmItemTags: wrong container index");
    }
    return *(d->m_containerVector.at(index));
}

//! Returns container corresponding to given tag name. If name is empty,
//! default tag will be used. Exception is thrown if no such tag exists.

QEXTMvvmItemContainer *QEXTMvvmItemTags::container(const QString &tagName) const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    QString validTagName = tagName.isEmpty() ? this->defaultTag() : tagName;
    QEXTMvvmItemContainer *container = this->findContainer(validTagName);
    if (!container)
    {
        throw std::runtime_error("QEXTMvvmItemTags::container() -> Error. No such container '" + tagName.toStdString() + "'");
    }
    return container;
}

//! Returns container corresponding to given tag name.

QEXTMvvmItemContainer *QEXTMvvmItemTags::findContainer(const QString &tagName) const
{
    QEXT_DECL_DC(QEXTMvvmItemTags);
    for (int i = 0; i < d->m_containerVector.size(); ++i)
    {
        if (d->m_containerVector.at(i)->name() == tagName)
        {
            return d->m_containerVector.at(i);
        }
    }
    return QEXT_DECL_NULLPTR;
}
