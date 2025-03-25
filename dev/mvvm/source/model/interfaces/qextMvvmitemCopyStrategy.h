// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ITEMCOPYSTRATEGY_H
#define MVVM_INTERFACES_ITEMCOPYSTRATEGY_H

#include <qextMvvmGlobal.h>

namespace ModelView {

class QExtMvvmSessionItem;

//! Interface for deep item copying.

class QEXT_MVVM_API QExtMvvmItemCopyStrategy {
public:
    virtual ~QExtMvvmItemCopyStrategy() = default;

    //! Creates item copy by deep copying all children. QExtMvvmSessionItem identifiers will be regenerated.
    virtual QExtUniquePointer<QExtMvvmSessionItem> createCopy(const QExtMvvmSessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ITEMCOPYSTRATEGY_H
