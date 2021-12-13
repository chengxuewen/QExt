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
//! Collection of custom types involved into QEXTMvvmSessionItem and JSON mutual convertion.

#include <functional>
#include <memory>
#include <qextMvvmGlobal.h>
#include <vector>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionItem;
class ItemFactoryInterface;

//! Provides necessary callbacks to convert QEXTMvvmSessionItem to JSON and back.

struct QEXT_MVVM_API ConverterCallbacks {
    using create_json_t = std::function<QJsonObject(const QEXTMvvmSessionItem&)>;
    using create_item_t = std::function<std::unique_ptr<QEXTMvvmSessionItem>(const QJsonObject&)>;
    using update_item_t = std::function<void(const QJsonObject&, QEXTMvvmSessionItem*)>;

    create_json_t m_create_json; //! creates JSON object from session item
    create_item_t m_create_item; //! creates new QEXTMvvmSessionItem from JSON object
    update_item_t m_update_item; //! updates existing QEXTMvvmSessionItem from JSON object
};

//! Flags to define converter behavior on the way from QEXTMvvmSessionItem to JSON and back.

enum class ConverterMode {
    none,   //!< undefined converter mode
    clone,  //!< full deep copying with item identifiers preserved
    copy,   //!< full deep copying with item identifiers regenerated
    project //!< selective copying for saving/loading the project (tags and data created by item,
            //!< updated from JSON)
};

//! Returns true if given mode requires ID regeneration instead of using the one stored in JSON.
inline bool isRegenerateIdWhenBackFromJson(ConverterMode mode)
{
    return mode == ConverterMode::copy;
}

//! Returns true if item content should be reconstructed from JSON
inline bool isRebuildItemDataAndTagFromJson(ConverterMode mode)
{
    return mode != ConverterMode::project;
}

//! Collection of input paramters for SessionItemConverter

struct QEXT_MVVM_API ConverterContext {
    const ItemFactoryInterface* m_factory{nullptr};
    ConverterMode m_mode = ConverterMode::none;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEM_TYPES_H
