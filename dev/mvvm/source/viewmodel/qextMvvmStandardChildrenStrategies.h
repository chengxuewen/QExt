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
//! @brief Collection of strategies to find children, actual of fictional, of given QExtMvvmSessionItem.
//! Used for QExtMvvmViewModel generation when underlying QExtMvvmSessionModel changes its layout.

#include <qextMvvmChildrenStrategyInterface.h>

namespace ModelView {

class QExtMvvmSessionItem;

//! Strategy to find children of given item: gives all actual children back.
//! Hidden children by the current convention will be also in the list.

class QEXT_MVVM_API QExtMvvmAllChildrenStrategy : public QExtMvvmChildrenStrategyInterface {
public:
    std::vector<QExtMvvmSessionItem*> children(const QExtMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: only top level items will be given, all
//! property items will be filtered out. All items explicitly marked with setVisible(false)
//! will not show up.

class QEXT_MVVM_API QExtMvvmTopItemsStrategy : public QExtMvvmChildrenStrategyInterface {
public:
    std::vector<QExtMvvmSessionItem*> children(const QExtMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: only property item will be given, all top level items
//! will be filtered out, all inactive children of QExtMvvmGroupItem will be filtered out. See example
//! in code.

class QEXT_MVVM_API QExtMvvmPropertyItemsStrategy : public QExtMvvmChildrenStrategyInterface {
public:
    std::vector<QExtMvvmSessionItem*> children(const QExtMvvmSessionItem* item) const override;
};

//! Strategy to find children of given item: flat alignment.
//! Acts as PropertyItemStrategy, with the difference that active subproperties of
//! QExtMvvmGroupItem are moved to the same parent, as QExtMvvmGroupItem itself. See example in code.

class QEXT_MVVM_API QExtMvvmPropertyItemsFlatStrategy : public QExtMvvmChildrenStrategyInterface {
public:
    std::vector<QExtMvvmSessionItem*> children(const QExtMvvmSessionItem* item) const override;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDCHILDRENSTRATEGIES_H
