#ifndef _QEXTMVVMJSONTAGINFOCONVERTER_H
#define _QEXTMVVMJSONTAGINFOCONVERTER_H

#include <QString>
#include <qextMvvmJsonTagInfoConverterInterface.h>

//! Default converter between QEXTMvvmTagInfo and json object.

class QEXT_MVVM_API QEXTMvvmJsonTagInfoConverter : public QEXTMvvmJsonTagInfoConverterInterface
{
public:
    static inline const QString nameKey = "name";
    static inline const QString minKey = "min";
    static inline const QString maxKey = "max";
    static inline const QString modelsKey = "models";

    QJsonObject toJson(const QEXTMvvmTagInfo &tag) QEXT_DECL_OVERRIDE;

    QEXTMvvmTagInfo fromJson(const QJsonObject &object) QEXT_DECL_OVERRIDE;

    bool isTagInfo(const QJsonObject& object);
};

#endif // _QEXTMVVMJSONTAGINFOCONVERTER_H
