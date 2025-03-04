// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONTAGINFOCONVERTER_H
#define MVVM_SERIALIZATION_JSONTAGINFOCONVERTER_H

#include "model/serialization/jsontaginfoconverterinterface.h"
#include <QString>

namespace ModelView {

//! Default converter between QExtMvvmTagInfo and json object.

class QEXT_MVVM_API QExtMvvmJsonTagInfoConverter : public QExtMvvmJsonTagInfoConverterInterface {
public:
    static inline const QString nameKey = "name";
    static inline const QString minKey = "min";
    static inline const QString maxKey = "max";
    static inline const QString modelsKey = "models";

    QJsonObject to_json(const QExtMvvmTagInfo& tag) override;

    QExtMvvmTagInfo from_json(const QJsonObject& object) override;

    bool isTagInfo(const QJsonObject& object);
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONTAGINFOCONVERTER_H
