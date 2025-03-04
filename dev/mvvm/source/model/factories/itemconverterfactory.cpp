// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/factories/itemconverterfactory.h"
#include "model/serialization/jsonitem_types.h"
#include "model/serialization/jsonitemconverter.h"

namespace ModelView {

//! Creates JSON item converter intended for item cloning.
//! Saves full deep copy of item to JSON. When restoring from JSON, reconstruct everything,
//! including item's unique ID. Used for backup.

QExtUniquePointer<QExtMvvmJsonItemConverterInterface>
qextMvvmCreateItemCloneConverter(const QExtMvvmItemFactoryInterface* item_factory)
{
    QExtMvvmConverterContext context(item_factory, QExtMvvmConverterMode::clone);
    return qextMakeUnique<QExtMvvmJsonItemConverter>(context);
}

//! Creates JSON item converter intended for item copying.
//! Saves full deep copy of item to JSON. When restoring from JSON, will regenerate item's ID
//! to make it unique. Used for copying of item together with its children.

QExtUniquePointer<QExtMvvmJsonItemConverterInterface>
qextMvvmCreateItemCopyConverter(const QExtMvvmItemFactoryInterface* item_factory)
{
    QExtMvvmConverterContext context(item_factory, QExtMvvmConverterMode::copy);
    return qextMakeUnique<QExtMvvmJsonItemConverter>(context);
}

//! Creates JSON item converter intended for saving on disk.
//! When saving on disk:
//! + Only selected data roles of items are saved (i.e. DATA, IDENTIFIER)
//! + All tags with its content are saved as usual
//! When loading from disk:
//! + Only selected roles are taken from JSON (i.e. DATA, IDENTIFIER), other roles (e.g. TOOLTIPS)
//!   are taken from memory.
//! + Property tags are updated, universal tags reconstructed.

QExtUniquePointer<QExtMvvmJsonItemConverterInterface>
qextMvvmCreateItemProjectConverter(const QExtMvvmItemFactoryInterface* item_factory)
{
    QExtMvvmConverterContext context(item_factory, QExtMvvmConverterMode::project);
    return qextMakeUnique<QExtMvvmJsonItemConverter>(context);
}

} // namespace ModelView
