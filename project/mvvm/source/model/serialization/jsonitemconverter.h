// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMCONVERTER_H

#include "model/serialization/jsonitemconverterinterface.h"

namespace ModelView {

struct ConverterContext;

//! Converter between SessionItem and JSON object.

class QEXT_MVVM_API JsonItemConverter : public JsonItemConverterInterface {
public:
    JsonItemConverter(const ConverterContext& context);
    JsonItemConverter(const JsonItemConverter&) = delete;
    JsonItemConverter& operator=(const JsonItemConverter&) = delete;

    ~JsonItemConverter() override;

    QJsonObject to_json(const SessionItem* item) const override;

    QExtUniquePointer<SessionItem> from_json(const QJsonObject& json) const override;

private:
    struct JsonItemConverterImpl;
    QExtUniquePointer<JsonItemConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTER_H
