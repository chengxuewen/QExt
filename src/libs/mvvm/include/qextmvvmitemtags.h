#ifndef QEXTMVVMITEMTAGS_H
#define QEXTMVVMITEMTAGS_H

#include <qextmvvmglobal.h>

#include <qextobject.h>

#include <QVector>



class QEXTMvvmItem;
class QEXTMvvmTagRow;
class QEXTMvvmTagInfo;
class QEXTMvvmItemContainer;
class QEXTMvvmItemTagsPrivate;
class QEXT_MVVM_API QEXTMvvmItemTags : public QEXTObject
{
public:
    typedef QVector<QEXTMvvmItemContainer *> container_t;
    typedef container_t::const_iterator const_iterator;

    QEXTMvvmItemTags();
    ~QEXTMvvmItemTags();

    void registerTag(const QEXTMvvmTagInfo &tagInfo, bool set_as_default = false);
    bool isTag(const QString &name) const;

    QString defaultTag() const;
    void setDefaultTag(const QString &name);

    int itemCount(const QString &tagName) const;

    // adding and removal
    bool insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow & tagrow);
    QEXTMvvmItem *takeItem(const QEXTMvvmTagRow &tagrow);
    bool canTakeItem(const QEXTMvvmTagRow &tagrow) const;

    // item access
    QEXTMvvmItem *item(const QEXTMvvmTagRow &tagrow) const;
    QVector<QEXTMvvmItem *> items(const QString &tag = "") const;
    QVector<QEXTMvvmItem *> allitems() const;

    QEXTMvvmTagRow tagRowOfItem(const QEXTMvvmItem *item) const;

    const_iterator begin() const;
    const_iterator end() const;

    bool isSinglePropertyTag(const QString &tag) const;

    int tagsCount() const;
    QEXTMvvmItemContainer &at(int index);

private:
    QEXT_DECLARE_PRIVATE(QEXTMvvmItemTags)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItemTags)
};



#endif // QEXTMVVMITEMTAGS_H
