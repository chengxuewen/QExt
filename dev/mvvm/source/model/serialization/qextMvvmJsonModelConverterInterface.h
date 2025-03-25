// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONMODELCONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONMODELCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView {

class QExtMvvmSessionModel;

//! Base class for all converters of QExtMvvmSessionModel to/from json object.

class QEXT_MVVM_API QExtMvvmJsonModelConverterInterface {
public:
    virtual ~QExtMvvmJsonModelConverterInterface() = default;

    virtual QJsonObject to_json(const QExtMvvmSessionModel&) const = 0;

    virtual void from_json(const QJsonObject&, QExtMvvmSessionModel&) const = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONMODELCONVERTERINTERFACE_H
