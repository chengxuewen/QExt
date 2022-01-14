// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmCommandUtils.h>
#include <qextMvvmSessionModel.h>
#include <serialization/qextMvvmJsonItemBackupStrategy.h>
#include <serialization/qextMvvmJsonItemCopyStrategy.h>

std::unique_ptr<ModelView::QEXTMvvmItemBackupStrategy>
ModelView::CreateItemBackupStrategy(const ModelView::QEXTMvvmSessionModel* model)
{
    assert(model);
    return make_unique<QEXTMvvmJsonItemBackupStrategy>(model->factory());
}

std::unique_ptr<ModelView::QEXTMvvmItemCopyStrategy>
ModelView::CreateItemCopyStrategy(const ModelView::QEXTMvvmSessionModel* model)
{
    assert(model);
    return make_unique<QEXTMvvmJsonItemCopyStrategy>(model->factory());
}
