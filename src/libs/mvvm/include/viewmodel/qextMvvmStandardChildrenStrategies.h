#ifndef _QEXTMVVMSTANDARDCHILDRENSTRATEGIES_H
#define _QEXTMVVMSTANDARDCHILDRENSTRATEGIES_H

#include <qextMvvmGlobal.h>

#include <cfMvvmChildrenStrategyInterface.h>

CF_USE_NAMESPACE

//! Strategy to find children of given item: gives all actual children back.

class QEXT_MVVM_API QEXTMvvmAllChildrenStrategy : public CFMvvmChildrenStrategyInterface
{
public:
    std::list<CFMvvmItem *> children(const CFMvvmItem *item) const QEXT_DECL_OVERRIDE;
};

//! Strategy to find children of given item: only top level items will be given, all
//! property items will be filtered out.

class QEXT_MVVM_API QEXTMvvmTopItemsStrategy : public CFMvvmChildrenStrategyInterface
{
public:
    std::list<CFMvvmItem *> children(const CFMvvmItem *item) const QEXT_DECL_OVERRIDE;
};

//! Strategy to find children of given item: only property item will be given, all top level items
//! will be filtered out, all inactive children of GroupItem will be filtered out. See example
//! in code.

class QEXT_MVVM_API QEXTMvvmPropertyItemsStrategy : public CFMvvmChildrenStrategyInterface
{
public:
    std::list<CFMvvmItem *> children(const CFMvvmItem *item) const QEXT_DECL_OVERRIDE;
};

//! Strategy to find children of given item: flat alignment.
//! Acts as PropertyItemStrategy, with the difference that active subproperties of
//! GroupItem are moved to the same parent, as GroupItem itself. See example in code.

class QEXT_MVVM_API QEXTMvvmPropertyItemsFlatStrategy : public CFMvvmChildrenStrategyInterface
{
public:
    std::list<CFMvvmItem *> children(const CFMvvmItem *item) const QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMSTANDARDCHILDRENSTRATEGIES_H
