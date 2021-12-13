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

#include <memory>
#include <qextMvvmItemCopyStrategy.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmItemFactoryInterface;

//! Provide QEXTMvvmSessionItem copying using json based strategy.

class QEXT_MVVM_API JsonItemCopyStrategy : public QEXTMvvmItemCopyStrategy
{
public:
    JsonItemCopyStrategy(const QEXTMvvmItemFactoryInterface* item_factory);
    ~JsonItemCopyStrategy();

    std::unique_ptr<QEXTMvvmSessionItem> createCopy(const QEXTMvvmSessionItem* item) const;

private:
    struct JsonItemCopyStrategyImpl;
    std::unique_ptr<JsonItemCopyStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
