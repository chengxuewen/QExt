#ifndef _QEXTMVVMITEMBACKUPSTRATEGY_H
#define _QEXTMVVMITEMBACKUPSTRATEGY_H

#include <memory>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Interface to backup items for later restore.

class QEXT_MVVM_API QEXTMvvmItemBackupStrategy
{
public:
    virtual ~QEXTMvvmItemBackupStrategy() = default;

    //! Restore item from saved content.
    virtual std::unique_ptr<QEXTMvvmSessionItem> restoreItem() const = 0;

    //! Save item's content.
    virtual void saveItem(const QEXTMvvmSessionItem*) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMITEMBACKUPSTRATEGY_H
