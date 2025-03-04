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

#include "model/interfaces/itembackupstrategy.h"
#include <memory>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmItemFactoryInterface;

//! Provide backup of QExtMvvmSessionItem using json strategy.

class QEXT_MVVM_API JsonItemBackupStrategy : public QExtMvvmItemBackupStrategy {
public:
    JsonItemBackupStrategy(const QExtMvvmItemFactoryInterface* item_factory);
    ~JsonItemBackupStrategy() override;

    QExtUniquePointer<QExtMvvmSessionItem> restoreItem() const override;

    void saveItem(const QExtMvvmSessionItem* item) override;

private:
    struct JsonItemBackupStrategyImpl;
    QExtUniquePointer<JsonItemBackupStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMBACKUPSTRATEGY_H
