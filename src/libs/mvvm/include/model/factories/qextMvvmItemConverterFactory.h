#ifndef _QEXTMVVMITEMCONVERTERFACTORY_H
#define _QEXTMVVMITEMCONVERTERFACTORY_H

//! @file itemconverterfactory.h
//! Collection of factory functions to create QEXTMvvmSessionItem converters to/from serialized content.

#include <memory>
#include <qextMvvmJsonItemConverterInterface.h>

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

#endif // _QEXTMVVMITEMCONVERTERFACTORY_H
