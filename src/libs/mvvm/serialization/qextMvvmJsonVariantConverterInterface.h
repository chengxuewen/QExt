#ifndef _QEXTMVVMJSONVARIANTCONVERTERINTERFACE_H
#define _QEXTMVVMJSONVARIANTCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QJsonObject>
#include <QVariant>

//! Base class for all supported converters of QVariant to/from json object

class QEXT_MVVM_API QEXTMvvmJsonVariantConverterInterface
{
public:
    virtual ~QEXTMvvmJsonVariantConverterInterface() { }

    virtual QJsonObject getJson(const QVariant &) = 0;

    virtual QVariant getVariant(const QJsonObject &) = 0;
};

#endif // _QEXTMVVMJSONVARIANTCONVERTERINTERFACE_H
