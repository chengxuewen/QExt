#ifndef _QEXTMVVMSERIALIZATIONJSONITEMBACKUPSTRATEGY_H
#define _QEXTMVVMSERIALIZATIONJSONITEMBACKUPSTRATEGY_H

#include <qextMvvmItemBackupStrategy.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmItemFactoryInterface;

//! Provide backup of QEXTMvvmSessionItem using json strategy.

class QEXT_MVVM_API QEXTMvvmJsonItemBackupStrategy : public QEXTMvvmItemBackupStrategy
{
public:
    QEXTMvvmJsonItemBackupStrategy(const QEXTMvvmItemFactoryInterface* item_factory);
    ~QEXTMvvmJsonItemBackupStrategy() override;

    std::unique_ptr<QEXTMvvmSessionItem> restoreItem() const override;

    void saveItem(const QEXTMvvmSessionItem* item) override;

private:
    struct JsonItemBackupStrategyImpl;
    std::unique_ptr<JsonItemBackupStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONITEMBACKUPSTRATEGY_H
