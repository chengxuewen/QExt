#include <qextMvvmCommandUtils.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmJsonItemBackupStrategy.h>
#include <qextMvvmJsonItemCopyStrategy.h>

std::unique_ptr<ModelView::QEXTMvvmItemBackupStrategy>
ModelView::CreateItemBackupStrategy(const ModelView::QEXTMvvmSessionModel* model)
{
    assert(model);
    return std::make_unique<QEXTMvvmJsonItemBackupStrategy>(model->factory());
}

std::unique_ptr<ModelView::QEXTMvvmItemCopyStrategy>
ModelView::CreateItemCopyStrategy(const ModelView::QEXTMvvmSessionModel* model)
{
    assert(model);
    return std::make_unique<QEXTMvvmJsonItemCopyStrategy>(model->factory());
}
