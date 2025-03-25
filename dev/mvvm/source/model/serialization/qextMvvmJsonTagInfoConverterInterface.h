// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H

#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView {

class QExtMvvmTagInfo;

//! Base class for all converters of QExtMvvmTagInfo to/from json object

class QEXT_MVVM_API QExtMvvmJsonTagInfoConverterInterface {
public:
    virtual ~QExtMvvmJsonTagInfoConverterInterface() = default;

    virtual QJsonObject to_json(const QExtMvvmTagInfo&) = 0;

    virtual QExtMvvmTagInfo from_json(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H
