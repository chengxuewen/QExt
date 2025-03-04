// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/factories/modelconverterfactory.h"
#include "model/factories/itemconverterfactory.h"
#include "model/serialization/jsonitem_types.h"
#include "model/serialization/jsonmodelconverter.h"

//! Creates a JSON model converter intended for model cloning.
//! Saves a full deep copy of model in JSON. When restoring, reconstruct full copy.
//! This will lead to item ID's which are identical to original.

QExtUniquePointer<ModelView::QExtMvvmJsonModelConverterInterface> ModelView::qextMvvmCreateModelCloneConverter()
{
    return qextMakeUnique<QExtMvvmJsonModelConverter>(QExtMvvmConverterMode::clone);
}

//! Creates a JSON model converter intended for model copying.
//! Saves a full deep copy of model in JSON. When restoring, reconstruct full copy and regenerate
//! item's ID to make them unique.

QExtUniquePointer<ModelView::QExtMvvmJsonModelConverterInterface> ModelView::qextMvvmCreateModelCopyConverter()
{
    return qextMakeUnique<QExtMvvmJsonModelConverter>(QExtMvvmConverterMode::copy);
}

//! Creates a JSON model converter intended for save/load of the project on disk.
//! When saving to disk, only certain data is saved. When loading from disk, items
//! in memory is gently updated from JSON content.

QExtUniquePointer<ModelView::QExtMvvmJsonModelConverterInterface> ModelView::qextMvvmCreateModelProjectConverter()
{
    return qextMakeUnique<QExtMvvmJsonModelConverter>(QExtMvvmConverterMode::project);
}
