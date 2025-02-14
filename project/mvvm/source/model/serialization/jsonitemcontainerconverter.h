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

#include "qextMVVMGlobal.h"
#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionItem;
class SessionItemContainer;
struct ConverterCallbacks;

//! Converter between SessionItemContainer and JSON object.

class QEXT_MVVM_API JsonItemContainerConverter {
public:
    JsonItemContainerConverter(ConverterCallbacks callbacks);
    ~JsonItemContainerConverter();

    QJsonObject to_json(const SessionItemContainer& container);

    void from_json(const QJsonObject& json, SessionItemContainer& container);

private:
    struct JsonItemContainerConverterImpl;
    std::unique_ptr<JsonItemContainerConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMCONTAINERCONVERTER_H
