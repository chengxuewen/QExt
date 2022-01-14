#ifndef _QEXTMVVMFACTORIESITEMCONVERTERFACTORY_H
#define _QEXTMVVMFACTORIESITEMCONVERTERFACTORY_H

#include <qextMvvmJsonItemConverterInterface.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmItemFactoryInterface;

//! Creates JSON item converter intended for item cloning.

QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonItemConverterInterface>
CreateItemCloneConverter(const QEXTMvvmItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for item copying.

QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonItemConverterInterface>
CreateItemCopyConverter(const QEXTMvvmItemFactoryInterface* item_factory);

//! Creates JSON item converter intended for saving on disk.

QEXT_MVVM_API std::unique_ptr<QEXTMvvmJsonItemConverterInterface>
CreateItemProjectConverter(const QEXTMvvmItemFactoryInterface* item_factory);

} // namespace ModelView

#endif // _QEXTMVVMFACTORIESITEMCONVERTERFACTORY_H
