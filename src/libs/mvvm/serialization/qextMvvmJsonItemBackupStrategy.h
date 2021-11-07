#ifndef _QEXTMVVMJSONITEMBACKUPSTRATEGY_H
#define _QEXTMVVMJSONITEMBACKUPSTRATEGY_H

#include <qextMvvmItemBackupStrategy.h>

#include <QScopedPointer>

class QEXTMvvmItem;
class QEXTMvvmItemFactoryInterface;

//! Provide backup of QEXTMvvmItem using json strategy.

class QEXT_MVVM_API QEXTMvvmJsonItemBackupStrategy : public QEXTMvvmItemBackupStrategy
{
public:
    QEXTMvvmJsonItemBackupStrategy(const QEXTMvvmItemFactoryInterface *item_factory);
    ~QEXTMvvmJsonItemBackupStrategy() QEXT_DECL_OVERRIDE;

    QEXTMvvmItem *restoreItem() const QEXT_DECL_OVERRIDE;

    void saveItem(const QEXTMvvmItem *item) QEXT_DECL_OVERRIDE;

private:
    struct JsonItemBackupStrategyImpl;
    QScopedPointer<JsonItemBackupStrategyImpl> p_impl;
};


#endif // _QEXTMVVMJSONITEMBACKUPSTRATEGY_H
