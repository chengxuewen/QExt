#ifndef _QEXTMVVMJSONMODELCONVERTERINTERFACE_H
#define _QEXTMVVMJSONMODELCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Base class for all converters of QEXTMvvmSessionModel to/from json object.

class QEXT_MVVM_API QEXTMvvmJsonModelConverterInterface
{
public:
    virtual ~QEXTMvvmJsonModelConverterInterface() = default;

    virtual QJsonObject to_json(const QEXTMvvmSessionModel&) const = 0;

    virtual void from_json(const QJsonObject&, QEXTMvvmSessionModel&) const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMJSONMODELCONVERTERINTERFACE_H
