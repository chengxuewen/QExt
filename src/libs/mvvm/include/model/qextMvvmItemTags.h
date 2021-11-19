#ifndef _QEXTMVVMITEMTAGS_H
#define _QEXTMVVMITEMTAGS_H

#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>

#include <QVector>
#include <QSharedPointer>

class QEXTMvvmItemContainer;
class QEXTMvvmItem;
class QEXTMvvmTagInfo;

//! Collection of QEXTMvvmItem's containers according to their tags.
class QEXTMvvmItemTagsPrivate;
class QEXT_MVVM_API QEXTMvvmItemTags
{
public:
    typedef QVector<QEXTMvvmItemContainer *>                    ItemContainerVector;
    typedef ItemContainerVector::ConstIterator                  ConstIterator;
    typedef ItemContainerVector::Iterator                       Iterator;

    QEXTMvvmItemTags();
    virtual ~QEXTMvvmItemTags();

    void registerTag(const QEXTMvvmTagInfo &tagInfo, bool setAsDefault = false);
    bool isTag(const QString &name) const;

    QString defaultTag() const;
    void setDefaultTag(const QString &tagName);

    int tagsCount() const;
    QEXTMvvmTagRow tagRowOfItem(QEXTMvvmItem *item) const;
    bool isSinglePropertyTag(const QString &tag) const;

    int itemCount(const QString &tagName) const;
    bool insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow &tagrow);

    // item access
    bool canTakeItem(const QEXTMvvmTagRow &tagrow) const;
    QEXTMvvmItem *takeItem(const QEXTMvvmTagRow &tagrow);
    QEXTMvvmItem *getItem(const QEXTMvvmTagRow &tagrow) const;
    QVector<QEXTMvvmItem *> getItems(const QString &tag = QString()) const;
    QVector<QEXTMvvmItem *> allItems() const;

    ConstIterator begin() const;
    ConstIterator end() const;

    QEXTMvvmItemContainer &at(int index);

protected:
    QEXTMvvmItemContainer *container(const QString &tagName) const;
    QEXTMvvmItemContainer *findContainer(const QString &tagName) const;

    QScopedPointer<QEXTMvvmItemTagsPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemTags)
    Q_DECLARE_PRIVATE(QEXTMvvmItemTags)
};

#endif // _QEXTMVVMITEMTAGS_H
