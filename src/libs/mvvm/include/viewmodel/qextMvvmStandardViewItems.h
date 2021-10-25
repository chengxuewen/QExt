#ifndef _QEXTMVVMSTANDARDVIEWITEMS_H
#define _QEXTMVVMSTANDARDVIEWITEMS_H

#include <qextMvvmGlobal.h>

#include <cfMvvmItem.h>
#include <cfMvvmViewItem.h>

CF_USE_NAMESPACE

//! Represents root item.

class QEXT_MVVM_API QEXTMvvmRootViewItem : public CFMvvmViewItem
{
public:
    explicit QEXTMvvmRootViewItem(CFMvvmItem *item);
};

//! Represents empty cell of tree or table.

class QEXT_MVVM_API QEXTMvvmViewEmptyItem : public CFMvvmViewItem
{
public:
    QEXTMvvmViewEmptyItem();

    CFAny data(int role) const QEXT_DECL_OVERRIDE;
};

//! Represents display name of SessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewLabelItem : public CFMvvmViewItem
{
public:
    explicit QEXTMvvmViewLabelItem(CFMvvmItem *item);

    CFAny data(int role) const QEXT_DECL_OVERRIDE;
};

//! Represents data role of SessionItem in any cell of Qt's trees and tables.

class QEXT_MVVM_API QEXTMvvmViewDataItem : public CFMvvmViewItem
{
public:
    explicit QEXTMvvmViewDataItem(CFMvvmItem *item);

    CFMvvmViewItem::ItemFlags itemFlags() const QEXT_DECL_OVERRIDE;

    CFAny data(int role) const QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMSTANDARDVIEWITEMS_H
