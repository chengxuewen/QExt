// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCommandUtils.h>
// #include "model/commands/commandutils.h"
#include "model/model/sessionmodel.h"
#include "model/serialization/jsonitembackupstrategy.h"
#include "model/serialization/jsonitemcopystrategy.h"

QExtUniquePointer<ModelView::QExtMvvmItemBackupStrategy>
ModelView::qextMvvmCreateItemBackupStrategy(const ModelView::QExtMvvmSessionModel* model)
{
    assert(model);
    return qextMakeUnique<JsonItemBackupStrategy>(model->factory());
}

QExtUniquePointer<ModelView::QExtMvvmItemCopyStrategy>
ModelView::qextMvvmCreateItemCopyStrategy(const ModelView::QExtMvvmSessionModel* model)
{
    assert(model);
    return qextMakeUnique<QExtMvvmJsonItemCopyStrategy>(model->factory());
}
