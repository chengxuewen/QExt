#ifndef _QEXTMVVMSERIALIZATIONJSONTAGINFOCONVERTER_H
#define _QEXTMVVMSERIALIZATIONJSONTAGINFOCONVERTER_H

#include <qextMvvmJsonTagInfoConverterInterface.h>

#include <QString>

namespace ModelView
{

//! Default converter between TagInfo and json object.

class QEXT_MVVM_API QEXTMvvmJsonTagInfoConverter : public QEXTMvvmJsonTagInfoConverterInterface
{
public:
    static inline const QString nameKey = "name";
    static inline const QString minKey = "min";
    static inline const QString maxKey = "max";
    static inline const QString modelsKey = "models";

    QJsonObject to_json(const QEXTMvvmTagInfo& tag) override;

    QEXTMvvmTagInfo from_json(const QJsonObject& object) override;

    bool isTagInfo(const QJsonObject& object);
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONTAGINFOCONVERTER_H
