// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>
#include <memory>

class QJsonArray;

namespace ModelView {

class QExtMvvmSessionItemData;

//! Base class for all converters of QExtMvvmSessionItemData to/from JSON object.

class QEXT_MVVM_API QExtMvvmJsonItemDataConverterInterface {
public:
    virtual ~QExtMvvmJsonItemDataConverterInterface() = default;

    //! Converts QExtMvvmSessionItemData to JSON;
    virtual QJsonArray to_json(const QExtMvvmSessionItemData&) = 0;

    //! Converts QExtMvvmSessionItemData from JSON;
    virtual void from_json(const QJsonArray& object, QExtMvvmSessionItemData& data) = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMDATACONVERTERINTERFACE_H
