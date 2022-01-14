#ifndef _QEXTMVVMSERIALIZATIONJSONTAGINFOCONVERTERINTERFACE_H
#define _QEXTMVVMSERIALIZATIONJSONTAGINFOCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmTagInfo;

//! Base class for all converters of TagInfo to/from json object

class QEXT_MVVM_API QEXTMvvmJsonTagInfoConverterInterface
{
public:
    virtual ~QEXTMvvmJsonTagInfoConverterInterface() = default;

    virtual QJsonObject to_json(const QEXTMvvmTagInfo&) = 0;

    virtual QEXTMvvmTagInfo from_json(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONTAGINFOCONVERTERINTERFACE_H
