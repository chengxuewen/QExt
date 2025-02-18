// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ITEMBACKUPSTRATEGY_H
#define MVVM_INTERFACES_ITEMBACKUPSTRATEGY_H

#include "qextMVVMGlobal.h"
#include <memory>

namespace ModelView {

class SessionItem;

//! Interface to backup items for later restore.

class QEXT_MVVM_API ItemBackupStrategy {
public:
    virtual ~ItemBackupStrategy() = default;

    //! Restore item from saved content.
    virtual QExtUniquePointer<SessionItem> restoreItem() const = 0;

    //! Save item's content.
    virtual void saveItem(const SessionItem*) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ITEMBACKUPSTRATEGY_H
