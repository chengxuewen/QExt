// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H
#define MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H

#include "model/core/variant.h"
#include "model/serialization/jsonvariantconverterinterface.h"
#include <functional>
#include <map>
#include <string>

class QJsonObject;

namespace ModelView {

//! Default converter between supported variants and json objects.

class QEXT_MVVM_API QExtMvvmJsonVariantConverter : public QExtMvvmJsonVariantConverterInterface {
public:
    QExtMvvmJsonVariantConverter();

    QJsonObject get_json(const QVariant& variant) override;

    QVariant get_variant(const QJsonObject& object) override;

    bool isVariant(const QJsonObject& object) const;

private:
    struct Converters {
        std::function<QJsonObject(const QVariant& variant)> variant_to_json;
        std::function<QVariant(const QJsonObject& json)> json_to_variant;
    };

    std::map<std::string, Converters> m_converters;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONVARIANTCONVERTER_H
