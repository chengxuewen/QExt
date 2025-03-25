// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCommandUtils.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmJsonItemBackupStrategy.h>
#include <qextMvvmJsonItemCopyStrategy.h>

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
