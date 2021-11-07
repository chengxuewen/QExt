// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonObject>
#include <QStringList>
#include <qextMvvmJsonItemFormatAssistant.h>



namespace
{
//! Returns list of keys which should be in QJsonObject to represent QEXTMvvmItem.
QStringList expected_item_keys()
{
    QStringList result{QEXTMvvmJsonItemFormatAssistant::modelKey, QEXTMvvmJsonItemFormatAssistant::itemDataKey,
                       QEXTMvvmJsonItemFormatAssistant::itemTagsKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QEXTMvvmItemData.

QStringList expected_itemdata_keys()
{
    QStringList result{QEXTMvvmJsonItemFormatAssistant::roleKey, QEXTMvvmJsonItemFormatAssistant::variantKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QEXTMvvmItemTags.

QStringList expected_tags_keys()
{
    QStringList result{QEXTMvvmJsonItemFormatAssistant::defaultTagKey,
                       QEXTMvvmJsonItemFormatAssistant::containerKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QEXTMvvmItemContainer.

QStringList expected_itemcontainer_keys()
{
    QStringList result = {QEXTMvvmJsonItemFormatAssistant::tagInfoKey, QEXTMvvmJsonItemFormatAssistant::itemsKey};
    std::sort(result.begin(), result.end());
    return result;
}

//! Returns list of keys which should be in QJsonObject to represent QEXTMvvmModel.

QStringList expected_sessionmodel_keys()
{
    QStringList result{QEXTMvvmJsonItemFormatAssistant::sessionModelKey, QEXTMvvmJsonItemFormatAssistant::itemsKey};
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace

//! Returns true if given json object represents QEXTMvvmItem.

bool QEXTMvvmJsonItemFormatAssistant::isSessionItem(const QJsonObject& json) const
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

bool QEXTMvvmJsonItemFormatAssistant::isSessionItemData(const QJsonObject& json) const
{
    static const QStringList expected = expected_itemdata_keys();
    return json.keys() == expected;
}

//! Returns true if given json object represents QEXTMvvmItemTags.

bool QEXTMvvmJsonItemFormatAssistant::isSessionItemTags(const QJsonObject& json) const
{
    static const QStringList expected = expected_tags_keys();

    if (json.keys() != expected)
        return false;

    if (!json[containerKey].isArray())
        return false;

    return true;
}

//! Returns true if given json object represents QEXTMvvmItemContainer.

bool QEXTMvvmJsonItemFormatAssistant::isSessionItemContainer(const QJsonObject& json) const
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

//! Returns true if given json object represents QEXTMvvmModel.

bool QEXTMvvmJsonItemFormatAssistant::isSessionModel(const QJsonObject& object) const
{
    static const QStringList expected = expected_sessionmodel_keys();

    if (object.keys() != expected)
        return false;

    if (!object[itemsKey].isArray())
        return false;

    return true;
}
