#ifndef _QEXTMVVMJSONITEMTYPES_H
#define _QEXTMVVMJSONITEMTYPES_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

#include <functional>
#include <memory>
#include <QVector>

class QJsonObject;

class QEXTMvvmItem;
class QEXTMvvmItemFactoryInterface;

//! Provides necessary callbacks to convert QEXTMvvmItem to JSON and back.

struct QEXT_MVVM_API QEXTMvvmConverterCallbacks
{
    typedef QEXTFunction<QJsonObject, const QEXTMvvmItem &> CreateJsonFunction;
    typedef QEXTFunction<QEXTMvvmItem *, const QJsonObject &> CreateItemFunction;
    typedef QEXTFunction<void, const QJsonObject &, QEXTMvvmItem *> UpdateItemFunction;

    CreateJsonFunction m_create_json; //! creates JSON object from session item
    CreateItemFunction m_create_item; //! creates new QEXTMvvmItem from JSON object
    UpdateItemFunction m_update_item; //! updates existing QEXTMvvmItem from JSON object
};

//! Flags to define converter behavior on the way from QEXTMvvmItem to JSON and back.

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

struct QEXT_MVVM_API QEXTMvvmConverterContext
{
    const QEXTMvvmItemFactoryInterface* m_factory{nullptr};
    ConverterMode m_mode = ConverterMode::none;
};

#endif // _QEXTMVVMJSONITEMTYPES_H
