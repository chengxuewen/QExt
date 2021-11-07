#ifndef _QEXTMVVMJSONITEMDATACONVERTER_H
#define _QEXTMVVMJSONITEMDATACONVERTER_H

#include <qextFunction.h>
#include <QScopedPointer>
#include <qextMvvmJsonItemDataConverterInterface.h>

#include <QString>

class QJsonObject;


class QEXTMvvmJsonVariantConverterInterface;

//! Default converter of QEXTMvvmItemData to/from json object.

class QEXT_MVVM_API QEXTMvvmJsonItemDataConverter : public QEXTMvvmJsonItemDataConverterInterface
{
public:
    typedef QEXTFunction<bool, int> accept_strategy_t;

    QEXTMvvmJsonItemDataConverter(accept_strategy_t to_json_accept = {},
                          accept_strategy_t from_json_accept = {});

    ~QEXTMvvmJsonItemDataConverter() QEXT_DECL_OVERRIDE;

    QJsonArray to_json(const QEXTMvvmItemData& data) QEXT_DECL_OVERRIDE;

    void from_json(const QJsonArray& object, QEXTMvvmItemData& data) QEXT_DECL_OVERRIDE;

    static QEXTMvvmJsonItemDataConverterInterface *createCopyConverter();

    static QEXTMvvmJsonItemDataConverterInterface *createProjectConverter();

private:
    bool isRoleToJson(int role) const;
    bool isRoleFromJson(int role) const;

    accept_strategy_t m_to_json_accept;   //!< callback to find whether to write role to json
    accept_strategy_t m_from_json_accept; //!< callback to find whether to read role from json
    QScopedPointer<QEXTMvvmJsonVariantConverterInterface> m_variant_converter;
};

#endif // _QEXTMVVMJSONITEMDATACONVERTER_H
