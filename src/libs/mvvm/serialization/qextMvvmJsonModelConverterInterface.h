#ifndef _QEXTMVVMJSONMODELCONVERTERINTERFACE_H
#define _QEXTMVVMJSONMODELCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

class QJsonObject;

class QEXTMvvmModel;

//! Base class for all converters of QEXTMvvmModel to/from json object.

class QEXT_MVVM_API QEXTMvvmJsonModelConverterInterface
{
public:
    virtual ~QEXTMvvmJsonModelConverterInterface() = default;

    virtual QJsonObject toJson(const QEXTMvvmModel&) const = 0;

    virtual void fromJson(const QJsonObject&, QEXTMvvmModel&) const = 0;
};

#endif // _QEXTMVVMJSONMODELCONVERTERINTERFACE_H
