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

#include <qextMvvmJsonTagInfoConverterInterface.h>
#include <QString>

namespace ModelView
{

//! Default converter between QExtMvvmTagInfo and json object.

class QEXT_MVVM_API QExtMvvmJsonTagInfoConverter : public QExtMvvmJsonTagInfoConverterInterface
{
public:
    static constexpr const char *nameKey = "name";
    static constexpr const char *minKey = "min";
    static constexpr const char *maxKey = "max";
    static constexpr const char *modelsKey = "models";

    QJsonObject to_json(const QExtMvvmTagInfo& tag) override;

    QExtMvvmTagInfo from_json(const QJsonObject& object) override;

    bool isTagInfo(const QJsonObject& object);
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONTAGINFOCONVERTER_H
