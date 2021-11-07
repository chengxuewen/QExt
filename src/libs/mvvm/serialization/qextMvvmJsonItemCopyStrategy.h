#ifndef _QEXTMVVMJSONITEMCOPYSTRATEGY_H
#define _QEXTMVVMJSONITEMCOPYSTRATEGY_H

#include <qextMvvmItemCopyStrategy.h>

#include <QScopedPointer>


class QEXTMvvmItem;
class QEXTMvvmItemFactoryInterface;

//! Provide QEXTMvvmItem copying using json based strategy.

class QEXT_MVVM_API QEXTMvvmJsonItemCopyStrategy : public QEXTMvvmItemCopyStrategy
{
public:
    QEXTMvvmJsonItemCopyStrategy(const QEXTMvvmItemFactoryInterface* item_factory);
    ~QEXTMvvmJsonItemCopyStrategy();

    QEXTMvvmItem *createCopy(const QEXTMvvmItem *item) const;

private:
    struct JsonItemCopyStrategyImpl;
    QScopedPointer<JsonItemCopyStrategyImpl> p_impl;
};

#endif // _QEXTMVVMJSONITEMCOPYSTRATEGY_H
