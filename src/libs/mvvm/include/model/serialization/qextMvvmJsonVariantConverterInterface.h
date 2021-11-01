#ifndef _QEXTMVVMJSONVARIANTCONVERTERINTERFACE_H
#define _QEXTMVVMJSONVARIANTCONVERTERINTERFACE_H

#include <qextMvvmVariant.h>
#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

//! Base class for all supported converters of QEXTMvvmVariant to/from json object

class QEXT_MVVM_API QEXTMvvmJsonVariantConverterInterface
{
public:
    virtual ~QEXTMvvmJsonVariantConverterInterface() = default;

    virtual QJsonObject get_json(const QEXTMvvmVariant&) = 0;

    virtual QEXTMvvmVariant get_variant(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMJSONVARIANTCONVERTERINTERFACE_H
