// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H

#include <memory>
#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Base class for all converters of QEXTMvvmSessionItem to/from JSON object.

class QEXT_MVVM_API JsonItemConverterInterface
{
public:
    virtual ~JsonItemConverterInterface() = default;

    //! Converts item to JSON.
    virtual QJsonObject to_json(const QEXTMvvmSessionItem* item) const = 0;

    //! Creates item from JSON.
    virtual std::unique_ptr<QEXTMvvmSessionItem> from_json(const QJsonObject&) const = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H
