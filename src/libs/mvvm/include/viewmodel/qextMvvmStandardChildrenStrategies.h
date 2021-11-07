#ifndef _QEXTMVVMSTANDARDCHILDRENSTRATEGIES_H
#define _QEXTMVVMSTANDARDCHILDRENSTRATEGIES_H

//! @file childrenstrategies.h
//! @brief Collection of strategies to find children, actual of fictional, of given QEXTMvvmItem.
//! Used for QEXTMvvmViewModel generation when underlying QEXTMvvmModel changes its layout.

#include <qextMvvmChildrenStrategyInterface.h>

class QEXTMvvmItem;

//! Strategy to find children of given item: gives all actual children back.

class QEXT_MVVM_API QEXTMvvmAllChildrenStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    QVector<QEXTMvvmItem*> children(const QEXTMvvmItem* item) const QEXT_DECL_OVERRIDE;
};

//! Strategy to find children of given item: only top level items will be given, all
//! property items will be filtered out.

class QEXT_MVVM_API QEXTMvvmTopItemsStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    QVector<QEXTMvvmItem*> children(const QEXTMvvmItem* item) const QEXT_DECL_OVERRIDE;
};

//! Strategy to find children of given item: only property item will be given, all top level items
//! will be filtered out, all inactive children of QEXTMvvmGroupItem will be filtered out. See example
//! in code.

class QEXT_MVVM_API QEXTMvvmPropertyItemsStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    QVector<QEXTMvvmItem*> children(const QEXTMvvmItem* item) const QEXT_DECL_OVERRIDE;
};

//! Strategy to find children of given item: flat alignment.
//! Acts as PropertyItemStrategy, with the difference that active subproperties of
//! QEXTMvvmGroupItem are moved to the same parent, as QEXTMvvmGroupItem itself. See example in code.

class QEXT_MVVM_API QEXTMvvmPropertyItemsFlatStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    QVector<QEXTMvvmItem*> children(const QEXTMvvmItem* item) const QEXT_DECL_OVERRIDE;
};


#endif // _QEXTMVVMSTANDARDCHILDRENSTRATEGIES_H
