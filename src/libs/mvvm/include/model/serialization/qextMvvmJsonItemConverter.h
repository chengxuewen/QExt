#ifndef _QEXTMVVMJSONITEMCONVERTER_H
#define _QEXTMVVMJSONITEMCONVERTER_H

#include <qextMvvmJsonItemConverterInterface.h>

namespace ModelView
{

    class QEXTMvvmItemFactoryInterface;
    class QEXTMvvmConverterContext;

//! Converter between QEXTMvvmSessionItem and JSON object.

    class QEXT_MVVM_API QEXTMvvmJsonItemConverter : public QEXTMvvmJsonItemConverterInterface
    {
    public:
        QEXTMvvmJsonItemConverter(const QEXTMvvmConverterContext &context);
        QEXTMvvmJsonItemConverter(const QEXTMvvmJsonItemConverter &) = delete;
        QEXTMvvmJsonItemConverter &operator=(const QEXTMvvmJsonItemConverter &) = delete;

        ~QEXTMvvmJsonItemConverter() override;

        QJsonObject to_json(const QEXTMvvmSessionItem *item) const override;

        std::unique_ptr<QEXTMvvmSessionItem> from_json(const QJsonObject &json) const override;

    private:
        struct JsonItemConverterImpl;
        std::unique_ptr<JsonItemConverterImpl> p_impl;
    };

} // namespace ModelView

#endif // _QEXTMVVMJSONITEMCONVERTER_H
