#ifndef _QEXTMVVMSERIALIZATIONJSONITEMCONTAINERCONVERTER_H
#define _QEXTMVVMSERIALIZATIONJSONITEMCONTAINERCONVERTER_H

#include <qextMvvmGlobal.h>

#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionItemContainer;
class QEXTMvvmConverterCallbacks;

//! Converter between SessionItemContainer and JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemContainerConverter
{
public:
    QEXTMvvmJsonItemContainerConverter(QEXTMvvmConverterCallbacks callbacks);
    ~QEXTMvvmJsonItemContainerConverter();

    QJsonObject to_json(const QEXTMvvmSessionItemContainer& container);

    void from_json(const QJsonObject& json, QEXTMvvmSessionItemContainer& container);

private:
    struct JsonItemContainerConverterImpl;
    std::unique_ptr<JsonItemContainerConverterImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONITEMCONTAINERCONVERTER_H
