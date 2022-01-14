#ifndef _QEXTMVVMVIEWMODELSTANDARDCHILDRENSTRATEGIES_H
#define _QEXTMVVMVIEWMODELSTANDARDCHILDRENSTRATEGIES_H

//! @file childrenstrategies.h
//! @brief Collection of strategies to find children, actual of fictional, of given QEXTMvvmSessionItem.
//! Used for ViewModel generation when underlying SessionModel changes its layout.

#include <qextMvvmChildrenStrategyInterface.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Strategy to find children of given item: gives all actual children back.

class QEXT_MVVM_API QEXTMvvmAllChildrenStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: only top level items will be given, all
//! property items will be filtered out.

class QEXT_MVVM_API QEXTMvvmTopItemsStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: only property item will be given, all top level items
//! will be filtered out, all inactive children of GroupItem will be filtered out. See example
//! in code.

class QEXT_MVVM_API QEXTMvvmPropertyItemsStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: flat alignment.
//! Acts as PropertyItemStrategy, with the difference that active subproperties of
//! GroupItem are moved to the same parent, as GroupItem itself. See example in code.

class QEXT_MVVM_API QEXTMvvmPropertyItemsFlatStrategy : public QEXTMvvmChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELSTANDARDCHILDRENSTRATEGIES_H
