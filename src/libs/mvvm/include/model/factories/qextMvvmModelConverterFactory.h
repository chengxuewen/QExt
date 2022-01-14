#ifndef _QEXTMVVMFACTORIESMODELCONVERTERFACTORY_H
#define _QEXTMVVMFACTORIESMODELCONVERTERFACTORY_H

#include <qextMvvmJsonModelConverterInterface.h>

#include <memory>

namespace ModelView
{

//! Creates a JSON model converter intended for model cloning.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonModelConverterInterface> CreateModelCloneConverter();

//! Creates a JSON model converter intended for model copying.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonModelConverterInterface> CreateModelCopyConverter();

//! Creates a JSON model converter intended for save/load of the project on disk.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonModelConverterInterface> CreateModelProjectConverter();

} // namespace ModelView

#endif // _QEXTMVVMFACTORIESMODELCONVERTERFACTORY_H
