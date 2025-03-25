// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONMODELCONVERTER_H
#define MVVM_SERIALIZATION_JSONMODELCONVERTER_H

#include <qextMvvmJsonModelConverterInterface.h>

class QJsonObject;

namespace ModelView {

class QExtMvvmSessionModel;
enum class QExtMvvmConverterMode;

//! Converter of QExtMvvmSessionModel to/from json object with posibility to select one of convertion modes.

class QEXT_MVVM_API QExtMvvmJsonModelConverter : public QExtMvvmJsonModelConverterInterface {
public:
    QExtMvvmJsonModelConverter(QExtMvvmConverterMode mode);
    ~QExtMvvmJsonModelConverter() override;

    //! Writes content of model into json.
    QJsonObject to_json(const QExtMvvmSessionModel& model) const override;

    //! Reads json object and build the model.
    void from_json(const QJsonObject& json, QExtMvvmSessionModel& model) const override;

private:
    QExtMvvmConverterMode m_mode;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONMODELCONVERTER_H
