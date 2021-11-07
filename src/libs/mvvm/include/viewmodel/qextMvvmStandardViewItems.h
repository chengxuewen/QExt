#ifndef _QEXTMVVMVIEWITEMS_H
#define _QEXTMVVMVIEWITEMS_H

#include <qextMvvmViewItem.h>


class QEXTMvvmItem;

//! Represents root item.

class QEXT_MVVM_API QEXTMvvmRootViewItem : public QEXTMvvmViewItem
{
public:
    explicit QEXTMvvmRootViewItem(QEXTMvvmItem* item);
};

//! Represents empty cell of tree or table.

class QEXT_MVVM_API QEXTMvvmViewEmptyItem : public QEXTMvvmViewItem
{
public:
    QEXTMvvmViewEmptyItem();
    QVariant data(int role) const QEXT_DECL_OVERRIDE;
};

//! Represents display name of QEXTMvvmItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewLabelItem : public QEXTMvvmViewItem
{
public:
    explicit QEXTMvvmViewLabelItem(QEXTMvvmItem *item);

    QVariant data(int role) const QEXT_DECL_OVERRIDE;
};

//! Represents data role of QEXTMvvmItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewDataItem : public QEXTMvvmViewItem
{
public:
    explicit QEXTMvvmViewDataItem(QEXTMvvmItem* item);

    Qt::ItemFlags flags() const QEXT_DECL_OVERRIDE;

    QVariant data(int role) const QEXT_DECL_OVERRIDE;
};


#endif // _QEXTMVVMVIEWITEMS_H
