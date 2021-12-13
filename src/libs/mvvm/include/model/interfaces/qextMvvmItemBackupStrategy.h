// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_ITEMBACKUPSTRATEGY_H
#define MVVM_SERIALIZATION_ITEMBACKUPSTRATEGY_H

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

#endif // MVVM_SERIALIZATION_ITEMBACKUPSTRATEGY_H
