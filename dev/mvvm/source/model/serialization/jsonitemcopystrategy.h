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

class SessionItem;
class ItemFactoryInterface;

//! Provide SessionItem copying using json based strategy.

class QEXT_MVVM_API JsonItemCopyStrategy : public ItemCopyStrategy {
public:
    JsonItemCopyStrategy(const ItemFactoryInterface* item_factory);
    ~JsonItemCopyStrategy();

    QExtUniquePointer<SessionItem> createCopy(const SessionItem* item) const;

private:
    struct JsonItemCopyStrategyImpl;
    QExtUniquePointer<JsonItemCopyStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
