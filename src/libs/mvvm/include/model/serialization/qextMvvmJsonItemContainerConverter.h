#ifndef _QEXTMVVMJSONITEMCONTAINERCONVERTER_H
#define _QEXTMVVMJSONITEMCONTAINERCONVERTER_H

#include <functional>
#include <memory>
#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

    class QEXTMvvmSessionItem;
    class QEXTMvvmSessionItemContainer;
    class QEXTMvvmConverterCallbacks;

//! Converter between QEXTMvvmSessionItemContainer and JSON object.

    class QEXT_MVVM_API QEXTMvvmJsonItemContainerConverter
    {
    public:
        QEXTMvvmJsonItemContainerConverter(QEXTMvvmConverterCallbacks callbacks);
        ~QEXTMvvmJsonItemContainerConverter();

        QJsonObject to_json(const QEXTMvvmSessionItemContainer &container);

        void from_json(const QJsonObject &json, QEXTMvvmSessionItemContainer &container);

    private:
        struct JsonItemContainerConverterImpl;
        std::unique_ptr<JsonItemContainerConverterImpl> p_impl;
    };

} // namespace ModelView

#endif // _QEXTMVVMJSONITEMCONTAINERCONVERTER_H
