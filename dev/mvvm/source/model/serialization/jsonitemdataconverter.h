// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H

#include "model/serialization/jsonitemdataconverterinterface.h"
#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView {

class QExtMvvmJsonVariantConverterInterface;

//! Default converter of QExtMvvmSessionItemData to/from json object.

class QEXT_MVVM_API QExtMvvmJsonItemDataConverter : public QExtMvvmJsonItemDataConverterInterface {
public:
    using accept_strategy_t = std::function<bool(int)>;

    QExtMvvmJsonItemDataConverter(accept_strategy_t to_json_accept = {},
                          accept_strategy_t from_json_accept = {});

    ~QExtMvvmJsonItemDataConverter() override;

    QJsonArray to_json(const QExtMvvmSessionItemData& data) override;

    void from_json(const QJsonArray& object, QExtMvvmSessionItemData& data) override;

    static QExtUniquePointer<QExtMvvmJsonItemDataConverterInterface> createCopyConverter();

    static QExtUniquePointer<QExtMvvmJsonItemDataConverterInterface> createProjectConverter();

private:
    bool isRoleToJson(int role) const;
    bool isRoleFromJson(int role) const;

    accept_strategy_t m_to_json_accept;   //!< callback to find whether to write role to json
    accept_strategy_t m_from_json_accept; //!< callback to find whether to read role from json
    QExtUniquePointer<QExtMvvmJsonVariantConverterInterface> m_variant_converter;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMDATACONVERTER_H
