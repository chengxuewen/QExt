// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_ITEMCOPYSTRATEGY_H
#define MVVM_SERIALIZATION_ITEMCOPYSTRATEGY_H

#include <memory>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Interface for deep item copying.

class QEXT_MVVM_API QEXTMvvmItemCopyStrategy
{
public:
    virtual ~QEXTMvvmItemCopyStrategy() = default;

    //! Creates item copy by deep copying all children. QEXTMvvmSessionItem identifiers will be regenerated.
    virtual std::unique_ptr<QEXTMvvmSessionItem> createCopy(const QEXTMvvmSessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_ITEMCOPYSTRATEGY_H
