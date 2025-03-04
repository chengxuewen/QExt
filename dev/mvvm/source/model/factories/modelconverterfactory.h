// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_MODELCONVERTERFACTORY_H
#define MVVM_FACTORIES_MODELCONVERTERFACTORY_H

//! @file modelconverterfactory.h
//! Collection of factory functions to create QExtMvvmSessionModel converters to/from serialized content.

#include "model/serialization/jsonmodelconverterinterface.h"
#include <memory>

namespace ModelView {

//! Creates a JSON model converter intended for model cloning.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmJsonModelConverterInterface> qextMvvmCreateModelCloneConverter();

//! Creates a JSON model converter intended for model copying.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmJsonModelConverterInterface> qextMvvmCreateModelCopyConverter();

//! Creates a JSON model converter intended for save/load of the project on disk.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmJsonModelConverterInterface> qextMvvmCreateModelProjectConverter();

} // namespace ModelView

#endif // MVVM_FACTORIES_MODELCONVERTERFACTORY_H
