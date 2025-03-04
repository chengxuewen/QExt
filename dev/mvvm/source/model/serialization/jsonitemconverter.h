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

struct QExtMvvmConverterContext;

//! Converter between QExtMvvmSessionItem and JSON object.

class QEXT_MVVM_API QExtMvvmJsonItemConverter : public QExtMvvmJsonItemConverterInterface {
public:
    QExtMvvmJsonItemConverter(const QExtMvvmConverterContext& context);
    QExtMvvmJsonItemConverter(const QExtMvvmJsonItemConverter&) = delete;
    QExtMvvmJsonItemConverter& operator=(const QExtMvvmJsonItemConverter&) = delete;

    ~QExtMvvmJsonItemConverter() override;

    QJsonObject to_json(const QExtMvvmSessionItem* item) const override;

    QExtUniquePointer<QExtMvvmSessionItem> from_json(const QJsonObject& json) const override;

private:
    struct JsonItemConverterImpl;
    QExtUniquePointer<JsonItemConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONVERTER_H
