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

#include "qextMVVMGlobal.h"
#include <memory>

namespace ModelView {

class SessionItem;

//! Interface for deep item copying.

class QEXT_MVVM_API ItemCopyStrategy {
public:
    virtual ~ItemCopyStrategy() = default;

    //! Creates item copy by deep copying all children. SessionItem identifiers will be regenerated.
    virtual std::unique_ptr<SessionItem> createCopy(const SessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ITEMCOPYSTRATEGY_H
