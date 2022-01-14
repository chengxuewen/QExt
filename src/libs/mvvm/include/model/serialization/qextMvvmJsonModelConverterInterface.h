#ifndef _QEXTMVVMSERIALIZATIONJSONMODELCONVERTERINTERFACE_H
#define _QEXTMVVMSERIALIZATIONJSONMODELCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Base class for all converters of SessionModel to/from json object.

class QEXT_MVVM_API QEXTMvvmJsonModelConverterInterface
{
public:
    virtual ~QEXTMvvmJsonModelConverterInterface() = default;

    virtual QJsonObject to_json(const QEXTMvvmSessionModel&) const = 0;

    virtual void from_json(const QJsonObject&, QEXTMvvmSessionModel&) const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONMODELCONVERTERINTERFACE_H
