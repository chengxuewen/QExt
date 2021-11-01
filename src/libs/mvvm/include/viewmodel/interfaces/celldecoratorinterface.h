// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_CELLDECORATORINTERFACE_H
#define MVVM_INTERFACES_CELLDECORATORINTERFACE_H

#include <qextMvvmGlobal.h>
#include <string>

class QModelIndex;
class QStyleOptionViewItem;

namespace ModelView
{

//! Interface class to generate cell decorations (i.e. text) in Qt trees and tables.

class QEXT_MVVM_API CellDecoratorInterface
{
public:
    virtual ~CellDecoratorInterface() = default;

    virtual bool hasCustomDecoration(const QModelIndex& index) const = 0;
    virtual void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_CELLDECORATORINTERFACE_H
