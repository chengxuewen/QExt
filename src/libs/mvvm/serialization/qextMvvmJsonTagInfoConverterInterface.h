#ifndef _QEXTMVVMJSONTAGINFOCONVERTERINTERFACE_H
#define _QEXTMVVMJSONTAGINFOCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

class QJsonObject;

class QEXTMvvmTagInfo;

//! Base class for all converters of QEXTMvvmTagInfo to/from json object

class QEXT_MVVM_API QEXTMvvmJsonTagInfoConverterInterface
{
public:
    virtual ~QEXTMvvmJsonTagInfoConverterInterface() = default;

    virtual QJsonObject toJson(const QEXTMvvmTagInfo&) = 0;

    virtual QEXTMvvmTagInfo fromJson(const QJsonObject&) = 0;
};

#endif // _QEXTMVVMJSONTAGINFOCONVERTERINTERFACE_H
