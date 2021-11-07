#ifndef _QEXTMVVMJSONVARIANTCONVERTER_H
#define _QEXTMVVMJSONVARIANTCONVERTER_H

#include <qextFunction.h>
#include <qextMvvmJsonVariantConverterInterface.h>

#include <QMap>
#include <QVector>
#include <QVariant>
#include <QJsonObject>

class QJsonObject;
class QJsonVariant;

//! Default converter between supported variants and json objects.

class QEXT_MVVM_API QEXTMvvmJsonVariantConverter : public QEXTMvvmJsonVariantConverterInterface
{
public:
    typedef QEXTFunction<QJsonObject, const QVariant &> VariantToJsonFunction;
    typedef QEXTFunction<QVariant, const QJsonObject &> JsonToVariantFunction;

    QEXTMvvmJsonVariantConverter();

    QJsonObject getJson(const QVariant &variant) QEXT_DECL_OVERRIDE;

    QVariant getVariant(const QJsonObject &object) QEXT_DECL_OVERRIDE;

    bool isVariant(const QJsonObject &object) const;

private:
    QMap<QString, VariantToJsonFunction> m_variantToJsonConverters;
    QMap<QString, JsonToVariantFunction> m_jsonToVariantconverters;
};

#endif // _QEXTMVVMJSONVARIANTCONVERTER_H
