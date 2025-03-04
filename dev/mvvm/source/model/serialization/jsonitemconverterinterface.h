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

#include <qextMvvmGlobal.h>
#include <memory>

class QJsonObject;

namespace ModelView {

class QExtMvvmSessionItem;

//! Base class for all converters of QExtMvvmSessionItem to/from JSON object.

class QEXT_MVVM_API QExtMvvmJsonItemConverterInterface {
public:
    virtual ~QExtMvvmJsonItemConverterInterface() = default;

    //! Converts item to JSON.
    virtual QJsonObject to_json(const QExtMvvmSessionItem* item) const = 0;

    //! Creates item from JSON.
    virtual QExtUniquePointer<QExtMvvmSessionItem> from_json(const QJsonObject&) const = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTERINTERFACE_H
