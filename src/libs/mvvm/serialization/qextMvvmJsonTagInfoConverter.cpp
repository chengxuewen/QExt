// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <qextMvvmTagInfo.h>
#include <qextMvvmJsonTagInfoConverter.h>
#include <stdexcept>



namespace
{
QStringList expected_taginfo_keys()
{
    QStringList result = QStringList()
                         << QEXTMvvmJsonTagInfoConverter::nameKey << QEXTMvvmJsonTagInfoConverter::minKey
                         << QEXTMvvmJsonTagInfoConverter::maxKey << QEXTMvvmJsonTagInfoConverter::modelsKey;
    std::sort(result.begin(), result.end());
    return result;
}
} // namespace

QJsonObject QEXTMvvmJsonTagInfoConverter::toJson(const QEXTMvvmTagInfo& tag)
{
    QJsonObject result;
    result[nameKey] = tag.name();
    result[minKey] = tag.min();
    result[maxKey] = tag.max();
    QJsonArray str_array;
    for (const auto& str : tag.modelTypes())
        str_array.append(str);
    result[modelsKey] = str_array;

    return result;
}

QEXTMvvmTagInfo QEXTMvvmJsonTagInfoConverter::fromJson(const QJsonObject &object)
{
    if (!isTagInfo(object))
        throw std::runtime_error("JsonTagInfo::get_tags() -> Invalid json object.");

    auto name = object[nameKey].toString();
    auto min = object[minKey].toInt();
    auto max = object[maxKey].toInt();
    QVector<QString> models;
    for (const auto ref : object[modelsKey].toArray())
        models.append(ref.toString());

    return QEXTMvvmTagInfo(name, min, max, models);
}

//! Returns true if given json object represents QEXTMvvmTagInfo object.

bool QEXTMvvmJsonTagInfoConverter::isTagInfo(const QJsonObject& object)
{
    static const QStringList expected = expected_taginfo_keys();

    if (object.keys() != expected)
        return false;

    if (!object[modelsKey].isArray())
        return false;

    return true;
}
