// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/serialization/jsontaginfoconverter.h"
#include "model/model/taginfo.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <stdexcept>

using namespace ModelView;

namespace {
QStringList expected_taginfo_keys()
{
    QStringList result = QStringList()
                         << QExtMvvmJsonTagInfoConverter::nameKey << QExtMvvmJsonTagInfoConverter::minKey
                         << QExtMvvmJsonTagInfoConverter::maxKey << QExtMvvmJsonTagInfoConverter::modelsKey;
    std::sort(result.begin(), result.end());
    return result;
}
} // namespace

QJsonObject QExtMvvmJsonTagInfoConverter::to_json(const ModelView::QExtMvvmTagInfo& tag)
{
    QJsonObject result;
    result[nameKey] = QString::fromStdString(tag.name());
    result[minKey] = tag.min();
    result[maxKey] = tag.max();
    QJsonArray str_array;
    for (const auto& str : tag.modelTypes())
        str_array.append(QString::fromStdString(str));
    result[modelsKey] = str_array;

    return result;
}

QExtMvvmTagInfo QExtMvvmJsonTagInfoConverter::from_json(const QJsonObject& object)
{
    if (!isTagInfo(object))
        throw std::runtime_error("JsonTagInfo::get_tags() -> Invalid json object.");

    auto name = object[nameKey].toString().toStdString();
    auto min = object[minKey].toInt();
    auto max = object[maxKey].toInt();
    std::vector<std::string> models;
    for (const auto ref : object[modelsKey].toArray())
        models.push_back(ref.toString().toStdString());

    return QExtMvvmTagInfo(name, min, max, models);
}

//! Returns true if given json object represents QExtMvvmTagInfo object.

bool QExtMvvmJsonTagInfoConverter::isTagInfo(const QJsonObject& object)
{
    static const QStringList expected = expected_taginfo_keys();

    if (object.keys() != expected)
        return false;

    if (!object[modelsKey].isArray())
        return false;

    return true;
}
