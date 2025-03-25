// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEM_TYPES_H
#define MVVM_SERIALIZATION_JSONITEM_TYPES_H

//! @file jsonitem_types.h
//! Collection of custom types involved into QExtMvvmSessionItem and JSON mutual convertion.

#include <qextMvvmGlobal.h>
#include <functional>
#include <memory>
#include <vector>

class QJsonObject;

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmItemFactoryInterface;

//! Provides necessary callbacks to convert QExtMvvmSessionItem to JSON and back.

struct QEXT_MVVM_API QExtMvvmConverterCallbacks {
    using create_json_t = std::function<QJsonObject(const QExtMvvmSessionItem&)>;
    using create_item_t = std::function<QExtUniquePointer<QExtMvvmSessionItem>(const QJsonObject&)>;
    using update_item_t = std::function<void(const QJsonObject&, QExtMvvmSessionItem*)>;

    create_json_t m_create_json; //! creates JSON object from session item
    create_item_t m_create_item; //! creates new QExtMvvmSessionItem from JSON object
    update_item_t m_update_item; //! updates existing QExtMvvmSessionItem from JSON object
};

//! Flags to define converter behavior on the way from QExtMvvmSessionItem to JSON and back.

enum class QExtMvvmConverterMode {
    none,   //!< undefined converter mode
    clone,  //!< full deep copying with item identifiers preserved
    copy,   //!< full deep copying with item identifiers regenerated
    project //!< selective copying for saving/loading the project (tags and data created by item,
            //!< updated from JSON)
};

//! Returns true if given mode requires ID regeneration instead of using the one stored in JSON.
inline bool isRegenerateIdWhenBackFromJson(QExtMvvmConverterMode mode)
{
    return mode == QExtMvvmConverterMode::copy;
}

//! Returns true if item content should be reconstructed from JSON
inline bool isRebuildItemDataAndTagFromJson(QExtMvvmConverterMode mode)
{
    return mode != QExtMvvmConverterMode::project;
}

//! Collection of input paramters for SessionItemConverter

struct QEXT_MVVM_API QExtMvvmConverterContext
{
    QExtMvvmConverterContext(const QExtMvvmItemFactoryInterface*factory, QExtMvvmConverterMode mode) : m_factory(factory), m_mode(mode) {}
    const QExtMvvmItemFactoryInterface* m_factory{nullptr};
    QExtMvvmConverterMode m_mode = QExtMvvmConverterMode::none;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEM_TYPES_H
