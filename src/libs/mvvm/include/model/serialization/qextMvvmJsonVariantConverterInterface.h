#ifndef _QEXTMVVMSERIALIZATIONJSONVARIANTCONVERTERINTERFACE_H
#define _QEXTMVVMSERIALIZATIONJSONVARIANTCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QVariant>

class QJsonObject;

namespace ModelView
{

//! Base class for all supported converters of Variant to/from json object

class QEXT_MVVM_API QEXTMvvmJsonVariantConverterInterface
{
public:
    virtual ~QEXTMvvmJsonVariantConverterInterface() = default;

    virtual QJsonObject get_json(const QVariant&) = 0;

    virtual QVariant get_variant(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONVARIANTCONVERTERINTERFACE_H
