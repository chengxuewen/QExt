#include <qextModelItemTags.h>
#include <qextModelItemContainer.h>
#include <qextModelTagInfo.h>
#include <qextModelTagRow.h>

#include <QDebug>

class QExtModelItemTagsPrivate
{
public:
    explicit QExtModelItemTagsPrivate(QExtModelItemTags *q);
    virtual ~QExtModelItemTagsPrivate();

    //! Returns container corresponding to given tag name. If name is empty,
    //! default tag will be used. Exception is thrown if no such tag exists.
    QExtModelItemContainer *container(const QString &tagName) const;
    //! Returns container corresponding to given tag name.
    QExtModelItemContainer *findContainer(const QString &tagName) const;

    QExtModelItemTags *const q_ptr;

    QString m_defaultTag;
    QVector<QExtModelItemContainer *> m_containers;

private:
    QEXT_DECL_PUBLIC(QExtModelItemTags)
    QEXT_DISABLE_COPY_MOVE(QExtModelItemTagsPrivate)
};

QExtModelItemTagsPrivate::QExtModelItemTagsPrivate(QExtModelItemTags *q)
    : q_ptr(q)
{

}

QExtModelItemTagsPrivate::~QExtModelItemTagsPrivate()
{
    qDeleteAll(m_containers);
}

QExtModelItemContainer *QExtModelItemTagsPrivate::container(const QString &tagName) const
{
    QString name = tagName.isEmpty() ? m_defaultTag : tagName;
    QExtModelItemContainer *container = this->findContainer(name);
    if (!container)
    {
        qCritical() << QString("QExtModelItemContainer::container() -> Error. No such container '%1'").arg(tagName);
    }
    return container;
}

QExtModelItemContainer *QExtModelItemTagsPrivate::findContainer(const QString &tagName) const
{
    for (QExtModelItemTags::ConstIterator iter = m_containers.begin(); iter != m_containers.end(); ++iter)
    {
        if ((*iter)->name() == tagName)
        {
            return *iter;
        }
    }
    return QEXT_NULLPTR;
}

QExtModelItemTags::QExtModelItemTags()
    : dd_ptr(new QExtModelItemTagsPrivate(this))
{

}

QExtModelItemTags::~QExtModelItemTags()
{

}

int QExtModelItemTags::itemCount(const QString &tagName) const
{
    Q_D(const QExtModelItemTags);
    return d->container(tagName)->itemCount();
}

QString QExtModelItemTags::defaultTag() const
{
    Q_D(const QExtModelItemTags);
    return d->m_defaultTag;
}

void QExtModelItemTags::setDefaultTag(const QString &name)
{
    Q_D(QExtModelItemTags);
    d->m_defaultTag = name;
}

bool QExtModelItemTags::isTag(const QString &name) const
{
    Q_D(const QExtModelItemTags);
    for (ConstIterator iter = d->m_containers.begin(); iter != d->m_containers.end(); ++iter)
    {
        if ((*iter)->name() == name)
        {
            return true;
        }
    }
    return false;
}

void QExtModelItemTags::registerTag(const QExtModelTagInfo &tagInfo, bool setAsDefault)
{
    Q_D(QExtModelItemTags);
    if (this->isTag(tagInfo.name()))
    {
        qCritical() << QString("QExtModelItemTags::registerTag() -> Error. Existing name '%1'").arg(tagInfo.name());
        return;
    }

    d->m_containers.push_back(new QExtModelItemContainer(tagInfo));
    if (setAsDefault)
    {
        d->m_defaultTag = tagInfo.name();
    }
}

bool QExtModelItemTags::canTakeItem(const QExtModelTagRow &tagRow) const
{
    Q_D(const QExtModelItemTags);
    return d->container(tagRow.tag)->canTakeItem(tagRow.row);
}

bool QExtModelItemTags::insertItem(QExtModelItem *item, const QExtModelTagRow &tagRow)
{
    Q_D(QExtModelItemTags);
    QExtModelItemContainer *tagContainer = d->container(tagRow.tag);
    int row = tagRow.row < 0 ? tagContainer->itemCount() : tagRow.row;
    return d->container(tagRow.tag)->insertItem(item, row);
}

QExtModelItem *QExtModelItemTags::takeItem(const QExtModelTagRow &tagRow)
{
    Q_D(QExtModelItemTags);
    return d->container(tagRow.tag)->takeItem(tagRow.row);
}

QVector<QExtModelItem *> QExtModelItemTags::allItems() const
{
    Q_D(const QExtModelItemTags);
    QVector<QExtModelItem *> result;
    for (ConstIterator iter = d->m_containers.begin(); iter != d->m_containers.end(); ++iter)
    {
        QVector<QExtModelItem *> containerItems = (*iter)->items();
        result.append(containerItems);
    }
    return result;
}

QVector<QExtModelItem *> QExtModelItemTags::getItems(const QString &tag) const
{
    Q_D(const QExtModelItemTags);
    return d->container(tag)->items();
}

QExtModelItem *QExtModelItemTags::getItem(const QExtModelTagRow &tagRow) const
{
    Q_D(const QExtModelItemTags);
    return d->container(tagRow.tag)->itemAt(tagRow.row);
}

QExtModelTagRow QExtModelItemTags::tagRowOfItem(QExtModelItem *item) const
{
    Q_D(const QExtModelItemTags);
    for (ConstIterator iter = d->m_containers.begin(); iter != d->m_containers.end(); ++iter)
    {
        int row = (*iter)->indexOfItem(item);
        if (row != -1)
        {
            return QExtModelTagRow((*iter)->name(), row);
        }
    }
    return QExtModelTagRow();
}

QExtModelItemTags::ConstIterator QExtModelItemTags::begin() const
{
    Q_D(const QExtModelItemTags);
    return d->m_containers.begin();
}

QExtModelItemTags::ConstIterator QExtModelItemTags::end() const
{
    Q_D(const QExtModelItemTags);
    return d->m_containers.end();
}

int QExtModelItemTags::tagsCount() const
{
    Q_D(const QExtModelItemTags);
    return static_cast<int>(d->m_containers.size());
}

bool QExtModelItemTags::isSinglePropertyTag(const QString &tag) const
{
    Q_D(const QExtModelItemTags);
    QExtModelItemContainer *container = d->findContainer(tag);
    return container ? container->tagInfo().isSinglePropertyTag() : false;
}

QExtModelItemContainer &QExtModelItemTags::at(int index)
{
    Q_D(QExtModelItemTags);
    if (index < 0 || index >= tagsCount())
    {
        qFatal("QExtModelItemTags::at():index out of range!");
    }
    return *d->m_containers.at(index);
}
