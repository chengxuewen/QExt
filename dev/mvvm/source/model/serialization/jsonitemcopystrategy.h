// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
#define MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H

#include "model/interfaces/itemcopystrategy.h"
#include <memory>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmItemFactoryInterface;

//! Provide QExtMvvmSessionItem copying using json based strategy.

class QEXT_MVVM_API QExtMvvmJsonItemCopyStrategy : public QExtMvvmItemCopyStrategy {
public:
    QExtMvvmJsonItemCopyStrategy(const QExtMvvmItemFactoryInterface* item_factory);
    ~QExtMvvmJsonItemCopyStrategy();

    QExtUniquePointer<QExtMvvmSessionItem> createCopy(const QExtMvvmSessionItem* item) const;

private:
    struct JsonItemCopyStrategyImpl;
    QExtUniquePointer<JsonItemCopyStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
