#ifndef _QEXTMVVMJSONVARIANTCONVERTER_H
#define _QEXTMVVMJSONVARIANTCONVERTER_H

#include <functional>
#include <map>
#include <qextMvvmVariant.h>
#include <qextMvvmJsonVariantConverterInterface.h>
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

    QJsonObject get_json(const QEXTMvvmVariant& variant) override;

    QEXTMvvmVariant get_variant(const QJsonObject& object) override;

    bool isVariant(const QJsonObject& object) const;

private:
    struct Converters {
        std::function<QJsonObject(const QEXTMvvmVariant& variant)> variant_to_json;
        std::function<QEXTMvvmVariant(const QJsonObject& json)> json_to_variant;
    };

    std::map<std::string, Converters> m_converters;
};

} // namespace ModelView

#endif // _QEXTMVVMJSONVARIANTCONVERTER_H
