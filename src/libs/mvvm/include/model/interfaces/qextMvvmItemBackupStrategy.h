#ifndef _QEXTMVVMITEMBACKUPSTRATEGY_H
#define _QEXTMVVMITEMBACKUPSTRATEGY_H

#include <qextMvvmGlobal.h>

#include <QSharedPointer>

class QEXTMvvmItem;

//! Interface to backup items for later restore.

class QEXT_MVVM_API QEXTMvvmItemBackupStrategy
{
public:
    virtual ~QEXTMvvmItemBackupStrategy() {}

    //! Restore item from saved content.
    virtual QEXTMvvmItem *restoreItem() const = 0;

    //! Save item's content.
    virtual void saveItem(const QEXTMvvmItem *) = 0;
};


#endif // _QEXTMVVMITEMBACKUPSTRATEGY_H
