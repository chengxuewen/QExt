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
//! Collection of factory functions to create QExtMvvmSessionItem converters to/from serialized content.

#include "model/serialization/jsonitemconverterinterface.h"
#include <memory>

namespace ModelView {

class QExtMvvmItemFactoryInterface;

//! Creates JSON item converter intended for item cloning.

QEXT_MVVM_API QExtUniquePointer<QExtMvvmJsonItemConverterInterface>
qextMvvmCreateItemCloneConverter(const QExtMvvmItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for item copying.

QEXT_MVVM_API QExtUniquePointer<QExtMvvmJsonItemConverterInterface>
qextMvvmCreateItemCopyConverter(const QExtMvvmItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for saving on disk.

QEXT_MVVM_API QExtUniquePointer<QExtMvvmJsonItemConverterInterface>
qextMvvmCreateItemProjectConverter(const QExtMvvmItemFactoryInterface* item_factory);

} // namespace ModelView

#endif // MVVM_FACTORIES_ITEMCONVERTERFACTORY_H
