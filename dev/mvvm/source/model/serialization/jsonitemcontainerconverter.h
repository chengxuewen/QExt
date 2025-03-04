// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H

#include <qextMvvmGlobal.h>
#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmSessionItemContainer;
struct QExtMvvmConverterCallbacks;

//! Converter between QExtMvvmSessionItemContainer and JSON object.

class QEXT_MVVM_API QExtMvvmJsonItemContainerConverter {
public:
    QExtMvvmJsonItemContainerConverter(QExtMvvmConverterCallbacks callbacks);
    ~QExtMvvmJsonItemContainerConverter();

    QJsonObject to_json(const QExtMvvmSessionItemContainer& container);

    void from_json(const QJsonObject& json, QExtMvvmSessionItemContainer& container);

private:
    struct JsonItemContainerConverterImpl;
    QExtUniquePointer<JsonItemContainerConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H
