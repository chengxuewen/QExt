#ifndef QEXTMVVMITEMCONTAINER_H
#define QEXTMVVMITEMCONTAINER_H

#include <qextmvvmglobal.h>

#include <qextobject.h>

#include <QList>



class QEXTMvvmItem;
class QEXTMvvmTagInfo;
class QEXTMvvmItemContainerPrivate;
class QEXT_MVVM_API QEXTMvvmItemContainer : public QEXTObject
{
public:
    typedef QList<QEXTMvvmItem *> container_t;
    typedef container_t::const_iterator const_iterator;

    QEXTMvvmItemContainer(const QEXTMvvmTagInfo &tagInfo);
    ~QEXTMvvmItemContainer();

    bool isEmpty() const;
    int itemCount() const;
    QList<QEXTMvvmItem *> items() const;

    bool insertItem(QEXTMvvmItem *item, int index);
    QEXTMvvmItem *takeItem(int index);
    bool canTakeItem(int index) const;
    bool canInsertItem(const QEXTMvvmItem *item, int index) const;
    int indexOfItem(const QEXTMvvmItem *item) const;
    QEXTMvvmItem *itemAt(int index) const;

    QString name() const;
    QEXTMvvmTagInfo tagInfo() const;

    const_iterator begin() const;
    const_iterator end() const;

private:
    QEXT_DECLARE_PRIVATE(QEXTMvvmItemContainer)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItemContainer)
};



#endif // QEXTMVVMITEMCONTAINER_H
