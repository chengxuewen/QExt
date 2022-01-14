#ifndef _QEXTMVVMSERIALIZATIONJSONVARIANTCONVERTER_H
#define _QEXTMVVMSERIALIZATIONJSONVARIANTCONVERTER_H

#include <qextMvvmJsonVariantConverterInterface.h>

#include <map>
#include <functional>
#include <string>

class QJsonObject;
class QJsonVariant;

namespace ModelView
{

//! Default converter between supported variants and json objects.

class QEXT_MVVM_API QEXTMvvmJsonVariantConverter : public QEXTMvvmJsonVariantConverterInterface
{
public:
    QEXTMvvmJsonVariantConverter();

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

#endif // _QEXTMVVMSERIALIZATIONJSONVARIANTCONVERTER_H
