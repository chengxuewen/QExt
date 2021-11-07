#ifndef _QEXTMVVMVIEWITEM_H
#define _QEXTMVVMVIEWITEM_H

#include <qextMvvmGlobal.h>

#include <QVector>
#include <QVariant>
#include <QScopedPointer>


class QEXTMvvmItem;

//! Represents the view of QEXTMvvmItem's data in a single cell of QEXTMvvmViewModel.
class QEXTMvvmViewItemPrivate;
class QEXT_MVVM_API QEXTMvvmViewItem
{
public:
    virtual ~QEXTMvvmViewItem();

    int rowCount() const;
    int columnCount() const;

    void appendRow(const QVector<QEXTMvvmViewItem *> &items);
    void insertRow(int row, const QVector<QEXTMvvmViewItem *> &items);
    void removeRow(int row);
    void clear();

    QEXTMvvmViewItem *parent() const;
    QVector<QEXTMvvmViewItem *> children() const;
    QEXTMvvmViewItem *child(int row, int column) const;
    QEXTMvvmItem *item() const;

    int column() const;
    int row() const;
    int itemRole() const;

    virtual QVariant data(int role) const;
    virtual bool setData(const QVariant &value, int role);

    virtual Qt::ItemFlags flags() const;

protected:
    QEXTMvvmViewItem(QEXTMvvmItem *item, int role);

    void setParent(QEXTMvvmViewItem *parent);

    QScopedPointer<QEXTMvvmViewItemPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmViewItem)
    QEXT_DECL_PRIVATE(QEXTMvvmViewItem)
};


#endif // _QEXTMVVMVIEWITEM_H
