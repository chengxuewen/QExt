#ifndef _QEXTMVVMJSONITEMDATACONVERTERINTERFACE_H
#define _QEXTMVVMJSONITEMDATACONVERTERINTERFACE_H

#include <memory>
#include <qextMvvmGlobal.h>

class QJsonArray;

class QEXTMvvmItemData;

//! Base class for all converters of QEXTMvvmItemData to/from JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemDataConverterInterface
{
public:
    virtual ~QEXTMvvmJsonItemDataConverterInterface() = default;

    //! Converts QEXTMvvmItemData to JSON;
    virtual QJsonArray to_json(const QEXTMvvmItemData&) = 0;

    //! Converts QEXTMvvmItemData from JSON;
    virtual void from_json(const QJsonArray& object, QEXTMvvmItemData& data) = 0;
};

#endif // _QEXTMVVMJSONITEMDATACONVERTERINTERFACE_H
