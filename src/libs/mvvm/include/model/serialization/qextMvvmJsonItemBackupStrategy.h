// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMBACKUPSTRATEGY_H
#define MVVM_SERIALIZATION_JSONITEMBACKUPSTRATEGY_H

#include <memory>
#include <qextMvvmItemBackupStrategy.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class ItemFactoryInterface;

//! Provide backup of QEXTMvvmSessionItem using json strategy.

class QEXT_MVVM_API JsonItemBackupStrategy : public ItemBackupStrategy
{
public:
    JsonItemBackupStrategy(const ItemFactoryInterface* item_factory);
    ~JsonItemBackupStrategy() override;

    std::unique_ptr<QEXTMvvmSessionItem> restoreItem() const override;

    void saveItem(const QEXTMvvmSessionItem* item) override;

private:
    struct JsonItemBackupStrategyImpl;
    std::unique_ptr<JsonItemBackupStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMBACKUPSTRATEGY_H
