#ifndef _QEXTMVVMJSONITEMCONTAINERCONVERTER_H
#define _QEXTMVVMJSONITEMCONTAINERCONVERTER_H

#include <QScopedPointer>
#include <qextMvvmGlobal.h>

#include <functional>

class QJsonObject;


class QEXTMvvmItem;
class QEXTMvvmItemContainer;
class QEXTMvvmConverterCallbacks;

//! Converter between QEXTMvvmItemContainer and JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemContainerConverter
{
public:
    QEXTMvvmJsonItemContainerConverter(QEXTMvvmConverterCallbacks callbacks);
    ~QEXTMvvmJsonItemContainerConverter();

    QJsonObject to_json(const QEXTMvvmItemContainer &container);

    void from_json(const QJsonObject &json, QEXTMvvmItemContainer &container);

private:
    struct JsonItemContainerConverterImpl;
    QScopedPointer<JsonItemContainerConverterImpl> p_impl;
};


#endif // _QEXTMVVMJSONITEMCONTAINERCONVERTER_H
