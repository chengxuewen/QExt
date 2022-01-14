#ifndef _QEXTMVVMSERIALIZATIONITEMBACKUPSTRATEGY_H
#define _QEXTMVVMSERIALIZATIONITEMBACKUPSTRATEGY_H

#include <qextMvvmGlobal.h>

#include <memory>

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

#endif // _QEXTMVVMSERIALIZATIONITEMBACKUPSTRATEGY_H
