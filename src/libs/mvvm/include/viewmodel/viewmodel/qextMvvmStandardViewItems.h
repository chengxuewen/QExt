#ifndef _QEXTMVVMVIEWMODELVIEWITEMS_H
#define _QEXTMVVMVIEWMODELVIEWITEMS_H

#include <qextMvvmViewItem.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Represents root item.

class QEXT_MVVM_API QEXTMvvmRootViewItem : public QEXTMvvmViewItem
{
public:
    explicit QEXTMvvmRootViewItem(QEXTMvvmSessionItem* item);
};

//! Represents empty cell of tree or table.

class QEXT_MVVM_API QEXTMvvmViewEmptyItem : public QEXTMvvmViewItem
{
public:
    QEXTMvvmViewEmptyItem();
    QVariant data(int role) const override;
};

//! Represents display name of QEXTMvvmSessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewLabelItem : public QEXTMvvmViewItem
{
public:
    explicit QEXTMvvmViewLabelItem(QEXTMvvmSessionItem* item);

    QVariant data(int role) const override;
};

//! Represents data role of QEXTMvvmSessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewDataItem : public QEXTMvvmViewItem
{
public:
    explicit QEXTMvvmViewDataItem(QEXTMvvmSessionItem* item);

    Qt::ItemFlags flags() const override;

    QVariant data(int role) const override;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELVIEWITEMS_H
