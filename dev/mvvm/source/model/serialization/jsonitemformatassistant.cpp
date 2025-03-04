// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/serialization/jsonitemformatassistant.h"
#include <QJsonObject>
#include <QStringList>

using namespace ModelView;

namespace {
//! Returns list of keys which should be in QJsonObject to represent QExtMvvmSessionItem.
QStringList expected_item_keys()
{
    QStringList result{QExtMvvmJsonItemFormatAssistant::modelKey, QExtMvvmJsonItemFormatAssistant::itemDataKey,
                       QExtMvvmJsonItemFormatAssistant::itemTagsKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QExtMvvmSessionItemData.

QStringList expected_itemdata_keys()
{
    QStringList result{QExtMvvmJsonItemFormatAssistant::roleKey, QExtMvvmJsonItemFormatAssistant::variantKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QExtMvvmSessionItemTags.

QStringList expected_tags_keys()
{
    QStringList result{QExtMvvmJsonItemFormatAssistant::defaultTagKey,
                       QExtMvvmJsonItemFormatAssistant::containerKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QExtMvvmSessionItemContainer.

QStringList expected_itemcontainer_keys()
{
    QStringList result = {QExtMvvmJsonItemFormatAssistant::tagInfoKey, QExtMvvmJsonItemFormatAssistant::itemsKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QExtMvvmSessionModel.

QStringList expected_sessionmodel_keys()
{
    QStringList result{QExtMvvmJsonItemFormatAssistant::sessionModelKey, QExtMvvmJsonItemFormatAssistant::itemsKey};
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace

//! Returns true if given json object represents QExtMvvmSessionItem.

bool QExtMvvmJsonItemFormatAssistant::isSessionItem(const QJsonObject& json) const
{
    static const QStringList expected = expected_item_keys();

    if (json.keys() != expected)
        return false;

    if (!json[itemDataKey].isArray())
        return false;

    if (!json[itemTagsKey].isObject())
        return false;

    return true;
}

bool QExtMvvmJsonItemFormatAssistant::isSessionItemData(const QJsonObject& json) const
{
    static const QStringList expected = expected_itemdata_keys();
    return json.keys() == expected;
}

//! Returns true if given json object represents QExtMvvmSessionItemTags.

bool QExtMvvmJsonItemFormatAssistant::isSessionItemTags(const QJsonObject& json) const
{
    static const QStringList expected = expected_tags_keys();

    if (json.keys() != expected)
        return false;

    if (!json[containerKey].isArray())
        return false;

    return true;
}

//! Returns true if given json object represents QExtMvvmSessionItemContainer.

bool QExtMvvmJsonItemFormatAssistant::isSessionItemContainer(const QJsonObject& json) const
{
    static const QStringList expected = expected_itemcontainer_keys();

    if (json.keys() != expected)
        return false;

    if (!json[tagInfoKey].isObject())
        return false;

    if (!json[itemsKey].isArray())
        return false;

    return true;
}

//! Returns true if given json object represents QExtMvvmSessionModel.

bool QExtMvvmJsonItemFormatAssistant::isSessionModel(const QJsonObject& object) const
{
    static const QStringList expected = expected_sessionmodel_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}
