#ifndef _QEXTMVVMJSONITEMDATACONVERTERINTERFACE_H
#define _QEXTMVVMJSONITEMDATACONVERTERINTERFACE_H

#include <memory>
#include <qextMvvmGlobal.h>

class QJsonArray;

namespace ModelView
{

class QEXTMvvmSessionItemData;

//! Base class for all converters of QEXTMvvmSessionItemData to/from JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemDataConverterInterface
{
public:
    virtual ~QEXTMvvmJsonItemDataConverterInterface() = default;

    //! Converts QEXTMvvmSessionItemData to JSON;
    virtual QJsonArray to_json(const QEXTMvvmSessionItemData&) = 0;

    //! Converts QEXTMvvmSessionItemData from JSON;
    virtual void from_json(const QJsonArray& object, QEXTMvvmSessionItemData& data) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMJSONITEMDATACONVERTERINTERFACE_H
