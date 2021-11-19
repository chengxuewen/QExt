#ifndef _QEXTMVVMITEMCONTAINER_H
#define _QEXTMVVMITEMCONTAINER_H

#include <qextMvvmTagInfo.h>
#include <qextMvvmGlobal.h>

#include <QVector>
#include <QSharedPointer>


class QEXTMvvmItem;

//! Holds collection of QEXTMvvmItem objects related to the same tag.
class QEXTMvvmItemContainerPrivate;
class QEXT_MVVM_API QEXTMvvmItemContainer
{
public:
    typedef QVector<QEXTMvvmItem *>                 ItemVector;
    typedef ItemVector::ConstIterator               ConstIterator;
    typedef ItemVector::Iterator                    Iterator;

    QEXTMvvmItemContainer(const QEXTMvvmTagInfo &tagInfo);
    virtual ~QEXTMvvmItemContainer();

    bool isEmpty() const;
    int itemCount() const;

    QVector<QEXTMvvmItem *> items() const;
    QEXTMvvmItem *takeItem(int index);
    QEXTMvvmItem *itemAt(int index) const;

    bool canTakeItem(int index) const;
    bool canInsertItem(QEXTMvvmItem *item, int index) const;

    int indexOfItem(QEXTMvvmItem *item) const;
    bool insertItem(QEXTMvvmItem *item, int index);

    QString name() const;
    QEXTMvvmTagInfo tagInfo() const;

    ConstIterator begin() const;
    ConstIterator end() const;

protected:
    bool maximumReached() const;
    bool minimumReached() const;
    bool isValidItem(const QEXTMvvmItem *item) const;

    QScopedPointer<QEXTMvvmItemContainerPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemContainer)
    Q_DECLARE_PRIVATE(QEXTMvvmItemContainer)
};


#endif // _QEXTMVVMITEMCONTAINER_H
