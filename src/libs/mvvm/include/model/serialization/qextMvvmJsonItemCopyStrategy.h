#ifndef _QEXTMVVMSERIALIZATIONJSONITEMCOPYSTRATEGY_H
#define _QEXTMVVMSERIALIZATIONJSONITEMCOPYSTRATEGY_H

#include <qextMvvmItemCopyStrategy.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmItemFactoryInterface;

//! Provide QEXTMvvmSessionItem copying using json based strategy.

class QEXT_MVVM_API QEXTMvvmJsonItemCopyStrategy : public QEXTMvvmItemCopyStrategy
{
public:
    QEXTMvvmJsonItemCopyStrategy(const QEXTMvvmItemFactoryInterface* item_factory);
    ~QEXTMvvmJsonItemCopyStrategy();

    std::unique_ptr<QEXTMvvmSessionItem> createCopy(const QEXTMvvmSessionItem* item) const;

private:
    struct JsonItemCopyStrategyImpl;
    std::unique_ptr<JsonItemCopyStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONITEMCOPYSTRATEGY_H
