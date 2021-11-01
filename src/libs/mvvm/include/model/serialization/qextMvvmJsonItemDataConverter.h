#ifndef _QEXTMVVMJSONITEMDATACONVERTER_H
#define _QEXTMVVMJSONITEMDATACONVERTER_H

#include <QString>
#include <functional>
#include <memory>
#include <qextMvvmJsonItemDataConverterInterface.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmJsonVariantConverterInterface;

//! Default converter of QEXTMvvmSessionItemData to/from json object.

class QEXT_MVVM_API QEXTMvvmJsonItemDataConverter : public QEXTMvvmJsonItemDataConverterInterface
{
public:
    using accept_strategy_t = std::function<bool(int)>;

    QEXTMvvmJsonItemDataConverter(accept_strategy_t to_json_accept = {},
                          accept_strategy_t from_json_accept = {});

    ~QEXTMvvmJsonItemDataConverter() override;

    QJsonArray to_json(const QEXTMvvmSessionItemData& data) override;

    void from_json(const QJsonArray& object, QEXTMvvmSessionItemData& data) override;

    static std::unique_ptr<QEXTMvvmJsonItemDataConverterInterface> createCopyConverter();

    static std::unique_ptr<QEXTMvvmJsonItemDataConverterInterface> createProjectConverter();

private:
    bool isRoleToJson(int role) const;
    bool isRoleFromJson(int role) const;

    accept_strategy_t m_to_json_accept;   //!< callback to find whether to write role to json
    accept_strategy_t m_from_json_accept; //!< callback to find whether to read role from json
    std::unique_ptr<QEXTMvvmJsonVariantConverterInterface> m_variant_converter;
};

} // namespace ModelView

#endif // _QEXTMVVMJSONITEMDATACONVERTER_H
