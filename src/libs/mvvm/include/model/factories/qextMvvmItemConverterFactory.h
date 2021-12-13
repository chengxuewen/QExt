// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_ITEMCONVERTERFACTORY_H
#define MVVM_FACTORIES_ITEMCONVERTERFACTORY_H

//! @file itemconverterfactory.h
//! Collection of factory functions to create QEXTMvvmSessionItem converters to/from serialized content.

#include <memory>
#include <serialization/qextMvvmJsonItemConverterInterface.h>

namespace ModelView
{

class QEXTMvvmItemFactoryInterface;

//! Creates JSON item converter intended for item cloning.

QEXT_MVVM_API std::unique_ptr<JsonItemConverterInterface>
CreateItemCloneConverter(const QEXTMvvmItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for item copying.

QEXT_MVVM_API std::unique_ptr<JsonItemConverterInterface>
CreateItemCopyConverter(const QEXTMvvmItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for saving on disk.

QEXT_MVVM_API std::unique_ptr<JsonItemConverterInterface>
CreateItemProjectConverter(const QEXTMvvmItemFactoryInterface* item_factory);

} // namespace ModelView

#endif // MVVM_FACTORIES_ITEMCONVERTERFACTORY_H
