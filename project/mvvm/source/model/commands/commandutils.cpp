// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/commands/commandutils.h"
#include "model/model/sessionmodel.h"
#include "model/serialization/jsonitembackupstrategy.h"
#include "model/serialization/jsonitemcopystrategy.h"

QExtUniquePointer<ModelView::ItemBackupStrategy>
ModelView::CreateItemBackupStrategy(const ModelView::SessionModel* model)
{
    assert(model);
    return qextMakeUnique<JsonItemBackupStrategy>(model->factory());
}

QExtUniquePointer<ModelView::ItemCopyStrategy>
ModelView::CreateItemCopyStrategy(const ModelView::SessionModel* model)
{
    assert(model);
    return qextMakeUnique<JsonItemCopyStrategy>(model->factory());
}
