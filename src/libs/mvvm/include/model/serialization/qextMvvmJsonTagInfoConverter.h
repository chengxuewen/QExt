#ifndef _QEXTMVVMJSONTAGINFOCONVERTER_H
#define _QEXTMVVMJSONTAGINFOCONVERTER_H

#include <QString>
#include <qextMvvmJsonTagInfoConverterInterface.h>

namespace ModelView
{

//! Default converter between QEXTMvvmTagInfo and json object.

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

#endif // _QEXTMVVMJSONTAGINFOCONVERTER_H
