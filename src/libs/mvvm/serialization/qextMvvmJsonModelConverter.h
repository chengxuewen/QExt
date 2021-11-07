#ifndef _QEXTMVVMJSONMODELCONVERTER_H
#define _QEXTMVVMJSONMODELCONVERTER_H

#include <qextMvvmJsonModelConverterInterface.h>

class QJsonObject;

class QEXTMvvmModel;
enum class ConverterMode;

//! Converter of QEXTMvvmModel to/from json object with posibility to select one of convertion modes.

class QEXT_MVVM_API QEXTMvvmJsonModelConverter : public QEXTMvvmJsonModelConverterInterface
{
public:
    QEXTMvvmJsonModelConverter(ConverterMode mode);
    ~QEXTMvvmJsonModelConverter() QEXT_DECL_OVERRIDE;

    //! Writes content of model into json.
    QJsonObject toJson(const QEXTMvvmModel& model) const QEXT_DECL_OVERRIDE;

    //! Reads json object and build the model.
    void fromJson(const QJsonObject& json, QEXTMvvmModel& model) const QEXT_DECL_OVERRIDE;

private:
    ConverterMode m_mode;
};

#endif // _QEXTMVVMJSONMODELCONVERTER_H
