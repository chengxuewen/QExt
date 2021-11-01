// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H
#define MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H

//! @file childrenstrategies.h
//! @brief Collection of strategies to find children, actual of fictional, of given QEXTMvvmSessionItem.
//! Used for ViewModel generation when underlying QEXTMvvmSessionModel changes its layout.

#include <childrenstrategyinterface.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Strategy to find children of given item: gives all actual children back.

class QEXT_MVVM_API AllChildrenStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: only top level items will be given, all
//! property items will be filtered out.

class QEXT_MVVM_API TopItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: only property item will be given, all top level items
//! will be filtered out, all inactive children of QEXTMvvmGroupItem will be filtered out. See example
//! in code.

class QEXT_MVVM_API PropertyItemsStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: flat alignment.
//! Acts as PropertyItemStrategy, with the difference that active subproperties of
//! QEXTMvvmGroupItem are moved to the same parent, as QEXTMvvmGroupItem itself. See example in code.

class QEXT_MVVM_API PropertyItemsFlatStrategy : public ChildrenStrategyInterface
{
public:
    std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H
