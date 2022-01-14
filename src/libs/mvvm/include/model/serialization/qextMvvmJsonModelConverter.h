#ifndef _QEXTMVVMSERIALIZATIONJSONMODELCONVERTER_H
#define _QEXTMVVMSERIALIZATIONJSONMODELCONVERTER_H

#include <qextMvvmJsonModelConverterInterface.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionModel;
enum class ConverterMode;

//! Converter of SessionModel to/from json object with posibility to select one of convertion modes.

class QEXT_MVVM_API QEXTMvvmJsonModelConverter : public QEXTMvvmJsonModelConverterInterface
{
public:
    QEXTMvvmJsonModelConverter(ConverterMode mode);
    ~QEXTMvvmJsonModelConverter() override;

    //! Writes content of model into json.
    QJsonObject to_json(const QEXTMvvmSessionModel& model) const override;

    //! Reads json object and build the model.
    void from_json(const QJsonObject& json, QEXTMvvmSessionModel& model) const override;

private:
    ConverterMode m_mode;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONMODELCONVERTER_H
