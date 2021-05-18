#include <qextmvvmitemtags.h>
#include <qextmvvmitemtags_p.h>
#include <qextmvvmitemcontainer.h>
#include <qextmvvmitemtags.h>
#include <qextmvvmtagrow.h>
#include <qextmvvmtaginfo.h>

#include <QDebug>

QEXT_USE_NAMESPACE

QEXTMvvmItemTagsPrivate::QEXTMvvmItemTagsPrivate(QEXTMvvmItemTags *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTMvvmItemTagsPrivate::~QEXTMvvmItemTagsPrivate()
{
    qDeleteAll(m_containers);
    m_containers.clear();
}

QEXTMvvmItemContainer *QEXTMvvmItemTagsPrivate::container(const QString &tagName) const
{
    QEXT_QC(QEXTMvvmItemContainer);
    QString tagName = tagName.empty() ? q->defaultTag() : tagName;
    QEXTMvvmItemContainer *container = this->findContainer(tagName);
    if (!container) {
        QString error = QString("SessionItemTags::container() -> Error. No such container '%1'").arg(tagName);
        qFatal(error.toLatin1().data());
    }
    return container;
}

QEXTMvvmItemContainer *QEXTMvvmItemTagsPrivate::findContainer(const QString &tagName) const
{
    QVectorIterator<QEXTMvvmItemContainer *> iter(m_containers);
    while (iter.hasNext()) {
        QEXTMvvmItemContainer *container = iter.next();
        if (container->name() == tagName) {
            return container;
        }
    }
    return QEXT_NULLPTR;
}



QEXTMvvmItemTags::QEXTMvvmItemTags()
    : QEXTObject(*(new QEXTMvvmItemTagsPrivate(this)))
{

}

QEXTMvvmItemTags::~QEXTMvvmItemTags()
{

}

void QEXTMvvmItemTags::registerTag(const QEXTMvvmTagInfo &tagInfo, bool set_as_default)
{
    QEXT_D(QEXTMvvmItemTags);
    if (this->isTag(tagInfo.name())) {
        QString error = QString("SessionItemTags::registerTag() -> Error. Existing name '%1'").arg(tagInfo.name());
        qFatal(error.toLatin1().data());
    }

    d->m_containers.append(new QEXTMvvmItemContainer(tagInfo));
    if (set_as_default) {
        d->m_default_tag = tagInfo.name();
    }
}

bool QEXTMvvmItemTags::isTag(const QString &name) const
{
    QEXT_DC(QEXTMvvmItemTags);
    QVectorIterator<QEXTMvvmItemContainer *> iter(d->m_containers);
    while (iter.hasNext()) {
        QEXTMvvmItemContainer *container = iter.next();
        if (container->name() == name) {
            return true;
        }
    }
    return false;
}

QString QEXTMvvmItemTags::defaultTag() const
{
    QEXT_DC(QEXTMvvmItemTags);
    return d->m_default_tag;
}

void QEXTMvvmItemTags::setDefaultTag(const QString &name)
{
    QEXT_D(QEXTMvvmItemTags);
    d->m_default_tag = name;
}

int QEXTMvvmItemTags::itemCount(const QString &tagName) const
{
    QEXT_DC(QEXTMvvmItemTags);
    return d->container(tagName)->itemCount();
}

bool QEXTMvvmItemTags::insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow &tagrow)
{
    QEXT_D(QEXTMvvmItemTags);
    QEXTMvvmItemContainer  *tag_container = d->container(tagrow.tag);
    int row = tagrow.row < 0 ? tag_container->itemCount() : tagrow.row;
    return d->container(tagrow.tag)->insertItem(item, row);
}

QEXTMvvmItem *QEXTMvvmItemTags::takeItem(const QEXTMvvmTagRow &tagrow)
{
    QEXT_D(QEXTMvvmItemTags);
    return d->container(tagrow.tag)->takeItem(tagrow.row);
}

bool QEXTMvvmItemTags::canTakeItem(const QEXTMvvmTagRow &tagrow) const
{
    QEXT_D(QEXTMvvmItemTags);
    return d->container(tagrow.tag)->canTakeItem(tagrow.row);
}

QEXTMvvmItem *QEXTMvvmItemTags::item(const QEXTMvvmTagRow &tagrow) const
{
    QEXT_D(QEXTMvvmItemTags);
    return d->container(tagrow.tag)->itemAt(tagrow.row);
}

QVector<QEXTMvvmItem *> QEXTMvvmItemTags::items(const QString &tag) const
{
    QEXT_D(QEXTMvvmItemTags);
    return d->container(tag)->items();
}

QVector<QEXTMvvmItem *> QEXTMvvmItemTags::allitems() const
{
    QEXT_DC(QEXTMvvmItemTags);
    QVector<QEXTMvvmItem *> result;
    QVectorIterator<QEXTMvvmItemContainer *> iter(d->m_containers);
    while (iter.hasNext()) {
        QEXTMvvmItemContainer *container = iter.next();
        QList<QEXTMvvmItem *> container_items = container->items();
        result.append(container_items.toVector());
    }
    return result;
}

QEXTMvvmTagRow QEXTMvvmItemTags::tagRowOfItem(const QEXTMvvmItem *item) const
{
    QEXT_DC(QEXTMvvmItemTags);
    QVectorIterator<QEXTMvvmItemContainer *> iter(d->m_containers);
    while (iter.hasNext()) {
        QEXTMvvmItemContainer *container = iter.next();
        int row = container->indexOfItem(item);
        if (row != -1) {
            return QEXTMvvmTagRow(cont->name(), row);
        }
    }
    return QEXTMvvmTagRow();
}

QEXTMvvmItemTags::const_iterator QEXTMvvmItemTags::begin() const
{
    QEXT_DC(QEXTMvvmItemTags);
    return d->m_containers.begin();
}

QEXTMvvmItemTags::const_iterator QEXTMvvmItemTags::end() const
{
    QEXT_DC(QEXTMvvmItemTags);
    return d->m_containers.end();
}

bool QEXTMvvmItemTags::isSinglePropertyTag(const QString &tag) const
{
    QEXT_DC(QEXTMvvmItemTags);
    QEXTMvvmItemContainer *container = d->find_container(tag);
    return container ? container->tagInfo().isSinglePropertyTag() : false;
}

int QEXTMvvmItemTags::tagsCount() const
{
    QEXT_DC(QEXTMvvmItemTags);
    return static_cast<int>(d->m_containers.size());
}

QEXTMvvmItemContainer &QEXTMvvmItemTags::at(int index)
{
    QEXT_DC(QEXTMvvmItemTags);
    if (index < 0 || index >= this->tagsCount()) {
        qFatal("Error it SessionItemTags: wrong container index");
    }
    return *d->m_containers.at(index);
}


