// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_ITEMCATALOGUEFACTORY_H
#define MVVM_FACTORIES_ITEMCATALOGUEFACTORY_H

#include <qextMvvmItemCatalogue.h>

namespace ModelView {

//! Creates a catalog of items supported by QExtMvvmSessionModel out-of-the-box.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmItemCatalogue> qextMvvmCreateStandardItemCatalogue();

} // namespace ModelView

#endif // MVVM_FACTORIES_ITEMCATALOGUEFACTORY_H
