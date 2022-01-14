#ifndef _QEXTMVVMSERIALIZATIONJSONITEMDATACONVERTERINTERFACE_H
#define _QEXTMVVMSERIALIZATIONJSONITEMDATACONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

#include <memory>

class QJsonArray;

namespace ModelView
{

class QEXTMvvmSessionItemData;

//! Base class for all converters of SessionItemData to/from JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemDataConverterInterface
{
public:
    virtual ~QEXTMvvmJsonItemDataConverterInterface() = default;

    //! Converts SessionItemData to JSON;
    virtual QJsonArray to_json(const QEXTMvvmSessionItemData&) = 0;

    //! Converts SessionItemData from JSON;
    virtual void from_json(const QJsonArray& object, QEXTMvvmSessionItemData& data) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONITEMDATACONVERTERINTERFACE_H
