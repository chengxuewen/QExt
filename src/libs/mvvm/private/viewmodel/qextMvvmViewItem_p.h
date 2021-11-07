#ifndef _QEXTMVVMVIEWITEM_P_H
#define _QEXTMVVMVIEWITEM_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmItem.h>

class QEXTMvvmViewItem;
class QEXT_MVVM_API QEXTMvvmViewItemPrivate
{
public:
    explicit QEXTMvvmViewItemPrivate(QEXTMvvmViewItem *q);
    virtual ~QEXTMvvmViewItemPrivate();

    void appendRow(QVector<QEXTMvvmViewItem *> items);
    void insertRow(int row, QVector<QEXTMvvmViewItem *> items);
    void removeRow(int row);

    QEXTMvvmViewItem *child(int row, int column) const;
    QEXTMvvmViewItem *parent() const;

    int indexOfChild(QEXTMvvmViewItem *child);
    QVector<QEXTMvvmViewItem*> children() const;

    QVariant data() const;

    QEXTMvvmViewItem * const q_ptr;

    int m_rows;
    int m_columns;
    int m_role;
    QEXTMvvmItem *m_item;
    QEXTMvvmViewItem *m_parentViewItem;
    QVector<QEXTMvvmViewItem *> m_children; //! buffer to hold rows x columns HOLD LIFECYCLE

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmViewItemPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmViewItem)
};

#endif // _QEXTMVVMVIEWITEM_P_H
