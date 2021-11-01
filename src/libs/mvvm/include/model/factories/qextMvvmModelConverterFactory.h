#ifndef _QEXTMVVMMODELCONVERTERFACTORY_H
#define _QEXTMVVMMODELCONVERTERFACTORY_H

//! @file modelconverterfactory.h
//! Collection of factory functions to create QEXTMvvmSessionModel converters to/from serialized content.

#include <memory>
#include <qextMvvmJsonModelConverterInterface.h>

namespace ModelView
{

//! Creates a JSON model converter intended for model cloning.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonModelConverterInterface> CreateModelCloneConverter();

//! Creates a JSON model converter intended for model copying.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonModelConverterInterface> CreateModelCopyConverter();

//! Creates a JSON model converter intended for save/load of the project on disk.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonModelConverterInterface> CreateModelProjectConverter();

} // namespace ModelView

#endif // _QEXTMVVMMODELCONVERTERFACTORY_H
