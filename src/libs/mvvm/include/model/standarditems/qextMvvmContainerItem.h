// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_CONTAINERITEM_H
#define MVVM_STANDARDITEMS_CONTAINERITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

//! Simple container to store any type of children.
//! Used as convenience item to create branch with uniform children beneath.

class QEXT_MVVM_API ContainerItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string T_ITEMS = "T_ITEMS";

    ContainerItem(const std::string& modelType = Constants::ContainerItemType);

    bool empty() const;

    size_t size() const;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_CONTAINERITEM_H
