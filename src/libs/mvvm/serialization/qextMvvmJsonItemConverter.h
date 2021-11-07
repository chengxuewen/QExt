#ifndef _QEXTMVVMJSONITEMCONVERTER_H
#define _QEXTMVVMJSONITEMCONVERTER_H

#include <qextMvvmJsonItemConverterInterface.h>

#include <QSharedPointer>

class QEXTMvvmItemFactoryInterface;
class QEXTMvvmConverterContext;

//! Converter between QEXTMvvmItem and JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemConverter : public QEXTMvvmJsonItemConverterInterface
{
public:
    QEXTMvvmJsonItemConverter(const QEXTMvvmConverterContext &context);
    QEXTMvvmJsonItemConverter(const QEXTMvvmJsonItemConverter &) = delete;
    QEXTMvvmJsonItemConverter &operator=(const QEXTMvvmJsonItemConverter &) = delete;

    ~QEXTMvvmJsonItemConverter() QEXT_DECL_OVERRIDE;

    QJsonObject toJson(const QEXTMvvmItem *item) const QEXT_DECL_OVERRIDE;

    QEXTMvvmItem *fromJson(const QJsonObject &json) const QEXT_DECL_OVERRIDE;

private:
    struct JsonItemConverterImpl;
    QScopedPointer<JsonItemConverterImpl> p_impl;
};


#endif // _QEXTMVVMJSONITEMCONVERTER_H
